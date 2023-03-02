/* Class Player
 * --------------------
 * COMP.CS.110 SPRING 2021
 * --------------------
 * Class for the players to store their data.
 * */

#ifndef PLAYER_HH
#define PLAYER_HH
#include <iostream>
#include <vector>
#include <QWidget>

class Player
{
public:
    Player(const QString name);
    /**
     * Add cards to player
     */
    void add_card(char c);
    /**
     * returns the cards that the player is holding
     */
    std::string get_cards();
    /**
     * Add score if won the round
     */
    void add_score();

    std::string get_score();
    /**
     * Return the amount of rounds won
     */
    std::string get_match_score();

    QString get_name();

    void add_round_won();

    void reset_score();


private:

    QString name_;
    int score_ = 0;
    int rounds_won_ = 0;
    std::string cards_ = "";
};

#endif // PLAYER_HH
