# User Manual

## Getting started

After you have successfully downloaded your new CheckMate program, duble click or right click and select run to start the application.

***NB! All functionalities need to be responded with a keyboard input, your computer mouse or trackpad does not work with the program.***

The first thing you will see is a page which asks you to either, start a new tournament or Quit the program. If you input _Q_ the program will close.
If you input _S_, you will be forwarded to the next page which asks you: 

_Are you certain you wish to start a new tournament?This will delete all existing tournament data, including the player list._ 

If you input:
- _N_: the previous page will show again.
- _Y_: You will be forwarded to the next page and be asked the following: 

On the next page you will be asked how many tables wil be at the tournament, choose between 1 and 1000.

Next you will be asked to choose how many rounds should be in the tournament, choose between 1 and 20.


## The program

After you have gone through the setup you will be met with this page:

V: View player list

E: Edit a player

A: Add player

D: Delete player

F: Start the first round

S: Start a new tournament

Q: Quit the program

Command: 

You wil now get a run through of the various commands and functionalities.



## View player list:

When a user inputs the command _V_ a list will be displayed of all the players who has been added to the player list, the list contains the players lastname, player ID, club and their rating. 

## Edit a player: 

When a user inpts the command _E_ a page asking the user to choose either to search for a player by name or ID. If the information typed in does not exist, an error message will appear telling the user that no player with such name or ID exists. 

If the player with such name or ID, does in fact exist, the user will be given the choise as to what they want to edit either firstname, lastname, club, rating or the Player ID. 

Finally after the player has been edited, the user will be asked if they would like to edit another player, if they do wish to edit another, simply input 1, if not input 2.


## Add a player

To add a new player simply input _A_. The user will be asked to enter the players ID between 0 and 10000. After entering a valid player ID, the user has to enter the players lastname, firstname, rating between 1 and 3000 and the players club.


## Delete player

If A player has dropped out or has not showed up, the user has the ability to delete this player from the tournament with this command, enter _D_ and a page will show up asking you to choose between searching by name or ID. If the user exists then they will be displayed and the user will be asked to double check that it is the right player. If it's the right player, you can either enter 1 to delete said player or enter 2 to dismiss and not delete the player.


## Start the first round

To start the tournament the user uses the _F_ command, this will start to match up players as long as there are enough players and tabels dedicated to the tournament, if not the user will get an error message telleing them to either add/remove tabels or playes.

The program starts by pairing up different players on tables and allocating them to either start as white pieces or black ones, they also get a table number.

After the players has been given a color and a table the user has to enter the _N_ command which shows up only after starting the first round. When the _N_ command is entered the user will be given a choise to either enter 1 for white victory, 2 for black victory or 3 for a draw. After choosing the winner, the match results will be displayed, and the user will be forwarded back to the main menu.


## Start a new tournament

When entering _S_ to start a new tournament you will get the same messages as you did at the start of the program. You will be notified that if you wish to start a new tournament, all saved data for the previous tournament will be deleted. You will then go on to be asked the same questions as earlier:

- how many tables wil be at the tournament, choose between 1 and 1000.

- choose how many rounds should be in the tournament, choose between 1 and 20.

And then finally you wil be brought back to the main menu again.

## Saving the data

All data that is added during theuse of the program will be saved on 2 different files;

- PlayerList.dta
- tournamentData.dta

the different players will be stores in the PlayerList.dta file, and the tournament data such as amout of tables, nuber of rounds and who sarted as white and who started as black.