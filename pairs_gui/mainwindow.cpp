/* Class mainwindow
 * ----------
 * COMP.CS.110 SPRING 2021
 * ----------
 * The cpp file of mainwindow where everything happens.
 * For more details on what these methods are read the
 * mainwindow.hh file.
 * */

#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(timer_, &QTimer::timeout, this, &MainWindow::update_timer);
}

MainWindow::~MainWindow()
{
    file_object_.close();
    delete player1_;
    delete player2_;
    delete ui;
}

void MainWindow::handle_card_clicked()
{
    // Take the button that was pressed and store it.
    pressed_card_ = static_cast<QPushButton*>(sender());
    // Take the coordinate value of the pressed card.
    int coord = buttons_.value(static_cast<QPushButton*>(sender()));
    QChar c = card_chac_.at(coord);
    // Reveal the card letter.
    pressed_card_->setText(c);
    pressed_card_->setIcon(QIcon());

    // Check if there is already one card flipped.
    if(flipped_amount_ == 0)
    {
        first_card_flipped(coord);
    }
    else if (flipped_amount_ == 1)
    {
        second_card_flipped(c);
    }
}

void MainWindow::on_sr_push_button_clicked()
{
    // Check if its the first game.
    if (game_started_ == true)
    {
        clear_board();
    }
    // Init game_board.
    if(check_card_amount())
    {
        ui->card_amount_spinbox->setDisabled(true);
        create_game_board();
        set_first_turn_label();
        game_started_ = true;
        start_timer();
    }
}

bool MainWindow::check_card_amount()
{
    card_amount_ = ui->card_amount_spinbox->value();

    if (card_amount_ < MIN_CARD_A or
        card_amount_ % 2 != 0 or
        card_amount_ > MAX_CARD_A)
    {
        create_warning();
        return false;
    }
    else
    {
        return true;
    }
}

void MainWindow::create_game_board()
{
    // Check if its the first game.
    if(game_started_ == false)
    {
        add_player();
        find_file();
        ui->file_name_lineedit->setDisabled(true);
    }

    calc_highest_divisions();
    set_card_layout(false);
    randomize_card_chac();
    create_cards();
}

void MainWindow::create_warning()
{
    set_card_layout(true);
    QSize label_size = QSize(WARNING_LABEL_WIDTH, WARNING_LABEL_HEIGHT);
    QLabel* warning = new QLabel("WRONG AMOUNT OF CARDS");
    warning->setFixedSize(label_size);
    gridlayout_cards_->addWidget(warning);
}

void MainWindow::calc_highest_divisions()
{
    int temp1 = 1;
    int temp2 = 1;

    for (int i = 1; i < card_amount_ / 2; ++i )
    {
        // Check if card can be divided with a certain number.
        if (card_amount_ % i == 0)
        {
            temp1 = i;
            // Check if divided number is larger than already known number.
            if (abs(card_amount_ / temp2 - temp2) >
                abs(card_amount_ /temp1 - temp1))
            {
                temp2 = temp1;
            }
        }
    }
    // Give column_amount_ the bigger number.
    if (card_amount_ / temp2 < temp2)
    {
        column_amount_ = temp2;
        row_amount_ = card_amount_ / temp2;
    }
    else
    {
        row_amount_ = temp2;
        column_amount_ = card_amount_ / temp2;
    }
}

void MainWindow::set_card_layout(bool incorret_amount)
{
    graphicshview_cards_ = new QGraphicsView(this);
    if(incorret_amount)
    {
        graphicshview_cards_->setGeometry(GRAPHICHSVIEW_LOC_X,
                                          GRAPHICHSVIEW_LOC_Y,
                                          WA_CARD_GRAPVIEW_WIDTH,
                                          WA_CARD_GRAPVIEW_HEIGHT);
    }
    else
    {
        graphicshview_cards_->setGeometry(GRAPHICHSVIEW_LOC_X,
                                          GRAPHICHSVIEW_LOC_Y,
                                          RA_CARD_GRAPVIEW_WIDTH*column_amount_,
                                          RA_CARD_GRAPVIEW_HEIGHT*row_amount_);
    }
    gridlayout_cards_ = new QGridLayout(graphicshview_cards_);
    graphicshview_cards_->show();
}

void MainWindow::randomize_card_chac()
{
    std::string card_characters = ALL_CARD_CHARACTERS.substr(0,card_amount_);

    std::string::iterator first = card_characters.begin();
    std::string::iterator end = card_characters.end();

    // Using system time as a seed.
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(first,end,std::default_random_engine(seed));

    for(char c : card_characters)
    {
        card_chac_.push_back(c);
    }
}

