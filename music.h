#ifndef MUSIC_H
#define MUSIC_H

#include <QMainWindow>
#include <QObject>

class music : public QObject
{
    Q_OBJECT
public:
    explicit music(QObject *parent = nullptr);


    QString filename; /*переменная хранящая имя - адрес файла*/
    bool isPlaying;

signals:

public slots:
};

#endif // MUSIC_H
