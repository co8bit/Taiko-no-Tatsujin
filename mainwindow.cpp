#include <QtGui>
#include <QKeyEvent>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "midi.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QSpacerItem *spacer = new QSpacerItem(0, -200);
    ui->verticalLayout->addItem(spacer);
    ui->verticalLayout->setAlignment(Qt::AlignCenter);

    setStyleSheet(QString("QMainWindow { background-image: url(:/images/title.png); } QPushButton { font-family: 'AvenirNext-Regular'; font-size: 40px; font-weight: bold; };"));

    sound_menu = new Phonon::MediaObject(this);
    Phonon::createPath(sound_menu, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    sound_menu->setCurrentSource(Phonon::MediaSource(":/sounds/don008.m4a"));
    QObject::connect(sound_menu, SIGNAL(aboutToFinish()), SLOT(menu_sound_finished()));
    sound_menu->setTransitionTime(-270);
    sound_menu->play();

    ui->songsList->setVisible(false);
    ui->songsList->setStyleSheet(QString("font-family: 'Avenir Next'; font-size: 40px; font-weight: bold;"));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(200);
    timer->start();

    setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update()
{
    if (bg_music != NULL && bg_music->state() == Phonon::PausedState)
    {
        setStyleSheet(QString("QMainWindow { background-image: url(:/images/title.png); } QPushButton { font-family: 'AvenirNext-Regular'; font-size: 40px; font-weight: bold; };"));
        show_buttons();
        bg_music = NULL;
    }
}

void MainWindow::menu_sound_finished()
{
    ;
}

void MainWindow::hide_buttons()
{
    ui->playButton->setVisible(false);
    ui->exitButton->setVisible(false);
}

void MainWindow::show_buttons()
{
    ui->playButton->setVisible(true);
    ui->exitButton->setVisible(true);
}

void MainWindow::on_playButton_clicked()
{
//    QFrame *frame = new QFrame;
//    frame->setObjectName("myframe");
//    frame->resize(800, 600);
//    frame->setStyleSheet("QFrame#myframe{border-image:url(/Users/yanzheng//workspace/Taiko-no-Tatsujin/images/background.jpg)}" );
//    frame->show();

//    QLabel *label = new QLabel;
//    QMovie *movie = new QMovie("/Users/yanzheng//workspace/Taiko-no-Tatsujin/images/background.jpg");
//    label->setMovie(movie);
//    movie->start();
//    label->show();
    hide_buttons();
    ui->songsList->setVisible(true);
    ui->songsList->setFocus();

    QDir dir_songs(":/songs");
    ui->songsList->clear();
    ui->songsList->addItems(dir_songs.entryList(QDir::Dirs | QDir::NoDotAndDotDot));
    if (ui->songsList->count() > 0)
        ui->songsList->setCurrentItem(ui->songsList->item(0));
}

void MainWindow::start_game(QString music_name)
{
    sound_menu->stop();

    QString song_path = ":/songs/" + music_name + "/song.mp3";
    bg_music = new Phonon::MediaObject(this);
    Phonon::createPath(bg_music, new Phonon::AudioOutput(Phonon::MusicCategory, this));
    bg_music->setCurrentSource(Phonon::MediaSource(song_path));

    QString midi_path = ":/songs/" + music_name + "/notes.tnt";
    Midi midi(midi_path);

    setStyleSheet(QString("QMainWindow { background-image: url(:/images/background.jpg); } QPushButton { font-family: 'AvenirNext-Regular'; font-size: 40px; font-weight: bold; };"));

    game = new Game(this);
    game->setMidi(midi);
    game->setBgMusic(bg_music);
    game->resize(this->size());
    game->show();
}

void MainWindow::on_exitButton_clicked()
{
    exit(0);
}

void MainWindow::on_songsList_itemDoubleClicked()
{
    ui->songsList->setVisible(false);
    start_game(ui->songsList->currentItem()->text());
}
