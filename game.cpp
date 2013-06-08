#include <QtGui>
#include <QDebug>
#include <QRect>
#include "game.h"

QLabel *labelTable[100];
Phonon::MediaObject *phononTable[100];
int phononCounter = 0;
QLabel *scoreLabel;
QLabel *comboLabel;

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
        label->setVisible(false);
    }

    scoreLabel = new QLabel(this);
    scoreLabel->setGeometry(60, 0, 200, 200);
    scoreLabel->setText("Score: 100");
    scoreLabel->setStyleSheet("* {font-size: 32px;}");
    scoreLabel->show();

    comboLabel = new QLabel(this);
    comboLabel->setGeometry(360, 0, 200, 200);
    comboLabel->setText("Combo: 1");
    comboLabel->setStyleSheet("* {font-size: 32px;}");
    comboLabel->show();


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
    timer->setInterval(20);
    timer->start();

    setFocus();
    update_counter = 0;

    current_note = 0;
    current_label = 0;

    score = 0;
    combo = 0;
}

void Game::update()
{
    if (bg_music->state() != Phonon::PlayingState && update_counter > midi.offset)
    {
        bg_music->play();
    }

    if (midi.notes[current_note].start_time == update_counter)
    {
        QLabel *label = labelTable[ current_label % 100 ];

        if (midi.notes[current_note].key == 1)
        {
            QPixmap dong(":/images/dong.png");
            label->setPixmap(dong);
        }
        else if (midi.notes[current_note].key == 2)
        {
            QPixmap katsu(":/images/katsu.png");
            label->setPixmap(katsu);
        }

        label->setGeometry(700, 175, 80, 80);
        label->setVisible(true);
        current_label += 1;
        current_note += 1;
    }

    for (int i = 0; i < 100; i++)
    {
        QLabel *label = labelTable[i];
        if (label->isVisible())
        {
            QRect geom = labelTable[i]->geometry();
            if (geom.x() < 90)
            {
                label->setVisible(false);
                combo = 0;
            }
            geom.adjust(-4, 0, -4, 0);
            labelTable[i]->setGeometry(geom);
        }
    }

    scoreLabel->setText("Score: " + QString::number(score));
    comboLabel->setText("Combo: " + QString::number(combo));

    update_counter++;
}

void Game::setBgMusic(Phonon::MediaObject *music)
{
    bg_music = music;
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
        // qDebug() << "1 " << update_counter << " 0";
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

    for (int i = 0; i < 100; i++)
    {
        QLabel *label = labelTable[i];
        if (label->isVisible())
        {
            QRect geom = labelTable[i]->geometry();
            if (geom.x() > 100 && geom.x() < 180)
            {
                label->setVisible(false);

                int x = geom.x();
                if (x > 120 && x < 170)
                {
                    score += 100;
                }
                else
                {
                    score += 70;
                }

                combo += 1;

                if (combo == 50)
                {
                    Phonon::MediaObject *combo_50 = phononTable[phononCounter++];
                    combo_50->setCurrentSource(Phonon::MediaSource(":/sounds/tkds_combo050pst.m4a"));
                    combo_50->play();
                }
                else if (combo == 100)
                {
                    Phonon::MediaObject *combo_100 = phononTable[phononCounter++];
                    combo_100->setCurrentSource(Phonon::MediaSource(":/sounds/tkds_combo100pst.m4a"));
                    combo_100->play();
                    phononCounter %= 100;
                }
                else if (combo == 200)
                {
                    Phonon::MediaObject *combo_200 = phononTable[phononCounter++];
                    combo_200->setCurrentSource(Phonon::MediaSource(":/sounds/tkds_combo200pst.m4a"));
                    combo_200->play();
                    phononCounter %= 100;
                }
            }
            geom.adjust(-2, 0, -2, 0);
            labelTable[i]->setGeometry(geom);
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

