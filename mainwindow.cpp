#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
<<<<<<< HEAD
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

=======
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
>>>>>>> e1b351f58c7540dcd016904f890fae707e6f0ca0
MainWindow::~MainWindow()
{
    delete ui;
}
