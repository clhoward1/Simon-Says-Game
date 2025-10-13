#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "simon.h"
#include <QMainWindow>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow { Q_OBJECT

    public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();


    private slots:
        void delay(int timeMilli);
        void startClicked();
        void colorClicked();
        void chooseColor();
        void showColor(int count);
        void showColors();
        void playerInput();
        void gameLoop();


    private:
        Ui::MainWindow *ui;
        Player player;
        Simon simon;
};
#endif // MAINWINDOW_H
