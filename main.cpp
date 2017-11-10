#include <stdio.h>
#include "bass.h"

void Error(const char *text)
{
    printf("Error(%d): %s\n",BASS_ErrorGetCode(),text);
    BASS_Free();
    exit(0);
}

int main(int argc, char *argv[])
{
    //HSTREAM chan;
    char *filename = "C:\Qt\QtProg\5.mp3";

    printf("Simple console mode BASS example : MOD/MPx/OGG/WAV player\n"
                "---------------------------------------------------------\n");

// check the correct BASS was loaded
    if (HIWORD(BASS_GetVersion())!=BASSVERSION)
        printf("An incorrect version of BASS was loaded");

// initialize output device
    if (!BASS_Init(-1,44100,0,0,NULL))
        Error("Can't initialize device");
    else {
        printf("BASS is successful initialaze\n");
    }

    printf("%s\n",filename);

    /*Convert filename to c char array so we can use it with BASS
    QByteArray temparr = file.toLocal8Bit(); //QString file в файле лежит адрес файла"C:\Qt\QtProg\5.mp3"
    char *cfile = temparr.data();*/

    HSTREAM stream=BASS_StreamCreateFile(FALSE, "5.mp3", 0, 0, 0);
    if(BASS_ErrorGetCode() != BASS_OK){
        Error("Stream error\n");
    }

    // play the music (continue from current position)
    if (!BASS_ChannelPlay(stream,FALSE))
        Error("Can't play music");
    /*else {
        BASS_ChannelPlay(stream,FALSE);
    }*/

  return 0;
}
/*
*   В консоли выводит
*   BASS is successful initialaze
*   C:QtQtProg.mp3
*   Error(2): Stream error
*/
