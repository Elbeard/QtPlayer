#include "player.h"
#include "bass.h"

Player::Player(QObject *parent) : QObject(parent)
{
    //HSTREAM channel;

    BASS_Init(-1, 44100, 0, NULL, NULL);

    //if (!BASS_Init(-1, 44100, 0, NULL, NULL))
        //qDebug() << "Cannot initialize device"
        //qDebug("Cannot initialize device");

}

Player::~Player()
{
    BASS_Free();
}

void Player::play()
{
    //BASS_ChannelPlay(channel,FALSE);
}

void Player::loadFile(QString lf)
{
    //char filename[] = "‪C:\Qt\QtProg\5.mp3";
    //sample =BASS_SampleLoad(FALSE,filename, 0, 0,1, BASS_SAMPLE_3D | BASS_SAMPLE_LOOP );
    //channel = BASS_StreamCreateFile(false, str.toLocal8Bit().constData(), 0, 0, BASS_STREAM_AUTOFREE);

    //char *a = lf;

    channel = BASS_StreamCreateFile(FALSE, "‪C:\Qt\QtProg\5.mp3", 0, 0, 0);



}
