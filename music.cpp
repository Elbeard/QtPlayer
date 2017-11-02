#include "music.h"
#include <windows.h>
//#include <conio.h> /* нужен для других примеров */
#include "bass.h" /* подключаем библиотеку импорта */

music::music(QObject *parent) : QObject(parent)
{
    BASS_Init (-1, 22050, 0 , NULL, NULL);

    HSAMPLE samp;		/*дескриптор сэмпла */
    HCHANNEL ch; 	/* дескриптор канала */

    /* загрузка звукового образца из файла*/
    samp =BASS_SampleLoad(FALSE,filename, 0, 0,1, NULL );

    /* создание канала воспроизведения */
    ch = BASS_SampleGetChannel(samp,FALSE);
    if (!ch) {
        /*... обработка ошибки */
        return 1;
    }
    /* воспроизводим звук */
    if (!BASS_ChannelPlay(ch,FALSE)) {
        /* ... обработка ошибки ... */
        return 1;
    }
    /* цикл, прерываемый по нажатию клавиши */
    while (!kbhit()) {
        if (pos.y > 10.0f) pos.y= -10.0f;
        else pos.y+= 0.2f;
        BASS_ChannelSet3DPosition (ch, &pos, NULL, NULL);
        BASS_Apply3D();
        Sleep (200);
    }
    /* остановка воспроизведения */
    BASS_ChannelStop(ch);
    /* освобождение ресурсов */
    BASS_SampleFree (samp);
}
