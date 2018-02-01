#include "player.h"
#include "bass.h"
#include <QMessageBox>
#include <QFileDialog>

Player::Player(QObject *parent) : QObject(parent)
{
    //filename = "C:/Qt/QtProg/5.mp3";

    this->Initialize();
}

Player::~Player()
{
    BASS_Free();
}

void Player::Initialize()
{
    // check the correct BASS was loaded
      if (HIWORD(BASS_GetVersion())!=BASSVERSION)
         this->Error("An incorrect version of BASS was loaded");

    //  output device
      if (!BASS_Init(-1,44100,0,0,NULL))
         this->Error("Can't initialize device");
     else{
         this->Error("BASS is successful initialaze\n");
         }
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

void Player::Play()
{
    if (!isPlaying)
    {
        // play the music (continue from current position)
        if (!BASS_ChannelPlay(stream,FALSE)){
            //this->Error("Can't play music");
            this->Error(QString::number(BASS_ErrorGetCode()));}
    }

    else
    {
        BASS_ChannelPause(stream);
    }

    isPlaying = !isPlaying;



}

void Player::OpenFile()
{
    filename = QFileDialog::getOpenFileName();

    /*
        Странное действие с переменной filename здесь это
        преобразование типа данных QString который даёт на выходе QFileDialog
        в тип char который может принять BASS_StreamCreateFile
    */

    stream = BASS_StreamCreateFile(FALSE, filename.toLocal8Bit().data(), 0, 0, NULL);
}

void Player::StopPlaying()
{

    BASS_StreamFree(stream);
    isPlaying = FALSE;
}



