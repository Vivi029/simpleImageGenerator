#include <iostream>
#include "pattern.h"
#include "../utils.h"

#ifndef _POINT_
#define _POINT_
struct POINT
{
    uint32_t xPosition;
    uint32_t yPosition;
};
#endif

#ifndef _LINE_MESS_PATTERN_
#define _LINE_MESS_PATTERN_

class LineMessPattern : public Pattern {
    public:
        LineMessPattern(uint32_t numberOfPoints, Image *image, float thickness) : Pattern(image){
            this->numberOfPoints = numberOfPoints;
            this->thickness = thickness;
            this->points = new POINT[numberOfPoints];
            for (uint32_t i = 0; i < numberOfPoints; i++)
            {
                points[i] = {Utils::getRandomIntBetweenBounds(0, image->getImageWidth()), Utils::getRandomIntBetweenBounds(0, image->getImageHeight())};
            };
        }
        void processPattern();
    private:
        uint32_t numberOfPoints;
        POINT * points;
        float thickness;
};

#endif