void MainWindow::create_cards()
{
    // Coordinate for the card character.
    int coord = 0;
    QSize card_size = QSize(CARD_WIDTH, CARD_HEIGHT);
    QSize picture_size = QSize(PICTURE_WIDTH, PICTURE_HEIGTH);
    QIcon front_side(":/bicyle.jpg");

    for(int row = 0; row < row_amount_; ++row)
    {
        for(int column = 0; column < column_amount_; ++column)
        {
            QPushButton* button = new QPushButton();

            button->setIcon(front_side);
            button->setIconSize(picture_size);
            // Store the button to QMap.
            buttons_.insert(button,coord);

            button->setFixedSize(card_size);
            // Add the button to gridlayout.
            gridlayout_cards_->addWidget(button,row,column);
            connect(button, &QPushButton::clicked,
                    this, &MainWindow::handle_card_clicked);

            coord++;
        }
    }
}

void MainWindow::add_player()
{
    // Create first player.
    if (ui->p1_name_lineedit->text().isEmpty())
    {
        // Set default name to player 1 if no name is given.
        player1_ = new Player("Player 1");
        ui->p1_name_lineedit->setText("Player 1");
    }
    else
    {
        QString p1_name = ui->p1_name_lineedit->text();
        player1_ = new Player(p1_name);
    }

    // Create second player.
    if (ui->p2_name_lineedit->text().isEmpty())
    {
        // Set default name to player 2 if no name is given.
        player2_ = new Player("Player 2");
        ui->p2_name_lineedit->setText("Player 2");
    }
    else
    {
        QString p2_name = ui->p2_name_lineedit->text();
        player2_ = new Player(p2_name);
    }
    ui->pname_label->setText("Player names");
    ui->p1_name_lineedit->setDisabled(true);
    ui->p2_name_lineedit->setDisabled(true);
}

void MainWindow::set_first_turn_label()
{
    if (in_turn_ == 1)
    {
        ui->whose_turn_label->setText(player1_->get_name());
    }
    else
    {
        ui->whose_turn_label->setText(player2_->get_name());
    }
}

void MainWindow::start_timer()
{
    timer_->start(1000);
}

void MainWindow::update_timer()
{
    int current_mins = ui->min_lcd->intValue();
    int current_sec = ui->sec_lcd->intValue();

    if(current_sec == 59)
    {
        ui->min_lcd->display(current_mins+1);
        ui->sec_lcd->display(0);
    }
    else
    {
        ui->sec_lcd->display(current_sec+1);
    }
}

void MainWindow::stop_timer()
{
    timer_->stop();
}

void MainWindow::first_card_flipped(int coord)
{
    pressed_card_->setDisabled(true);
    flipped_amount_ = 1;
    first_card_ = pressed_card_;;
    first_card_char_ = card_chac_.at(coord);
}

void MainWindow::second_card_flipped(QChar c)
{
    for (auto button : buttons_.keys())
    {
        button->setDisabled(true);
    }

    if (c == first_card_char_)
    {
        add_card_to_player(c);
        pair_found();
    }
    else
    {
        switch_turn();
        // Timer so that the cards are not instantly turned back.
        QTimer::singleShot(SHOW_CARD_TIME, this, &MainWindow::hide_card);
    }
    first_card_char_ = ' ';
    flipped_amount_ = 0;
}

void MainWindow::pair_found()
{
    // Store found cards.
    found_cards_.push_back(first_card_);
    found_cards_.push_back(pressed_card_);
    check_winner();
    // Timer so that the cards are not instantly enabled.
    QTimer::singleShot(SHOW_CARD_TIME, this, &MainWindow::enable_all_buttons);
}

void MainWindow::check_winner()
{
    size_t cards_stack_size = card_amount_;
    // Check if all the cards were found.
    if(found_cards_.size() == cards_stack_size)
    {
        amount_of_games_played_ += 1;
        stop_timer();
        // Check who won
        if(stoi(player1_->get_score()) == stoi(player2_->get_score()))
        {
            when_tie();
        }
        else if(stoi(player1_->get_score()) > stoi(player2_->get_score()))
        {
            when_p1_won();
        }
        else if(stoi(player1_->get_score()) < stoi(player2_->get_score()))
        {
            when_p2_won();
        }
        ui->card_amount_spinbox->setDisabled(false);
        player1_->reset_score();
        player2_->reset_score();
    }
}

void MainWindow::when_tie()
{
    // Write to file.
    write_file_score("No one. Was TIE");
    ties_ += 1;
    QString ties_amount = QString::fromStdString(std::to_string(ties_));
    ui->ties_label->setText(ties_amount);
    ui->announcer_label->setText("TIE");
}

