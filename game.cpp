#include <QtGui>
#include <QDebug>
#include <QRect>
#include "game.h"

QLabel *labelTable[1000];

Game::Game(QWidget *parent) :
    QWidget(parent),
    midi("")
{
    QPixmap panel(":/images/panel.png");
    QLabel *panelLabel = new QLabel(this);
    panelLabel->setPixmap(panel);
    panelLabel->setGeometry(0, 149, 800, 179);
    panelLabel->show();

    QPixmap dong(":/images/dong.png");
    for (int i = 0; i < 100; i++)
    {
        QLabel *label = new QLabel(this);
        label->setPixmap(dong);
        label->setGeometry(i * 60, 175, 80, 80);
        label->show();
        labelTable[i] = label;
    }

    pressing_don = false;
    pressing_katsu = false;

    don_sound = new Phonon::MediaObject(this);
    don_sound_output =
        new Phonon::AudioOutput(Phonon::MusicCategory, this);
    createPath(don_sound, don_sound_output);
    don_sound_output->setVolume(1.0);

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->setInterval(17);
    timer->start();

    setFocus();
}

void Game::update()
{
    for (int i = 0; i < 100; i++)
    {
        QRect geom = labelTable[i]->geometry();
        geom.adjust(-2, 0, -2, 0);
        labelTable[i]->setGeometry(geom);
    }
}

void Game::setMidi(Midi new_midi)
{
    midi = new_midi;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_V or event->key() == Qt::Key_B or event->key() == Qt::Key_N)
    {
        Phonon::MediaObject *don_sound = new Phonon::MediaObject(this);
        Phonon::createPath(don_sound, new Phonon::AudioOutput(Phonon::MusicCategory, this));
        don_sound->setCurrentSource(Phonon::MediaSource(":/sounds/com_don.m4a"));
        don_sound->play();
    }
    else if (event->key() == Qt::Key_C or event->key() == Qt::Key_M)
    {
        Phonon::MediaObject *katsu_sound = new Phonon::MediaObject(this);
        Phonon::createPath(katsu_sound, new Phonon::AudioOutput(Phonon::MusicCategory, this));
        katsu_sound->setCurrentSource(Phonon::MediaSource(":/sounds/com_katsu.m4a"));
        katsu_sound->play();
    }
}
