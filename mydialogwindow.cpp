#include "mydialogwindow.h"
#include "ui_mydialogwindow.h"
#include "player.h"
#include <QFileDialog>

MyDialogWindow::MyDialogWindow(QWidget *parent) : QDialog(parent),
    ui(new Ui::MyDialogWindow)
{
    ui->setupUi(this);

}

MyDialogWindow::~MyDialogWindow()
{
    delete ui;
}

    class Music;
void MyDialogWindow::on_OpenButton_clicked()
{
    QString filename = QFileDialog::getOpenFileName(this);
    ui->label->setText(filename);
    player->loadFile(filename);
}

void MyDialogWindow::on_PlayButton_clicked()
{
    player->play();
}
