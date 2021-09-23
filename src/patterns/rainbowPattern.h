#include "pattern.h"

#ifndef _RAINBOW_PATTERN_
#define _RAINBOW_PATTERN_
class RainbowPattern : public Pattern
{
public:
    RainbowPattern(Image *image) : Pattern(image){}
    void processPattern();
};
#endif