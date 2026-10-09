#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QCoreApplication> //to find where your application is running
#include <QUrl>  //QMediaPlayer::setSource() expects a QUrl for the media source. Qt's documentation shows local media being supplied with QUrl::fromLocalFile(...).


MainWindow::MainWindow(QWidget *parent)  : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  Additional
    QPixmap pixmap(":/album.jpg");
    ui->label_image->setPixmap(pixmap);
    ui->label_image->setScaledContents(true);
    ui->label_image->setFixedSize(250,250);

    qDebug() << "Image loaded:" << !pixmap.isNull();
    //

    currentIndex = 0;

    ui->play->setCheckable(true);

    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this); //this is inbuilt inside the qt through this only we will get

    player->setAudioOutput(audioOutput);

    ui->start_duration->setText("00:00");
    ui->end_duration->setText("00:00");
    ui->horizontalSlider->setValue(0);

    ui->horizontalSlider_2->setValue(50);
    ui->volume_label->setText("50%");
    audioOutput->setVolume(0.5);

    loadSongs();

    if(!songList.isEmpty())
    {
        player->setSource(QUrl::fromLocalFile(songList.at(currentIndex)));
    }

    if(!songList.isEmpty())
    {
        QFileInfo fileInfo(songList.at(currentIndex));
        ui->label_song->setText(fileInfo.baseName());
        ui->label_artist->setText("Artist:Unknown Artist");
    }
   // Qt to call your two functions automatically when duration/position changes
     connect(player,&QMediaPlayer::durationChanged,this,&MainWindow::onDurationChanged);
     connect(player,&QMediaPlayer::positionChanged,this,&MainWindow::onPositionChanged);
     connect(player,&QMediaPlayer::mediaStatusChanged,this,&MainWindow::onMediaStatusChanged);

       //Debug
     // connect(player, &QMediaPlayer::errorOccurred, this,
     //         [](QMediaPlayer::Error error, const QString &errorString)
     //         {
     //             qDebug() << "PLAYER ERROR:" << error << errorString;
     //         });

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_prev_clicked()
{
    if(songList.isEmpty()) return;

    currentIndex--;
    if(currentIndex < 0)
        currentIndex = songList.size()-1;

    player->setSource(QUrl::fromLocalFile(songList.at(currentIndex)));

    QFileInfo fileInfo(songList.at(currentIndex));
    ui->label_song->setText(fileInfo.baseName());
    ui->label_artist->setText("Artist:Unknown Artist");

    player->play();

}
void MainWindow::on_play_clicked(bool checked)
{
    if(checked == false)
    {
        player->pause();
        ui->play->setText("Play");
       // ui->play->setCheckable(false);
    }
    else
    {
        player->play();
        ui->play->setText("Pause");
       // ui->play->setCheckable(true);
    }

}
void MainWindow::on_Next_clicked()
{
    if(songList.isEmpty()) return;

    currentIndex = (currentIndex+1) %songList.size();

    player->setSource(QUrl::fromLocalFile(songList.at(currentIndex)));
    QFileInfo fileInfo(songList.at(currentIndex));
    ui->label_song->setText(fileInfo.baseName());
    ui->label_artist->setText("Artist:Unknown Artist");

    player->play();
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if(status == QMediaPlayer::EndOfMedia)
    {
        currentIndex = (currentIndex + 1) % songList.size();

        player->setSource(QUrl::fromLocalFile(songList.at(currentIndex)));

        QFileInfo fileInfo(songList.at(currentIndex));
        ui->label_song->setText(fileInfo.baseName());

        player->play();
    }
}

void MainWindow::loadSongs()
{
    QDir musicDir("C:/Users/dhanu/Music");

    QStringList filters;
    filters <<"*.mp3" << "*.wav";

   // qDebug() <<filters;

    QFileInfoList files = musicDir.entryInfoList(filters,QDir::Files);

  //  qDebug() <<files;

    for(const QFileInfo &File :files)
    {
        songList.append(File.absoluteFilePath());
    }

    qDebug() <<songList;

}

QString MainWindow::formatTime(qint64 ms)
{
    int seconds = ms/1000;
    int minutes = seconds/60;
    seconds %= 60;

    return QString("%1:%2")
        .arg(minutes,2,10,QChar('0'))
        .arg(seconds,2,10,QChar('0'));
}

void MainWindow::onDurationChanged(qint64 duration)
{
    ui->horizontalSlider->setRange(0,duration);
    ui->end_duration->setText(formatTime(duration));
}

void MainWindow::onPositionChanged(qint64 position)
{
    ui->horizontalSlider->setValue(position);
    ui->start_duration->setText(formatTime(position));
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)  //song progess slider
{
    player->setPosition(position);
}


void MainWindow::on_horizontalSlider_2_valueChanged(int value)  //volume slider
{
    audioOutput->setVolume(value/100.0);

    //Display the volume percentage
    ui->volume_label->setText(QString::number(value) + "%");
}


void MainWindow::updateSongInfo()
{
    QFileInfo fileInfo(songList.at(currentIndex));
    ui->label_song->setText(fileInfo.baseName());

    QVariant artist = player->metaData().value(QMediaMetaData::Key::ContributingArtist);

    if(artist.isValid())
        ui->label_artist->setText("Artist: " + artist.toString());
    else
        ui->label_artist->setText("Artist: Unknown Artist");
}