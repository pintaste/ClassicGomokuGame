#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QMessageBox>


int moveX = 0, moveY = 0, lastX = -1, lastY = -1;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(860,660);
    this->setWindowTitle("Classic Gomoku Game");
    game = new Game('1');

    // label: game mode
    label_game_type1 = new QLabel(this);
    label_game_type1->setText("Mode: ");
    label_game_type1->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE, START_Y, 85, 20);
    label_game_type1->show();
    label_game_type2 = new QLabel(this);
    QString game_type = "";
    if(game->get_game_type() == '1')
        game_type = "Player vs. Player";
    else if(game->get_game_type() == '2')
        game_type = "Player vs. AI";
    else if(game->get_game_type() == '3')
        game_type = "AI vs. AI";
    label_game_type2->setText(game_type);
    label_game_type2->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE * 4, START_Y, 120, 20);
    label_game_type2->show();

    // label : game progress
    label_game_state1 = new QLabel(this);
    label_game_state1->setText("Current: ");
    label_game_state1->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE, START_Y + ROW_SPACE, 85, 20);
    label_game_state1->show();
    label_game_state2 = new QLabel(this);
    label_game_state2->setText("Black's turn");
    label_game_state2->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE * 4, START_Y + ROW_SPACE, 85, 20);
    label_game_state2->show();

    // button: pvp
    button_PVP = new QPushButton(this);
    button_PVP->setText("Player vs. Player");
    button_PVP->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE*2, START_Y + ROW_SPACE*10, 120, 40);
    button_PVP->show();
    if(game->get_game_type() == '1') button_PVP->setEnabled(false);

    // button: pva
    button_PVA = new QPushButton(this);
    button_PVA->setText("Player vs. AI");
    button_PVA->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE*2, START_Y + ROW_SPACE*12, 120, 40);
    button_PVA->show();
    if(game->get_game_type() == '2') button_PVA->setEnabled(false);

    // button: ava
    button_AVA = new QPushButton(this);
    button_AVA->setText("AI vs. AI");
    button_AVA->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE*2, START_Y + ROW_SPACE*14, 120, 40);
    button_AVA->show();
    if(game->get_game_type() == '3') button_AVA->setEnabled(false);

    // button: restart
    button_restart = new QPushButton(this);
    button_restart->setText("Restart");
    button_restart->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE*2, START_Y + ROW_SPACE*16, 120, 40);
    button_restart->show();

    // button: exit
    button_exit = new QPushButton(this);
    button_exit->setText("Exit");
    button_exit->setGeometry(START_X + BOARD_SIZE * SINGLE_SIZE + COL_SPACE*2, START_Y + ROW_SPACE*18, 120, 40);
    button_exit->show();

    // connect the buttons
    (void)connect(button_PVP, &QPushButton::clicked, [=](){
        game->init_game('1');
        button_PVP->setEnabled(false);
        button_PVA->setEnabled(true);
        button_AVA->setEnabled(true);
        label_game_type2->setText("Player vs. Player");
        label_game_state2->setText("Black's turn");
        update();
    });

    (void)connect(button_PVA, &QPushButton::clicked, [=](){
        game->init_game('2');
        button_PVP->setEnabled(true);
        button_AVA->setEnabled(true);
        button_PVA->setEnabled(false);
        label_game_type2->setText("Player vs. AI");
        label_game_state2->setText("Black's turn");
        update();
    });

    (void)connect(button_AVA, &QPushButton::clicked, [=](){
        game->init_game('3');
        button_PVP->setEnabled(true);
        button_PVA->setEnabled(true);
        button_AVA->setEnabled(false);
        label_game_type2->setText("AI vs. AI");
        label_game_state2->setText("Black's turn");
        update();
    });

    (void)connect(button_restart, &QPushButton::clicked, [=](){
        game->init_game(game->get_game_type());
    });

    (void)connect(button_exit, &QPushButton::clicked, [=](){
        this->close();
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent* event){
    // drawing the board frame
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    this->setAutoFillBackground(true);
    QPalette palette; // backgroud color
    palette.setColor(QPalette::Window, QColor("#B1723C"));
    this->setPalette(palette);

    // handle the mouse movement
    centralWidget()->setMouseTracking(true);
    setMouseTracking(true);
    QPen pen = painter.pen();
    pen.setColor(QColor("#8D5822"));
    pen.setWidth(7);
    painter.setPen(pen);

    // brush borad inside color
    QBrush brush;
    brush.setColor(QColor("#EEC085"));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);
    painter.drawRect(START_X,START_Y,SINGLE_SIZE * BOARD_SIZE, SINGLE_SIZE * BOARD_SIZE);

    // drawing the checkerboard
    pen.setColor(Qt::black);
    pen.setWidth(1);
    painter.setPen(pen);
    for(int i = 0; i < BOARD_SIZE; ++i)
    {
        painter.drawLine(40+i*40,60,40+i*40,620); //vertical line，60 is the highest and 620 is the lowest
        painter.drawLine(40,60+i*40,600,60+i*40); //Horizontal line, 40 leftmost and 600 rightmost
    }

    // Draw the five black dots in the middle of the board
    brush.setColor(Qt::black);
    painter.setBrush(brush);
    painter.drawRect(155,175,10,10);
    painter.drawRect(475,175,10,10);
    painter.drawRect(155,495,10,10);
    painter.drawRect(475,495,10,10);
    painter.drawRect(315,335,10,10);

    // Debugging: draw the coordinates of the board
    for(int i=0; i < BOARD_SIZE; ++i){
        painter.drawText(QPoint(22, 70+i*40), QString::number(i));
        painter.drawText(QPoint(40+i*40, 55), QString::number(i));
    }

    // Loop through, draw stones
    painter.setPen(Qt::NoPen);
    for(int i=0; i < BOARD_SIZE; ++i){
        for(int j=0; j <BOARD_SIZE; ++j){
            if(game->get_stone(i,j) == FLAG_BLACK)
            {
                brush.setColor(Qt::black);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint((j+1)*40,(i+1)*40+20), 18, 18);
            }
            else if(game->get_stone(i,j) == FLAG_WHITE){
                brush.setColor(Qt::white);
                painter.setBrush(brush);
                painter.drawEllipse(QPoint((j+1)*40,(i+1)*40+20), 18, 18);
            }
        }
    }

    // Draw a red square
    pen.setColor(Qt::red);
    pen.setWidth(1);
    painter.setPen(pen);
    // qDebug() << "moveX: " << moveX << "moveY: " << moveY;
    painter.drawLine((moveX+1)*40-20,(moveY+1)*40,(moveX+1)*40-10,(moveY+1)*40);
    painter.drawLine((moveX+1)*40+20,(moveY+1)*40,(moveX+1)*40+10,(moveY+1)*40);
    painter.drawLine((moveX+1)*40-20,(moveY+1)*40+40,(moveX+1)*40-10,(moveY+1)*40+40);
    painter.drawLine((moveX+1)*40+20,(moveY+1)*40+40,(moveX+1)*40+10,(moveY+1)*40+40);
    painter.drawLine((moveX+1)*40-20,(moveY+1)*40,(moveX+1)*40-20,(moveY+1)*40+10);
    painter.drawLine((moveX+1)*40+20,(moveY+1)*40,(moveX+1)*40+20,(moveY+1)*40+10);
    painter.drawLine((moveX+1)*40-20,(moveY+1)*40+40,(moveX+1)*40-20,(moveY+1)*40+30);
    painter.drawLine((moveX+1)*40+20,(moveY+1)*40+40,(moveX+1)*40+20,(moveY+1)*40+30);

    // lastX, lastY record the position of the last drop
    // Draw a red cross at the last drop position
    if(lastX != -1 && lastY != -1){
        painter.drawLine((lastX+1)*40-6,(lastY+1)*40+20,(lastX+1)*40-1,(lastY+1)*40+20);
        painter.drawLine((lastX+1)*40+1,(lastY+1)*40+20,(lastX+1)*40+6,(lastY+1)*40+20);
        painter.drawLine((lastX+1)*40,(lastY+1)*40+14,(lastX+1)*40,(lastY+1)*40+19);
        painter.drawLine((lastX+1)*40,(lastY+1)*40+21,(lastX+1)*40,(lastY+1)*40+26);
    }

}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    // check the boundary
    if(event->position().x() < START_X || event->position().x() > MAX_X ||
       event->position().y() < START_Y || event->position().y() > MAX_Y)
        return;
    moveX = (event->position().x()-START_X)/SINGLE_SIZE;
    moveY = (event->position().y()-START_Y)/SINGLE_SIZE;
    // qDebug() << moveX << " " << moveY;
    update();
}

