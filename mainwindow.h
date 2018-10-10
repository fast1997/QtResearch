#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QtCore>
#include <QtGui>
#include <QGraphicsView>
#include "game.h"

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
    Ui::MainWindow * ui;
    QGraphicsScene * scene;
    QGraphicsView * graphicView;
    Game * othello;
};

#endif // MAINWINDOW_H
