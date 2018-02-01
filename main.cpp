#include <QApplication>
#include "mainwindow.h"
//#include "player.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

//    Player *player =new Player();

//    player->Initialize();

    w.show();
    a.exec();
  return 0;
}

