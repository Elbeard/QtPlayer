#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

class player : public QObject
{
    Q_OBJECT
public:
    explicit player(QObject *parent = nullptr);

signals:

public slots:
};

#endif // PLAYER_H