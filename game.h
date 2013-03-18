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

    void setMidi(Midi);
    void keyPressEvent(QKeyEvent *event);

    QTimer *timer;
    
signals:
    
private slots:
    void update();

private:
    QLabel *hit_don_left_label;
    QLabel *hit_don_right_label;

    Midi midi;

    int combo;
    int score;

    bool pressing_don;
    bool pressing_katsu;

    Phonon::MediaObject *don_sound;
    Phonon::AudioOutput *don_sound_output;
};

#endif // GAME_H
