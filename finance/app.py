import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # i have the history table of the purchases but i need to group them by symbol so there wont be 2 lines of the same stock
    history = db.execute("SELECT symbol , SUM(shares) AS totalshares FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0;", session["user_id"])

    # return the current price of the stocks and the total value
    totaltotal = 0
    for stock in history:
        stockinfo = lookup(stock["symbol"])
        stock["price"] = stockinfo["price"]
        stock["totalvalue"] = stock["price"] * stock["totalshares"]
        totaltotal += stock["totalvalue"]

    # get the current balance
    balancedict = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    balance = balancedict[0]["cash"]

    return render_template("index.html", history = history , totaltotal = totaltotal , balance = balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "POST":

        #get the info about the stock and check if it exists (SEARCH BUTTON)
        if request.form.get("stocksymbol"):

            # validate the symbol that we get
            if not lookup(request.form.get("stocksymbol")):
                return apology("Stock doesn't exist")

            stockinfo = lookup(request.form.get("stocksymbol"))


        # check and save (BUY BUTTON)
        if request.form.get("buybttn"):

            # validate the symbol that we get
            if not lookup(request.form.get("buybttn")):
                return apology("Stock doesn't exist")
            stockinfo = lookup(request.form.get("buybttn"))

            # validate the number of stocks
            stocknumber = request.form.get("stocknumber")
            try:
                intedquantity = int(stocknumber)
                if intedquantity <= 0:
                    return apology("Please enter a valid number")

            except (ValueError , TypeError):
                return apology("Please enter a valid number")

            # check if the user have enough money
            listusermoney = db.execute("SELECT cash FROM users WHERE id = ?",session["user_id"])
            usermoney = listusermoney[0]["cash"]
            stockprice = stockinfo["price"]
            stocksymbol = stockinfo["symbol"]
            total = float(stocknumber) * float(stockprice)

            if float(usermoney) > (total):
                # save the purchase in the database
                db.execute("INSERT INTO history (user_id, symbol, shares, price, total , operation) VALUES(?,?,?,?,?,?)",session["user_id"] , stocksymbol , stocknumber, stockprice , total , "BUY")
                # update the user's money
                cashupdated = float(usermoney) - total
                db.execute("UPDATE users SET cash = ? WHERE id = ?", cashupdated , session["user_id"])

                # Redirect user to home page
                return redirect("/")
            else:
                return apology("You don't have enough money for this purchase")

        return render_template("buy.html", stockinfo = stockinfo)

    # check if the user got transported from the quote page
    symbol = request.args.get("symbol")
    if symbol:
        stockinfo = lookup(symbol)
        return render_template("buy.html", stockinfo = stockinfo)

    return render_template("buy.html")


@app.route("/history")
@login_required
def history():

    history = db.execute("SELECT * FROM history WHERE user_id = ? ORDER BY timestamp DESC", session["user_id"])
    print (history)
    return render_template("history.html" , history = history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():

    # implement lookup function and show a html template to user that contains info about the stock
    if request.method == "POST":

        # redirect users when pressed on the button
        action = request.form.get("buy-sell")
        if action == "buy":
            return redirect("/buy")
        elif action == "sell":
            return redirect("/sell")

        #get the info about the stock and check if it exists
        if  lookup(request.form.get("stocksymbol")):
            stockinfo = lookup(request.form.get("stocksymbol"))
            return render_template("quote.html", stockinfo = stockinfo)
        else:
            # return apology if stock doesn't exist
            return apology("Stock doesn't exist")



    # print(lookup("amd"))
    #{'name': 'Advanced Micro Devices Inc. Common Stock', 'price': 135.09, 'symbol': 'AMD'}

    return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":

        # make sure user typed in name, password and password again
        rules = [
            (not request.form.get("username") , "Username is required"),
            (not request.form.get("password1") , "Password is required"),
            (not request.form.get("password2") , "Please fill in all required fields." ),
            (not request.form.get("password1") == request.form.get("password2") , "Passwords do not match.")
        ]

        for rule , feedback in rules:
            if rule:
                return apology(feedback)

        # check if username is taken
        username_check = db.execute("SELECT * FROM users WHERE username = ?" , request.form.get("username"))
        if not len(username_check) == 0:
            return apology("Username is taken.")

        #save the register data into finance.db
        password_hash = generate_password_hash(request.form.get("password1"))
        db.execute("INSERT INTO users (username , hash) VALUES(? , ?)", request.form.get("username") , password_hash)

        #save users id into the session
        username_list = db.execute("SELECT id FROM users WHERE username = ?" , request.form.get("username"))
        print(username_list[0]["id"])
        session["user_id"] = username_list[0]["id"]

        #redirect user to log in page
        return redirect("/")

    return render_template("register.html")



@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""

    # send the info of portfolio so we can show them to user for picking
    stocks = db.execute("SELECT symbol , SUM(shares) AS totalshares FROM history WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0;", session["user_id"])
    print(stocks)
    if request.method == "POST":

        #get the info about the stock and check if it exists (later i will check if the user has it or not)
        if request.form.get("stocksymbol"):

            stocksymbol = request.form.get("stocksymbol")
            stockinfo = lookup(request.form.get("stocksymbol"))

            # validate the symbol that we get
            if not lookup(stocksymbol):
                return apology("Stock doesn't exist")

            # valide the quantity of stocks (BURDA ISNUMERIC KULLANMA VE BURDAKI METHODU BUY FONKSIYONUNA DA EKLE)
            quantitysold = request.form.get("stocknumber")
            try:
                intedquantitysold = int(quantitysold)
                if intedquantitysold <= 0:
                    return apology("Please enter a valid number")

            except (ValueError , TypeError):
                return apology("Please enter a valid number")

            # update the database if user has enough stocks
            owned_stock = next((stock for stock in stocks if stock["symbol"] == stocksymbol), None)
            stockquantityowned = owned_stock["totalshares"]

            if stockquantityowned >= intedquantitysold:
                # process the selling in database
                stockprice = stockinfo["price"]
                total = float(intedquantitysold) * float(stockprice)
                db.execute("INSERT INTO history (user_id, symbol, shares, price, total , operation) VALUES(?,?,?,?,?,?)",session["user_id"] , stocksymbol , -intedquantitysold, stockprice , total , "SELL")

                # update the user's money
                moneygain = intedquantitysold * stockprice
                db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", moneygain , session["user_id"])

                # Redirect user to home page
                return redirect("/")

            else:
                return apology("You don't have enough stock to sell")

    return render_template("sell.html" , stocks = stocks)
