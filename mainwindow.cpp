#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setMouseTracking(true);
    QLabel * label = new QLabel(this);
}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->buttons() == Qt::LeftButton){
        QSize size = this->size();
        qDebug() << "Width: " << size.width() << " Height: " << size.height();
        qDebug() << event->pos();
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
