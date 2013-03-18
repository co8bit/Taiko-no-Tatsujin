#include <iostream>
#include "midi.h"

const int infinity = 31415926;

Midi::Midi(std::string address) : address(address)
{
    ;
}

void Midi::parse()
{
    FILE *fin = fopen(address.c_str(), "r");
    fscanf(fin, "BPM=%d\n", &bpm);
    fscanf(fin, "Division=%d", &division);
    printf("BPM: %d\n", bpm);
    printf("Division: %d\n", division);
    int count = 0;
    while (true)
    {
        fscanf(fin, "%d,%d,%d", &(notes[count].key), &(notes[count].start), &(notes[count].end));
        if (notes[count].key == 0)
        {
            notes[count].start = notes[count].end = infinity;
            break;
        }
        ++count;
    }
}
