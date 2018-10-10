#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    QSize size = this->size();
    scene = new QGraphicsScene(this);
    //scene->setSceneRect(0,0, size.width(), size.height());
    othello = new Game(scene);
    //graphicView = new QGraphicsView(scene, this);
    //graphicView->setSceneRect(0,0, size.width(), size.height());
    ui->graphicsView->setScene(scene);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton)
    {
        qDebug() << event->pos();
    }
}
void MainWindow::paintEvent(QPaintEvent * event)
{
    othello->Display(event);

}
MainWindow::~MainWindow()
{
    delete ui;
}
