#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QTime>
#include <QThread>
#include <map>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);

    this->player = Player();
    this->simon = Simon(this->player);

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


void MainWindow::startClicked() {
    simon.setGameOver(false);
    simon.setColorList({});
    player.setScore(0);

    ui->scoreLabel->setText("0");\

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

        cout << i << endl;

        delay(333);

        showColor(i);
    }

    delay(333);

    ui->redButton->setDown(false);
    ui->greenButton->setDown(false);
    ui->blueButton->setDown(false);
    ui->yellowButton->setDown(false);

}


void MainWindow::colorClicked() {

    QPushButton* clickedColor = qobject_cast<QPushButton*>(sender());

    string selectedColor = clickedColor->text().toStdString();

    player.getPlayerList()->push_back(selectedColor);

    cout << "Player Color: " << selectedColor << endl;

    // if the player's currently selected color is not the same as simon's color at the same index in the list
    if (selectedColor != simon.getColorList()->at(player.getPlayerList()->size() - 1)) {
        simon.setGameOver(true);
    }

}

void MainWindow::playerInput() {

    cout << "Simon List: " << simon.getColorList()->size() << " | Player List: " << player.getPlayerList()->size() << endl;

    while (!(simon.getColorList()->size() == player.getPlayerList()->size())) {
        QApplication::processEvents();

        if (simon.getGameOver()) {
            player.setScore(*player.getScore() - 1);
            break;
        }
    }

}

void MainWindow::gameLoop() {
    while (!simon.getGameOver()) {

        chooseColor();

        showColors();

        playerInput();

        player.setPlayerList({});

        player.setScore(*player.getScore() + 1);
        string score = to_string(*player.getScore());

        if (*player.getScore() > *player.getHighscore()) {
            player.setHighscore(*player.getScore());
            ui->highscoreLabel->setText(QString::fromStdString(score));
        }

        cout << "Score: " << score << endl;

        ui->scoreLabel->setText(QString::fromStdString(score));

    }

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

    ui->redButton->setEnabled(false);
    ui->greenButton->setEnabled(false);
    ui->blueButton->setEnabled(false);
    ui->yellowButton->setEnabled(false);

    ui->startButton->show();

}
