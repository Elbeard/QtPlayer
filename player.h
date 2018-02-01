#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "bass.h"

class Player : public QObject
{
    Q_OBJECT
private:
public:
    bool isPlaying = FALSE;
    QString filename = NULL;
    HSTREAM stream = NULL;
    explicit Player(QObject *parent = nullptr);

    void Initialize();
    void Error(QString text);
    void Play();
    void OpenFile();
    void StopPlaying();

    ~Player();

    signals:

public slots:
};

#endif // PLAYER_H
