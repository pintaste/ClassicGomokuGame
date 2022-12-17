#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QPushButton>
#include <QTimer>
#include <QLabel>
#include "game.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern int moveX, moveY, lastX, lastY;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent* event);

    void PVP_mode();
    void PVA_mode();
    void AI_move();

private:
    Ui::MainWindow *ui;
    const int SINGLE_SIZE = 40;
    const int START_X = 20;
    const int START_Y = 40;
    const int MAX_X = START_X + SINGLE_SIZE * BOARD_SIZE;
    const int MAX_Y = START_Y + SINGLE_SIZE * BOARD_SIZE;
    const int ROW_SPACE = 30;
    const int COL_SPACE = 20;

    Game  * game;
    QLabel* label_game_type1;
    QLabel* label_game_type2;
    QLabel* label_game_state1;
    QLabel* label_game_state2;
    QPushButton * button_PVP;
    QPushButton * button_PVA;
    QPushButton * button_AVA;
    QPushButton * button_restart;
    QPushButton * button_exit;

};
#endif // MAINWINDOW_H
