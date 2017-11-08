#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "bass.h"

class Player : public QObject
{
    Q_OBJECT
private:
    bool isPlaying;
    float volume;

    HSAMPLE sample;
    HSTREAM channel;

    static Player* player;
public:
    explicit Player(QObject *parent = nullptr);
    ~Player();

    void loadFile(QString lf);

signals:

public slots:
    void play();
    //void pause();
    //void nextSong();
    //void prevSong();
    //void setVolume(float vol);
};

#endif // PLAYER_H
