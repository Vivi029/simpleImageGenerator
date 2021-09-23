#include <iostream>
#include "../image/image.h"

#ifndef _PATTERN_
#define _PATTERN_
class Pattern{
    public:
        Pattern(Image *image);
        virtual void processPattern(){};
    protected:
        Image *image;
};
#endif