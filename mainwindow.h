#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <math.h>
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Player *player = new Player;

    // Коэффициент для преобразований в dBFS и обратно/ Ratio for changes in dBFS and back
    float DBFS_COEF = 20 / log(10);


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openButton_clicked();

    void on_playButton_clicked();

    void on_stopButton_clicked();

    void on_radioButton_clicked(bool checked);

    void on_volumeSlider_sliderMoved(int position);

    void on_volumeSlider_valueChanged(int value);

    void update_Time();

    void update_Slider();

    void load_song();

    void on_progressSlider_sliderMoved(int position);

    void on_progressSlider_sliderPressed();

    void on_progressSlider_sliderReleased();

    void on_progressSlider_valueChanged(int value);



private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
