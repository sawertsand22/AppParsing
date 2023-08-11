#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "qmessagebox.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    dataBase = new DataBase();
   // connect(dataBase,&DataBase::firstWindow,this,MainWindow::show());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonExit_2_clicked()
{
   QCoreApplication::quit();
}


void MainWindow::on_pushButtonConnection_clicked()
{

    dataBase->show();
    this->close();
}

