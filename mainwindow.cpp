#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    scene = new QGraphicsScene(this);
    othello = new Game(scene,this);
    othello->Display();
    ui->graphicsView->setScene(scene);

}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
        othello->Click(event->pos());
    }
}
void MainWindow::paintEvent(QPaintEvent * event)
{
    qDebug() << "Hello";
    othello->Display();
}
MainWindow::~MainWindow()
{
    delete ui;
}