void MainWindow::when_p1_won()
{
    ui->announcer_label->setText(player1_->get_name() + " won!");
    player1_->add_round_won();
    // Write to file.
    write_file_score(player1_->get_name().toStdString());
    QString p1_score = QString::fromStdString(
                player1_->get_match_score());

    ui->p1_match_score_label->setText(p1_score);
}

void MainWindow::when_p2_won()
{
    ui->announcer_label->setText(player2_->get_name() + " won!");
    player2_->add_round_won();
    // Write to file.
    write_file_score(player2_->get_name().toStdString());
    QString p2_score = QString::fromStdString(
                player2_->get_match_score());

    ui->p2_match_score_label->setText(p2_score);
}

void MainWindow::switch_turn()
{
    if(in_turn_ == 1)
    {
        in_turn_ = 2;
        ui->whose_turn_label->setText(player2_->get_name());
    }
    else if (in_turn_ == 2)
    {
        in_turn_ = 1;
        ui->whose_turn_label->setText(player1_->get_name());
    }
}

void MainWindow::enable_all_buttons()
{
    for (auto button : buttons_.keys())
    {
        // Check if the card was found already
        if(std::find(found_cards_.begin(), found_cards_.end(), button)
           == found_cards_.end())
        {
            button->setDisabled(false);
        }
    }
    first_card_ = nullptr;
}

void MainWindow::hide_card()
{
    QSize picture_size = QSize(PICTURE_WIDTH, PICTURE_HEIGTH);
    QIcon front_side(":/bicyle.jpg");
    QString empty = "";

    first_card_->setText(empty);
    first_card_->setIcon(front_side);
    first_card_->setIconSize(picture_size);

    pressed_card_->setText(empty);
    pressed_card_->setIcon(front_side);
    pressed_card_->setIconSize(picture_size);

    enable_all_buttons();
}

void MainWindow::clear_board()
{
    timer_->stop();
    ui->min_lcd->display(0);
    ui->sec_lcd->display(0);
    // Close the old graphicsview that had the old cards.
    graphicshview_cards_->close();
    found_cards_ = {};
    buttons_ = {};
    card_chac_ = {};

    // Easter egg.
    ui->announcer_label->setText("Have a nice summer");
    ui->p1_round_score_label->setText("0");
    ui->p2_round_score_label->setText("0");
    ui->p1_card_label->setText("");
    ui->p2_card_label->setText("");
}

void MainWindow::add_card_to_player(QChar qc)
{
    char c = qc.toLatin1();
    if(in_turn_ == 1)
    {
        player1_->add_score();
        player1_->add_card(c);
    }
    else
    {
        player2_->add_score();
        player2_->add_card(c);
    }
    update_scoreboard();
}

void MainWindow::update_scoreboard()
{
    if(in_turn_ == 1)
    {
        // Show the cards that the player has
        QString cards = QString::fromStdString(player1_->get_cards());
        ui->p1_card_label->setText(cards);
        // Show the player score
        QString score = QString::fromStdString(player1_->get_score());
        ui->p1_round_score_label->setText(score);
    }
    else
    {
        QString cards = QString::fromStdString(player2_->get_cards());
        ui->p2_card_label->setText(cards);

        QString score = QString::fromStdString(player2_->get_score());
        ui->p2_round_score_label->setText(score);
    }
}

void MainWindow::find_file()
{
    std::string file_name = ui->file_name_lineedit->text().toStdString();
    file_object_.open(file_name);
    if (!file_object_.is_open())
    {
        // Check if a file called scoreboard already exist incase this is the
        // Second time opening the game.
        file_object_.open("scoreboard.txt");

        if(!file_object_.is_open())
        {
            // Create a new file if no file is given.
            file_object_ = std::ofstream("scoreboard.txt");
        }
    }
}

void MainWindow::write_file_score(std::string winner)
{
    std::string p1_name = player1_->get_name().toStdString();
    std::string p2_name = player2_->get_name().toStdString();
    std::string min = std::to_string(ui->min_lcd->intValue());
    std::string sec = std::to_string(ui->sec_lcd->intValue());

    // For the first round.
    if(amount_of_games_played_ > 1)
    {
        file_object_ << std::endl;
    }
    file_object_ << "Game " << amount_of_games_played_  << ":" << std::endl
                 << "Winner: " << winner << "!" << " Game lasted: " << min
                 << " min and " << sec << " second."
                 << std::endl
                 << p1_name << " Score: " << player1_->get_score()
                 << ". Matches won: " << player1_->get_match_score() << std::endl
                 << std::endl
                 << p2_name << " Score: " << player2_->get_score()
                 << ". Matches won: " << player2_->get_match_score() << std::endl;
}
