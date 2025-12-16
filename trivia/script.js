
    //QUESTION 1

        //create functions to turn the buttons to green or red

        function makegreen(){
            this.style.backgroundColor = "#2ecc71";
            let win = document.createElement("p");
            win.textContent = "Correct!";
            const area1 = document.querySelector("#message-area");
            area1.appendChild(win)
        }

        function makered(){
            this.style.backgroundColor = "#e74c3c";
            let lose = document.createElement("p");
            lose.textContent = "Incorrect";
            const area2 = document.querySelector("#message-area");
            area2.appendChild(lose)
        }

        //created event listeners to activate the functions when clicked
        document.querySelector("#button1").addEventListener("click" , makegreen)

        document.querySelector("#button2").addEventListener("click" , makered)

        document.querySelector("#button3").addEventListener("click" , makered)

        document.querySelector("#button4").addEventListener("click" , makered)


        //created another click listener for all the buttons to remove the previous event listeners when clicked
        document.querySelectorAll(".buttonsclass")
        .forEach(buttonsclass => {

            //when any of the buttons are pressed remove all of the event listeners
            buttonsclass.addEventListener("click", function(){
                document.getElementById("button1").removeEventListener("click", makegreen);
                document.getElementById("button2").removeEventListener("click", makered);
                document.getElementById("button3").removeEventListener("click", makered);
                document.getElementById("button4").removeEventListener("click", makered);
                }
            )
        })

        //QUESTION 2

        document.querySelector("#q2").addEventListener("submit" , function(e){

            //prevent the page from reloading
            e.preventDefault();

            //select the answer
            const answer2 = document.querySelector("#answer").value;

            //select the area to give feedback
            const area3 = document.querySelector("#message-area3");

            //check the answer
            if(answer2 == 255){
                //answer = CORRECT
                area3.textContent = "Correct!";
                document.querySelector("#answer").style.backgroundColor = "#2ecc71";
            }
            else{
                //answer = INCORRECT
                area3.textContent = "Incorrect";
                document.querySelector("#answer").style.backgroundColor = "#e74c3c";
            }


        })
