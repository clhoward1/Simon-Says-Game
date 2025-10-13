#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QThread>
#include <map>

// initial setup, creates player and simon objects and disables color buttons
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    this->player = Player();
    this->simon = Simon();

    ui->redButton->setEnabled(false);
    ui->greenButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    ui->yellowButton->setEnabled(false);
}

MainWindow::~MainWindow() {
    delete ui;
}

// thanks stackoverflow for a program delay that doesn't mess with gui stuff
void MainWindow::delay(int timeMilli) {
    QTime dieTime= QTime::currentTime().addMSecs(timeMilli);
    while (QTime::currentTime() < dieTime)
        QCoreApplication::processEvents(QEventLoop::AllEvents, 100);
}


// when player clicks the start button, reset variables, hide start button, enable color buttons, and start game loop
void MainWindow::startClicked() {
    simon.setGameOver(false);
    simon.setColorList({});
    player.setScore(0);

    ui->scoreLabel->setText("0");

    ui->startButton->hide();

    ui->redButton->setEnabled(true);
    ui->greenButton->setEnabled(true);
    ui->blueButton->setEnabled(true);
    ui->yellowButton->setEnabled(true);

    gameLoop();

}


// Gets random color to add to simon's list
void MainWindow::chooseColor() {
    simon.getColorList()->push_back(simon.chooseRandomColor());

    for (int i = 0; i < (int) simon.getColorList()->size(); i++) {
        cout << "color: " << simon.getColorList()->at(i) << endl;
    }

}


// lights up selected color button in simon's list
void MainWindow::showColor(int count) {

    string color = simon.getColorList()->at(count);

    map<string, int> colorMap;

    colorMap["red"] = 0;
    colorMap["green"] = 1;
    colorMap["blue"] = 2;
    colorMap["yellow"] = 3;

    int colorNum = colorMap[color];

    switch (colorNum) {
        case 0: // red
            ui->redButton->setDown(false);

            delay(333);

            ui->redButton->setDown(true);

            break;

        case 1: // green
            ui->greenButton->setDown(false);

            delay(333);

            ui->greenButton->setDown(true);

            break;

        case 2: // blue
            ui->blueButton->setDown(false);

            delay(333);

            ui->blueButton->setDown(true);

            break;

        case 3: // yellow
            ui->yellowButton->setDown(false);

            delay(333);

            ui->yellowButton->setDown(true);

            break;
    }

}


// goes through all colors and lights them up in order
void MainWindow::showColors() {

    ui->redButton->setDown(true);
    ui->greenButton->setDown(true);
    ui->blueButton->setDown(true);
    ui->yellowButton->setDown(true);

    delay(750);

    for (int i = 0; i < (int) simon.getColorList()->size(); ++i) {

        ui->redButton->setDown(true);
        ui->greenButton->setDown(true);
        ui->blueButton->setDown(true);
        ui->yellowButton->setDown(true);

        simon.setListCounter(i);

        // console output for testing purposes
        cout << "Showing: " << i << endl;

        delay(333);

        showColor(i);
    }

    delay(333);

    ui->redButton->setDown(false);
    ui->greenButton->setDown(false);
    ui->blueButton->setDown(false);
    ui->yellowButton->setDown(false);

}


// when player clicks a button, add it to player's input list
void MainWindow::colorClicked() {

    QPushButton* clickedColor = qobject_cast<QPushButton*>(sender());

    string selectedColor = clickedColor->text().toStdString(); // I put the name of the button in the text value so I know which button it is

    player.getPlayerList()->push_back(selectedColor);

    cout << "Player Selected: " << selectedColor << endl; // console output

    // if the player's currently selected color is not the same as simon's color at the same index in the list, game over
    if (selectedColor != simon.getColorList()->at(player.getPlayerList()->size() - 1)) {
        simon.setGameOver(true);
    }

}


// waits around for player to click buttons until they've either clicked the same amount as simon's list or lost the game
void MainWindow::playerInput() {

    // console outputs length of both simon and player's list to make sure each is correct
    cout << "Simon List: " << simon.getColorList()->size() << " | Player List: " << player.getPlayerList()->size() << endl;

    // while player's inputs is less than simon's list
    while (simon.getColorList()->size() > player.getPlayerList()->size()) {
        QApplication::processEvents();

        if (simon.getGameOver()) {
            player.setScore(*player.getScore() - 1);
            break;
        }
    }

}

// Behold, the central game loop
void MainWindow::gameLoop() {
    while (!simon.getGameOver()) {

        chooseColor(); // Simon chooses next color

        showColors(); // Colors light up in order

        playerInput(); // Waits for player to input

        player.setPlayerList({}); // resets player input list for next round

        // sets player score and highschore
        player.setScore(*player.getScore() + 1);
        string score = to_string(*player.getScore());

        if (*player.getScore() > *player.getHighscore()) {
            player.setHighscore(*player.getScore());
            ui->highscoreLabel->setText(QString::fromStdString(score));
        }

        cout << "Score: " << score << endl; // console output

        ui->scoreLabel->setText(QString::fromStdString(score));

    }

    // resets score label and flashes buttons on and off to show game over
    ui->scoreLabel->setText("0");

    delay(250);

    for (int i = 0; i < 4; i++) {
        ui->redButton->setDown(true);
        ui->greenButton->setDown(true);
        ui->blueButton->setDown(true);
        ui->yellowButton->setDown(true);

        delay(250);

        ui->redButton->setDown(false);
        ui->greenButton->setDown(false);
        ui->blueButton->setDown(false);
        ui->yellowButton->setDown(false);

        delay(250);
    }

    // disables buttons and shows start button
    ui->redButton->setEnabled(false);
    ui->greenButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    ui->yellowButton->setEnabled(false);

    ui->startButton->show();

}
