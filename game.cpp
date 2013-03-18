#include <QtGui>
#include <QDebug>
#include <QRect>
#include "game.h"

QLabel *labelTable[100];
Phonon::MediaObject *phononTable[100];
int phononCounter = 0;

Game::Game(QWidget *parent) :
    QWidget(parent),
    midi("")
{
    QPixmap panel(":/images/panel.png");
    QLabel *panelLabel = new QLabel(this);
    panelLabel->setPixmap(panel);
    panelLabel->setGeometry(0, 149, 800, 179);
    panelLabel->show();

    QPixmap hit_don_left_pic(":/images/hit_don_left.png");
    hit_don_left_label = new QLabel(this);
    hit_don_left_label->setPixmap(hit_don_left_pic);
    hit_don_left_label->setGeometry(0, 150, 153, 178);
    hit_don_left_label->show();
    hit_don_left_label->setVisible(false);

    QPixmap hit_don_right_pic(":/images/hit_don_right.png");
    hit_don_right_label = new QLabel(this);
    hit_don_right_label->setPixmap(hit_don_right_pic);
    hit_don_right_label->setGeometry(0, 150, 153, 178);
    hit_don_right_label->show();
    hit_don_right_label->setVisible(false);

    QPixmap hit_katsu_left_pic(":/images/hit_katsu_left.png");
    hit_katsu_left_label = new QLabel(this);
    hit_katsu_left_label->setPixmap(hit_katsu_left_pic);
    hit_katsu_left_label->setGeometry(0, 138, 153, 178);
    hit_katsu_left_label->show();
    hit_katsu_left_label->setVisible(false);

    QPixmap hit_katsu_right_pic(":/images/hit_katsu_right.png");
    hit_katsu_right_label = new QLabel(this);
    hit_katsu_right_label->setPixmap(hit_katsu_right_pic);
    hit_katsu_right_label->setGeometry(0, 138, 153, 178);
    hit_katsu_right_label->show();
    hit_katsu_right_label->setVisible(false);

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

    for (int i = 0; i < 100; i++)
    {
        Phonon::MediaObject *phonon = new Phonon::MediaObject(this);
        Phonon::createPath(phonon, new Phonon::AudioOutput(Phonon::MusicCategory, this));
        phononTable[i] = phonon;
    }

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
        QLabel *label = labelTable[i];
        if (label->isVisible())
        {
            QRect geom = labelTable[i]->geometry();
            if (geom.x() < 50)
            {
                label->setVisible(false);
            }
            geom.adjust(-2, 0, -2, 0);
            labelTable[i]->setGeometry(geom);
        }
    }
}

void Game::setMidi(Midi new_midi)
{
    midi = new_midi;
}

void Game::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_G or event->key() == Qt::Key_H)
    {
        Phonon::MediaObject *don_sound = phononTable[phononCounter++];
        don_sound->setCurrentSource(Phonon::MediaSource(":/sounds/com_don.m4a"));
        don_sound->play();
        phononCounter %= 100;
        if (event->key() == Qt::Key_G)
        {
            hit_don_left_label->setVisible(true);
            QTimer::singleShot(200, this, SLOT(hideDonLeft()));
        }
        else
        {
            hit_don_right_label->setVisible(true);
            QTimer::singleShot(200, this, SLOT(hideDonRight()));
        }
    }
    else if (event->key() == Qt::Key_F or event->key() == Qt::Key_J)
    {
        Phonon::MediaObject *katsu_sound = phononTable[phononCounter++];
        katsu_sound->setCurrentSource(Phonon::MediaSource(":/sounds/com_katsu.m4a"));
        katsu_sound->play();
        phononCounter %= 100;
        if (event->key() == Qt::Key_F)
        {
            hit_katsu_left_label->setVisible(true);
            QTimer::singleShot(200, this, SLOT(hideKatsuLeft()));
        }
        else
        {
            hit_katsu_right_label->setVisible(true);
            QTimer::singleShot(200, this, SLOT(hideKatsuRight()));
        }
    }
}

void Game::hideDonLeft()
{
    hit_don_left_label->setVisible(false);
}

void Game::hideDonRight()
{
    hit_don_right_label->setVisible(false);
}

void Game::hideKatsuLeft()
{
    hit_katsu_left_label->setVisible(false);
}

void Game::hideKatsuRight()
{
    hit_katsu_right_label->setVisible(false);
}

