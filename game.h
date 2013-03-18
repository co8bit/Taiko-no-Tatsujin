#ifndef GAME_H
#define GAME_H

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
    Midi midi;

    int combo;
    int score;

    bool pressing_don;
    bool pressing_katsu;

    Phonon::MediaObject *don_sound;
    Phonon::AudioOutput *don_sound_output;
};

#endif // GAME_H
