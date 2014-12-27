#ifndef RECOGNISE_H
#define RECOGNISE_H

#include "platefinder.h"

class Recognise
{
public:
//    Recognise();
    std::vector<IplImage *>FindCharacter(IplImage *plate);
public:
    Recognise();
//    ~Recognise();
};

#endif // RECOGNISE_H
