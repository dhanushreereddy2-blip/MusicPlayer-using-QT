#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>    // this header file will provide player->play();player->pause();,player->setSource();,player->setPosition();
#include <QAudioOutput>  //control volume
#include <QStringList> //store songlist

#include <QMediaMetaData>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_prev_clicked();
    void on_play_clicked(bool checked);
    void on_Next_clicked();

    void on_horizontalSlider_sliderMoved(int position);
    void on_horizontalSlider_2_valueChanged(int value);


    //QMediaPlayer signals in mainwindow.cpp:
    void onDurationChanged(qint64 duration);
    void onPositionChanged(qint64 position);

    //Additional when one song finishes immediately it starts another song
    void onMediaStatusChanged(QMediaPlayer::MediaStatus status);

private:
    Ui::MainWindow *ui;

    QMediaPlayer *player;
    QAudioOutput *audioOutput;
    int currentIndex;
    QStringList songList;


   void loadSongs();

    QString formatTime(qint64 ms);

    void updateSongInfo();

};
#endif // MAINWINDOW_H
