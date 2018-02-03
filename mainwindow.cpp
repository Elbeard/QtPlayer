#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>
#include <math.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->openButton,SIGNAL(clicked(bool)), this, SLOT(load_song()));


    //Create systemtray icon
//        ticon = new QSystemTrayIcon(this);
//        ticon->setIcon(QIcon(":/icons/*.svg"));
//        ticon->show();

    //Connects positionbars valueChanged signal to a slot that enables mouse clicking in the slider.
//    connect(ui->progressSlider, SIGNAL(valueChanged(int)),
//            this, SLOT(progressSliderValueChanged(int)));

    //Timer that surveys when update functions are executed. This is done in order to reduce processor usage.
    QTimer *ptimer = new QTimer(this);
    ptimer->start(5);
    connect(ptimer, SIGNAL(timeout()), this, SLOT(update_Slider()));
//    connect(ptimer, SIGNAL(timeout()), this, SLOT(update_Volumeknob()));
//    connect(ptimer, SIGNAL(timeout()), this, SLOT(change_Buttons()));
    connect(ptimer, SIGNAL(timeout()), this, SLOT(update_Time()));
//    connect(ptimer, SIGNAL(timeout()), this, SLOT(update_currentPlayList()));

    //Sets up the player according to the loaded settings
//    lastvolume = settings.getVolume() / 100.0;

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update_Time()
{
    if(player->stream != 0)
    {
        //Some QString declarations
        QString shours;
        QString sminutes;
        QString sseconds;
        QString stseconds;
        QString stminutes;
        QString sthours;

        //Let's fetch our data, first the total time and then the current time of sound we're playing
        QWORD tlen=BASS_ChannelGetLength(player->stream, BASS_POS_BYTE);
        QWORD len=BASS_ChannelGetPosition(player->stream, BASS_POS_BYTE);

        /*---------TOTAL TIME TRANSFORMATION-------------*/
        double dttime=BASS_ChannelBytes2Seconds(player->stream, tlen);
        int ttime = dttime;
        int thours = ttime / 3600;
        ttime %= 3600;
        int tminutes = ttime / 60;
        ttime %= 60;
        int tseconds = ttime;

        if(thours < 10) sthours = "0" + QString::number(thours);
        else sthours = QString::number(thours);
        if(tminutes < 10) stminutes = "0" + QString::number(tminutes);
        else stminutes = QString::number(tminutes);
        if(tseconds < 10) stseconds = "0" + QString::number(tseconds);
        else stseconds = QString::number(tseconds);

        /*-----------CURRENT TIME TRANSFORMATION------------*/
        double dtime=BASS_ChannelBytes2Seconds(player->stream, len);
        int time = dtime;
        int hours = time / 3600;
        time %= 3600;
        int minutes = time / 60;
        time %= 60;
        int seconds = time;

        if(hours < 10) shours = "0" + QString::number(hours);
        else shours = QString::number(hours);
        if(minutes < 10) sminutes = "0" + QString::number(minutes);
        else sminutes = QString::number(minutes);
        if(seconds < 10) sseconds = "0" + QString::number(seconds);
        else sseconds = QString::number(seconds);

        //Put all the times to one huge QString and then put that QString into songTimeLabel
        QString stime = shours + ":" + sminutes + ":" + sseconds + "/" + sthours + ":" + stminutes + ":" + stseconds;
        ui->songTimeLabel->setText(stime);
    }
}

void MainWindow::update_Slider()
{
    if(player->stream != 0)
    {
        QWORD len=BASS_ChannelGetPosition(player->stream, BASS_POS_BYTE);
        double dtime=BASS_ChannelBytes2Seconds(player->stream, len);
        int time = dtime * 10;
        ui->progressSlider->setValue(time);
    }
}



void MainWindow::on_openButton_clicked()
{
    if(player->stream != 0)
        BASS_StreamFree(player->stream);
    player->OpenFile();
}

void MainWindow::load_song()
{
    //Read the total length of a song and store it into the slider
    QWORD len=BASS_ChannelGetLength(player->stream, BASS_POS_BYTE);
    double dtime=BASS_ChannelBytes2Seconds(player->stream, len);
    int time = dtime * 10;
    ui->progressSlider->setMaximum(time);
    player->isPlaying = FALSE;
}

void MainWindow::on_playButton_clicked()
{
    player->Play();
}

void MainWindow::on_stopButton_clicked()
{
    player->StopPlaying();
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    player->SetLoop();
}



void MainWindow::on_volumeSlider_sliderMoved(int position)
{
    player->SetVolume(position);
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    player->SetVolume(value);
}

void MainWindow::on_progressSlider_sliderMoved(int position)
{
    if(player->stream != 0)
    {
        double pos = position / 10;
        QWORD time = BASS_ChannelSeconds2Bytes(player->stream, pos);
        BASS_ChannelSetPosition(player->stream, time, BASS_POS_BYTE);
    }
}

void MainWindow::on_progressSlider_sliderPressed()
{
    if(player->stream != 0) BASS_ChannelPause(player->stream);
}

void MainWindow::on_progressSlider_sliderReleased()
{
    if(player->stream != 0) BASS_ChannelPlay(player->stream, 0);
}

void MainWindow::on_progressSlider_valueChanged(int value)
{
    if (this->isActiveWindow())
    {
        // Make slider to follow the mouse directly and not by pageStep steps
        Qt::MouseButtons btns = QApplication::mouseButtons();
        QPoint localMousePos = ui->progressSlider->mapFromGlobal(QCursor::pos());
        bool clickOnSlider = (btns & Qt::LeftButton) &&
                             (localMousePos.x() >= 0 &&
                              localMousePos.y() >= 0 &&
                              localMousePos.x() < ui->progressSlider->size().width() &&
                              localMousePos.y() < ui->progressSlider->size().height());
        if (clickOnSlider)
        {
            // Attention! The following works only for Horizontal, Left-to-right sliders
            float posRatio = localMousePos.x() / (float )ui->progressSlider->size().width();
            int sliderRange = ui->progressSlider->maximum() - ui->progressSlider->minimum();
            int sliderPosUnderMouse = ui->progressSlider->minimum() + sliderRange * posRatio;
            if (sliderPosUnderMouse != value)
            {
                if(player->stream != 0) BASS_ChannelPause(player->stream);

                ui->progressSlider->setValue(sliderPosUnderMouse);

                if(player->stream != 0){
                    double pos = sliderPosUnderMouse / 10;
                    QWORD time = BASS_ChannelSeconds2Bytes(player->stream, pos);
                    BASS_ChannelSetPosition(player->stream, time, BASS_POS_BYTE);
                }

                if(player->stream != 0) BASS_ChannelPlay(player->stream, false);

                return;
            }
        }
    }
}


