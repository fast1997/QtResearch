#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    scene = new QGraphicsScene();
    view = ui->graphicsView;
    view->setScene(scene);
    view->setHorizontalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    view->setVerticalScrollBarPolicy ( Qt::ScrollBarAlwaysOff );
    Game * othello = new Game(scene, view);
    currentPlayer = 1;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        othello->Click(event);
    }
}

void MainWindow::paintEvent(QPaintEvent * event)
{
    qDebug() << "called";

}

MainWindow::~MainWindow()
{
    delete ui;
}
