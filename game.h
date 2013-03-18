#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include "midi.h"

class Game : public QWidget
{
    Q_OBJECT
public:
    explicit Game(QWidget *parent = 0);

    void setMidi(Midi);
    
signals:
    
public slots:

private:
    Midi midi;
};

#endif // GAME_H