void MainWindow::mouseReleaseEvent(QMouseEvent* event){
    if(game->get_game_type() == '1'){
        PVP_mode();
    } else if(game->get_game_type() == '2'){
        PVP_mode();
        // timer for ai make move
        PVA_mode();
    } else if(game->get_game_type() == '3'){
        // timer for make move
        PVA_mode();
        PVA_mode();
    }
}

void MainWindow::PVP_mode(){
    char player = game->get_game_state();
    // qDebug() << player;
    int row = moveY;
    int col = moveX;
    if(game->is_vaild_position(row,col)){
        game->place_stone(player,row,col);
        if(game->get_game_state() == FLAG_BLACK){
            label_game_state2->setText("Black's turn");
        } else if(game->get_game_state() == FLAG_WHITE){
            label_game_state2->setText("White's turn");
        }
        lastX = col;
        lastY = row;
        update();

        if(game->is_winner(player,row,col) == true){
            QString msg;
            (player == FLAG_BLACK) ? msg = "Black Win!" : "White Win!";
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Congratulations!");
            msgBox.setText(msg+"\nAnother Game?");
            label_game_state2->setText(msg);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox:: No );
            if(msgBox.exec() == QMessageBox::Ok){
                game->init_game(game->get_game_type());
                update();
            }
        }
    }
}

void MainWindow::AI_move(){
    char player = game->get_game_state();
    pair<int,int> pos = game->get_next_move();
    int row = pos.first;
    int col = pos.second;
    if(game->is_vaild_position(row,col)){
        game->place_stone(player,row,col);
        if(game->get_game_state() == FLAG_BLACK){
            label_game_state2->setText("Black's turn");
        } else if(game->get_game_state() == FLAG_WHITE){
            label_game_state2->setText("White's turn");
        }
        lastX = col;
        lastY = row;
        update();

        if(game->is_winner(player,row,col) == true){
            QString msg;
            (player == FLAG_BLACK) ? msg = "Black Win!" : "White Win!";
            QMessageBox msgBox(this);
            msgBox.setWindowTitle("Congratulations!");
            msgBox.setText(msg+"\nAnother Game?");
            label_game_state2->setText(msg);
            msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox:: No );
            if(msgBox.exec() == QMessageBox::Ok){
                game->init_game(game->get_game_type());
                update();
            }
        }
    }
}

void MainWindow::PVA_mode(){
    char palyer = game->get_game_state();
    if(palyer == FLAG_BLACK){
        if(game->get_player_type(0) == 'h'){
            PVP_mode();
        } else if(game->get_player_type(0) == 'a'){
            AI_move();
        }
    } else if(palyer == FLAG_WHITE){
        if(game->get_player_type(1) == 'h'){
            PVP_mode();
        } else if(game->get_player_type(1) == 'a'){
            AI_move();
        }
    }
}
