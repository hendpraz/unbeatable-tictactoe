# unbeatable-tictactoe
Unbeatable Tic-Tac-Toe game made with C programming language.

## Description

A backend program for unbeatable tictactoe game with State Transition Machine concept. Instead of saving user state, the application transitioning its state based on current state and user input. Built with Python (flask) and C.

## Installation
1. Run `gcc -o prog tictactoe.c`
2. Run `export FLASK_APP=application.py`
3. Run `flask run`

## How To Use

Request to URL `http://127.0.0.1:5000/` with `POST` method. Request body example:

```
{
	"fm": "y",
	"inp": 4,
	"state": "CO-X-X-O--"
}
```

- fm: Is player the one who moved first, ["y", "n"]
- inp: Player input for next move, [1..9]
- state: Current state of the game, represented with 10 characters

State "CO-X-X-O--" represents:

```
     |     |     
  O  |  -  |  X 
_____|_____|_____
     |     |     
  -  |  X  |  - 
_____|_____|_____
     |     |     
  O  |  -  |  - 
     |     |     
```