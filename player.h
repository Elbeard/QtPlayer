#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>
#include "bass.h"

class Player : public QObject
{
    Q_OBJECT
private: Player *player;
public:
    char *filename;
    explicit Player(QObject *parent = nullptr);
    void Play();
    void Error(QString text);
    void Initialize();
    ~Player();

    signals:

public slots:
};

#endif // PLAYER_H
