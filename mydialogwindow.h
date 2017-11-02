#ifndef MYDIALOGWINDOW_H
#define MYDIALOGWINDOW_H

#include <QDialog>

namespace Ui {
class MyDialogWindow;
}

class MyDialogWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MyDialogWindow(QWidget *parent = 0);
    ~MyDialogWindow();

private:
    Ui::MyDialogWindow *ui;

private slots:
    void on_OpenButton_clicked();
};

#endif // MYDIALOGWINDOW_H
