#include "mydialogwindow.h"
//#include "music.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MyDialogWindow *win = new MyDialogWindow();

    win->show();
    return app.exec();
}
