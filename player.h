#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class Player : public QObject
{
    Q_OBJECT
public:
    char *filename;
    explicit Player(QObject *parent = nullptr);
    void Error(QString text);
    ~Player();

signals:

public slots:
};

#endif // PLAYER_H
