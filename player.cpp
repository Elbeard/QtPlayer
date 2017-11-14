#include "player.h"
#include "bass.h"
#include <QMessageBox>
#include <stdio.h>

Player::Player(QObject *parent) : QObject(parent)
{
    filename = "C:/Qt/QtProg/5.mp3";

    // check the correct BASS was loaded
        if (HIWORD(BASS_GetVersion())!=BASSVERSION)
            printf("An incorrect version of BASS was loaded");

    // initialize output device
        if (!BASS_Init(-1,44100,0,0,NULL))
            Error("Can't initialize device");
        else {
            Error("BASS is successful initialaze\n");
        }

        HSTREAM stream=BASS_StreamCreateFile(FALSE, filename, 0, 0,BASS_SAMPLE_LOOP);
        if(BASS_ErrorGetCode() != BASS_OK){
            Error("Stream error\n");
        }

        // play the music (continue from current position)
        if (!BASS_ChannelPlay(stream,FALSE))
            Error("Can't play music");
}

void Player::Error(QString text)
{
    QMessageBox *mb = new QMessageBox;
    mb->setWindowTitle("Ошибка");
    mb->setText(text);
    mb->exec();
    //printf("Error(%d): %s\n",BASS_ErrorGetCode(),text);
    //BASS_Free();
    //exit(0);
}

Player::~Player()
{
    BASS_Free();
}
