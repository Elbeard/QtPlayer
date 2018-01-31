#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*
void MainWindow::on_openButton_clicked()
{

}*/

void MainWindow::on_playButton_clicked()
{
    player->Play();
}

void MainWindow::on_stopButton_clicked()
{
    player->Error("Текст ошибки");
}
