#include "mydialogwindow.h"
#include "bass.h"
#include <QApplication>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    MyDialogWindow *win = new MyDialogWindow();

    BASS_Init(-1,44100,0,0,NULL);

    //HSAMPLE samp;		/*дескриптор сэмпла */
    //HCHANNEL ch; 	/* дескриптор канала */

    //char filename[] = "‪C:\Qt\QtProg\5.mp3";

    win->show();
    return app.exec();
}
