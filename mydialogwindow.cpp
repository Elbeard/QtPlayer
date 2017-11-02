#include "mydialogwindow.h"
#include "ui_mydialogwindow.h"
#include "music.h"
#include <QFileDialog>

MyDialogWindow::MyDialogWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyDialogWindow)
{
    ui->setupUi(this);

}

MyDialogWindow::~MyDialogWindow()
{
    delete ui;
}

void MyDialogWindow::on_OpenButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this);
    ui->label->setText(music.filename);
    music.filename = fileName;
}
