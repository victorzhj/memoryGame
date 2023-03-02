/* Class Mainwindow
 * --------------------
 * COMP.CS.110 SPRING 2021
 * --------------------
 * Class for the memorygame gui and functionality.
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QtWidgets>
#include <iostream>
#include <player.hh>
#include <random>
#include <chrono>
#include <algorithm>
#include <fstream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

using name = std::string;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    // Destructor
    ~MainWindow();

private slots:
    /**
     * Method when card is pressed
     */
    void handle_card_clicked();
    /**
     * Method when START/RESET button is pressed
     */
    void on_sr_push_button_clicked();

private:
    Ui::MainWindow *ui;

    // All the possible cards characters
    const std::string ALL_CARD_CHARACTERS = "AABBCCDDEEFFGGHHIIJJ";

    // Constants for card push buttons
    const int MIN_CARD_A = 4;
    const int MAX_CARD_A = 20;
    const int CARD_WIDTH = 50;
    const int CARD_HEIGHT = 50;

    // Constants for card icons
    const int PICTURE_WIDTH = 50;
    const int PICTURE_HEIGTH = 75;

    // Constants for graphicsviews
    const int GRAPHICHSVIEW_LOC_X = 10;
    const int GRAPHICHSVIEW_LOC_Y = 10;
    const int RA_CARD_GRAPVIEW_WIDTH = 90;
    const int RA_CARD_GRAPVIEW_HEIGHT = 70;
    const int WA_CARD_GRAPVIEW_WIDTH = 500;
    const int WA_CARD_GRAPVIEW_HEIGHT = 100;

    // Constanst for warning label
    const int WARNING_LABEL_WIDTH = 200;
    const int WARNING_LABEL_HEIGHT = 50;

    // Timer update time
    const int SHOW_CARD_TIME = 1000;

    /**
     * Method checks if given card amount of correct
     * @return true if its acceptable
     * @return false if its not acceptable
     */
    bool check_card_amount();

    /**
     * Method calls every method needed to create the game board.
     * Also checks if its the first round.
     */
    void create_game_board();

    /**
     * Method creates a warning label when player gives non acceptable
     * amount of cards.
     */
    void create_warning();

    /**
     * Method calculates two highest numbers that the given card amount can
     * be divided.
     */
    void calc_highest_divisions();

    /**
     * Method creates a graphichsview and agridlayout where cards are put.
     * @param incorrect_amount. True if correct amount of cards are given
     *                          False if incorrect amount of cards are given
     */
    void set_card_layout(bool incorrect_amount);

    /**
     * Method randomizez the possible card characters.
     */
    void randomize_card_chac();

    /**
     * Method creates pushbutton cards that are then stored to QMap
     */
    void create_cards();

    /**
     * Add the players with given names if there are any. If theere aren't any
     * the program will give them default names (player 1, player2)
     */
    void add_player();

    /**
     * Set the whose_turn_label on the first round of the first match. This
     * method is more on incase if the player wants to set that the second
     * player starts the game.
     */
    void set_first_turn_label();

    /**
     * Method starts the timer
     */
    void start_timer();

    /**
     * Method updates the values of the ui timer
     */
    void update_timer();

    /**
     * Method stops the timer
     */
    void stop_timer();    

    /**
     * Method for the first card that is flipped.
     * @param coord. The coordinate of the character in the card_chac vector.
     */
    void first_card_flipped(int coord);

    /**
     * Method when the second card if flipped.
     * Disables all the card and checks if a pair was found.
     * @param c. The character of the second card.
     */
    void second_card_flipped(QChar c);

    /**
     * Method does the actions needed when a pair is found.
     */
    void pair_found();

    /**
     * Method checks if all the cards were found. If they were declare winner.
     */
    void check_winner();

    /**
     * Fucntion for when game ended in a tie.
     */
    void when_tie();

    /**
     * Method for when player 1 wins.
     */
    void when_p1_won();

    /**
     * Method for when player 2 wins.
     */
    void when_p2_won();

    /**
     * Method for switching turn.
     */
    void switch_turn();

    /**
     * Method enables all the card that were not found.
     */
    void enable_all_buttons();

    /**
     * Method hides the cards when no pair was found.
     */
    void hide_card();

    /**
     * Method clears the old game_board when START/RESET button is clicked.
     */
    void clear_board();

    /**
     * Method adds the found pair to the player and
     * increases their score by one.
     * @param c. The found pair(letter).
     */
    void add_card_to_player(QChar c);

    /**
     * Method updates the scoreboard when a pair is found.
     */
    void update_scoreboard();

    /**
     * Check if given file exist. If not it will creata scoreboard.txt file.
     */
    void find_file();

    /**
     * Method writes on the file after everyround.
     * @param winner. The winner of the round.
     */
    void write_file_score(std::string winner);

    // int values that are needed
    int amount_of_games_played_ = 0;
    int card_amount_;
    int column_amount_;
    int row_amount_;
    int flipped_amount_ = 0;
    int in_turn_ = 1;
    int ties_ = 0;

    // char value that is needed
    char first_card_char_;

    // bool value that is needed
    bool game_started_ = false;

    // Special values that are needed
    std::ofstream file_object_;
    std::vector<QPushButton*> found_cards_;
    std::vector<char> card_chac_;

    // QT values that are needed
    QTimer* timer_ = new QTimer(this);
    QGridLayout* gridlayout_cards_;
    QGraphicsView* graphicshview_cards_;
    QPushButton* first_card_;
    QPushButton* pressed_card_;
    QMap<QPushButton*, int> buttons_;

    Player* player1_;
    Player* player2_;
};
#endif // MAINWINDOW_HH
