#ifndef MIDI_H
#define MIDI_H

#include <iostream>
#include <string>
#include <QFile>
#include <QTextStream>
#include "note.h"

class Midi
{

public:
    Midi(QString address);
    Note notes[10000];
    int offset;

private:
    QString address;
    QFile *file;
    QTextStream *in;

};

#endif // MIDI_H
