#ifndef GAME_H
#define GAME_H

#include <QtGui>
#include <QWidget>
#include <QTimer>
#include <Phonon>
#include "midi.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);

    void setBgMusic(Phonon::MediaObject *);
    void setMidi(Midi);
    void keyPressEvent(QKeyEvent *event);

    QTimer *timer;
    
signals:
    
private slots:
    void update();
    void hideDonLeft();
    void hideDonRight();
    void hideKatsuLeft();
    void hideKatsuRight();

private:
    QLabel *hit_don_left_label;
    QLabel *hit_don_right_label;
    QLabel *hit_katsu_left_label;
    QLabel *hit_katsu_right_label;
    QLabel *dongOkLabel;
    QLabel *katsuOkLabel;

    Phonon::MediaObject *bg_music;

    Midi midi;
    int current_note;
    int current_label;

    int combo;
    int score;

    bool pressing_don;
    bool pressing_katsu;

    Phonon::MediaObject *don_sound;
    Phonon::AudioOutput *don_sound_output;

    int update_counter;
};

#endif // GAME_H
