#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
<<<<<<< HEAD
#include <QLabel>
#include <QDebug>
#include<QGraphicsScene>
#include<QGraphicsView>
#include"game.h"
=======
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include "game.h"
>>>>>>> e1b351f58c7540dcd016904f890fae707e6f0ca0

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void mousePressEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);

private:
<<<<<<< HEAD
    Ui::MainWindow *ui;
    QGraphicsScene * scene;
    QGraphicsView * view;
    Game * othello;
    int currentPlayer;
=======
    Ui::MainWindow * ui;
    QGraphicsScene * scene;
    QGraphicsView * graphicView;
    Game * othello;
>>>>>>> e1b351f58c7540dcd016904f890fae707e6f0ca0
};

#endif // MAINWINDOW_H
