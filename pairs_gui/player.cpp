/* Class Player
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * The cpp file of Player where everything happens.
 * For more details on what these methods are read the
 * Player.hh file.

 * */

#include "player.hh"

Player::Player(const QString name):
    name_(name)
{

}

void Player::add_card(char c)
{
    cards_ += c;
}

std::string Player::get_cards()
{
    return cards_;
}


void Player::add_score()
{
    score_ += 1;
}

std::string Player::get_score()
{
    return std::to_string(score_);
}

std::string Player::get_match_score()
{
    return std::to_string(rounds_won_);
}

QString Player::get_name()
{
    return name_;
}

void Player::add_round_won()
{
    rounds_won_ += 1;
}

void Player::reset_score()
{
    score_ = 0;
    cards_ = "";
}
