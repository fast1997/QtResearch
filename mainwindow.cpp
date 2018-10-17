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

    othello = new Game(scene, view);
    othello->Init();
    othello->setUpDisplay();
    currentPlayer = 1;
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        qDebug() << "clicked";
        othello->Click(event->pos(),currentPlayer);
        currentPlayer = 3 - currentPlayer;

    }
}


//void MainWindow::paintEvent(QPaintEvent * event)
//{
//    QSize viewSize = view->size();
//    qDebug() << "Size of graphicview " << viewSize.width() << viewSize.height();
//    othello->updatedScreen();
//}

MainWindow::~MainWindow()
{
    delete ui;
}
