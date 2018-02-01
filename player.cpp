#include "player.h"
#include "bass.h"
#include <QMessageBox>
#include <stdio.h>
#include <iostream>
using namespace std;


Player::Player(QObject *parent) : QObject(parent)
{
    filename = "C:/Qt/QtProg/5.mp3";

    this->Initialize();

    /*    HSTREAM stream=BASS_StreamCreateFile(FALSE, filename, 0, 0,BASS_SAMPLE_LOOP);
        if(BASS_ErrorGetCode() != BASS_OK){
            this->Error("Stream error\n");
        }

        // play the music (continue from current position)
        if (!BASS_ChannelPlay(stream,FALSE))
            this->Error("Can't play music");
     */
}

void Player::Play()
{
    //this->Error("PlayButton clicked"); // test PlayButton

    //stream = BASS_StreamCreateFile(TRUE, "c:/3.mp3", 0, 0,BASS_SAMPLE_LOOP);

    if (!BASS_StreamCreateFile(TRUE, "C:/3.mp3", 0, 0,BASS_SAMPLE_LOOP))

        //Здесь маленькая победа с преобразованием топов. (Решение заняло два вечера.)
        this->Error(QString::number(BASS_ErrorGetCode()));

//    if(BASS_ErrorGetCode() != BASS_OK){
//        this->Error("Stream error\n");
//    }

       // play the music (continue from current position)
       if (!BASS_ChannelPlay(stream,FALSE))
           this->Error("Can't play music");
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

void Player::Initialize()
{
    // check the correct BASS was loaded
      if (HIWORD(BASS_GetVersion())!=BASSVERSION)
         this->Error("An incorrect version of BASS was loaded");

    //  output device
      if (!BASS_Init(-1,44100,0,0,NULL))
         this->Error("Can't initialize device");
     /* else {
         this->Error("BASS is successful initialaze\n");
     }*/

}

Player::~Player()
{
    BASS_Free();
}
