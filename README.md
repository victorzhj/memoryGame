This program creates a simple interactive memory game that is played by two person.

THE RULES:

1. The objective is to collect the most pairs of cards.

2. Player 1 goes first (this can be changed by going to mainwindown.hh and changing the in_turn to 2).

3. On each turn, a player turns over any two cards (one at a time) and keeps them if 
   the cards match (for instance two C were found).

4. If they successfully match a pair they get to keep the cards, and that player gets another turn.

5. When a player turns over two cards that do not match, those cards are turned face down again (in the same position) 
   and it becomes the next players turn.

6. The person with the most pairs at the end of the game wins.


HOW TO USE THE PROGRAM:

1. Start the program.

2. Give the amount of cards that you want to use (Min amount is 4, Max amount is 20, MUST BE A EVEN NUMBER!). 
   This can be done ether by typing the value to the spinbox or by clicking the spinbox arrows. 
   By clicking the arrows they go up by increment of 2. If given a non acceptable value the program will tell you about it.

3. Give player names by typing them on the scoreboard's lineEdits. If one or both lineEdits are left empty the program 
   will give the player default name Player 1 or Player 2. Names are not changeable after starting the game.

4. Give the file name that you want to store the game data. If no file is given the program will try to open a file 
   called scoreboard.txt and if no such file exist it will create it.

   Step 2, 3 and 4 doesn't need to be done in that exact order.

5. Start the game by clicking the START/RESET button and start clicking the cards.

6. To start a new round click START/RESET button. The last played player starts in the next round.

7. If you are done with the game press the x on the top right or the QUIT button.


Explaining some features:

Scoreboard: Tells whose turn is it right now. Shows the amount of cards that the player has gotten on that round 
            and what cards they have gotten. Also shows how many rounds they have won and how many ties there has been.

Announcer_label (the label under the scoreboard): Tells who won the round or if it was tie.

Timer: Shows the time that the round took.


Documentation:

The flow:
When player gives a int of how many cards to play and presses start/reset button the program will check if the given card amount is valid (check_card_amount). If the amount isn't valid program will say "wrong amount of cards" (create_warning). If its valit the program will jump create_game_board method that calls all the methods needed to create the gameboard. Depending if it's the first game or not the program will create the players (add_player) and take the given file name (find_file). It will also start the timer.

When creating the game board the program first calculates the row and column value (calc_highest_divisions) and then create the needed layouts for the cards (set_card_layouts). After that it will create a vector containing letters in random order (randomize_card_chac) and create the actual pushbutton cards (create_cards).

Now when a game is going. The card amount cannot be changed. Why? Honestly I just felt like adding it. This can be undone by removing the line 66 in mainwindow.cpp.

After that the user can press a card. When a card is pressed handle_card_clicked method that the buttons are connected will show the letter and check if it's the first flipped card or the second flipped card. If it's the first card it will call the first_card_flipped method that will store the first cards letter. If it's the second card the program will disable all the cards and check if a pair was found. If pair was found increase the players score by one, add the card to player (add_card_to_player) and update the scoreboard (update_scoreboard). The program will also store the found pair to a vector so that they won't be enabled again. Each time a pair is found the program will check if there is a winner (check_winner) by checking if all the cards have been flipped. If all the cards are flipped and there is no winner the program will declare tie and if there is a winner the program will increase their won match amount (add_round_won). If all the pairs haven't been found the program will enable the cards back (enable_all_buttons).

Everytime a pair is not found the program will switch the guessers turn (switch_turn) and hide the guessed cards (hide_card).

After all the pairs have been found the program will write that data to a text file (write_file_score) and update the scoreboard.

If player clicks the start/reset button again. The program will call the clear_board function that clears the old board and resets the round scores.


Some explanations of my though process:

Why QPushbuttons as cards?
* Felt like they were a great option for this. Being able to click the cards gives a real life feeling.

Why put the cards inside a gridlayout?
* Gridlayout makes it easier to place the cards on the right spot

Why place gridlayout inside a graphicsview?
* I just felt like it's easier to look at the cards.

Why store the buttons inside a QMap?
* I needed to store the buttons with their coordinates to point to the cards letter. QMap did just that.

Why only two players?
* Honestly I was too lazy so I went with it. If I wanted to change it now. I would need to redo so many methods
* and I don't feel like doing it.

Why QIcon and not Qpixemap?
* I wasn't sure how to get rid of the picture when showing the card letter when using QPixelmap.
* So I went with the QIcon as in QT documentation there was an example code on how to get rid of the icon when
* needed.


Additional features for additional points:

2. User can give players names.

4. The program tells what cards the player has gotten.

5. There is timer that shows the round time in realtime.

6. Cards can be changed on the fly meaning that you don't need to restart the program to change the card amount

7. Program has a scoreboard that and those scores can be saved to file. Program is incapable of reading 
   a file to continue from the last game. Not exacly what was required as I misunderstood what part 7. of additional features ment. 
   Still putting it here incase I get some compassion points.
 
8. There is a picture on the front side of each card. The picture should be copyright free.


