#include <QtGui>
#include <QKeyEvent>
#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sound_menu = new Phonon::MediaObject(this);
    createPath(sound_menu, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    sound_menu->setCurrentSource(Phonon::MediaSource("/Users/yanzheng//workspace/Taiko-no-Tatsujin/songs/examination.mp3"));
    sound_menu->setTransitionTime(-270);
    sound_menu->play();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_playButton_clicked()
{
    QFrame *frame = new QFrame;
    frame->setObjectName("myframe");
    frame->resize(800, 600);
    frame->setStyleSheet("QFrame#myframe{border-image:url(/Users/yanzheng//workspace/Taiko-no-Tatsujin/images/background.jpg)}" );
    frame->show();
}

void MainWindow::on_exitButton_clicked()
{
    exit(0);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    ;
}
