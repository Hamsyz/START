import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database

        # check if the user entered the needed datas
        if (
            request.form.get("name")
            and request.form.get("month")
            and request.form.get("day")
        ):  #and insert them into db
            name = request.form.get("name")
            month = request.form.get('month')
            day = request.form.get("day")
            db.execute("INSERT INTO birthdays (name , month , day) VALUES(? , ? ,?) ", name, month, day)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html

        birthdays = db.execute("SELECT * FROM birthdays")
        for birthday in birthdays:
            current_month = str(birthday["month"])
            current_day = str(birthday["day"])
            if len(current_month) < 2:
                birthday["month"] = "0" + str(birthday["month"])
            if len(current_day) < 2:
                birthday["day"] = "0" + str(birthday["day"])



        return render_template("index.html", birthdays = birthdays)


@app.route("/delete", methods=["GET", "POST"])
def delete():
    #add functionality
    if request.method == "POST":
        id = request.form.get("deletebutt")
        db.execute("DELETE FROM birthdays WHERE id = ?", id)
    return redirect("/")



