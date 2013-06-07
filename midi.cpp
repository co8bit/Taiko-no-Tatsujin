#include <iostream>
#include <QString>
#include <QFile>
#include <QDebug>
#include "midi.h"
using namespace std;

const int infinity = 31415926;

/*
 *
 *      type    start_time      speed
 *
 *
 */

Midi::Midi(QString address) : address(address)
{
    file = new QFile(address);
    file->open(QIODevice::ReadOnly | QIODevice::Text);
    in = new QTextStream(file);

    QString line = "";

    line = in->readLine();
    sscanf(line.toAscii(), "Offset: %d", &offset);

    int count = 0;
    while ( 1 )
    {
        line = in->readLine();
        if (line.isEmpty())
            break;
        int type;
        int time;
        int speed;
        sscanf(line.toAscii(), "%d %d %d", &type, &time, &speed);
        notes[count].key = type;
        notes[count].start_time = time;
        notes[count].speed = speed;
        count += 1;
    }
}
