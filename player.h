#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "bass.h"
#include <math.h>

class Player : public QObject
{
    Q_OBJECT
private:
    //Ratio for changes in dBFS and back
    float DBFS_COEF = 20 / log(10);
public:
    bool isPlaying = FALSE;
    QString filename = NULL;
    HSTREAM stream = NULL;
    explicit Player(QObject *parent = nullptr);

    void Initialize();
    void Error(QString);
    void Play();
    void OpenFile();
    void StopPlaying();
    void SetLoop();
    void SetVolume(int);

    ~Player();

    signals:

public slots:
};

#endif // PLAYER_H
