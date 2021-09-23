#include <iostream>
#include "pattern.h"
#include "../image/image.h"
#include "../utils.h"

#ifndef _POINT_
#define _POINT_
struct POINT
{
    uint32_t xPosition;
    uint32_t yPosition;
};
#endif

#ifndef _CHANMEL_
#define _CHANNEL_
enum CHANNEL{
    RED,
    GREEN,
    BLUE,
    YELLOW,
    CYAN,
    PINK,
    BLACK,
    ALL,
    INVERTEDRED,
    INVERTEDGREEN,
    INVERTEDBLUE,
    INVERTEDYELLOW,
    INVERTEDCYAN,
    INVERTEDPINK,
    INVERTEDBLACK,
    INVERTEDALL
};
#endif

#ifndef _POINT_PATTERN_
#define _POINT_PATTERN_
class PointPattern : public Pattern {
    public:
        PointPattern(uint32_t numberOfPoints, Image *image, CHANNEL channel, bool wrap, bool transparent) : Pattern(image)
        {
            this->numberOfPoints = numberOfPoints;
            this->points = new POINT[numberOfPoints];
            this->channel = channel;
            this->wrap = wrap;
            this->transparent = transparent;
            for (uint32_t i = 0; i < numberOfPoints; i++)
            {
                points[i] = {Utils::getRandomIntBetweenBounds(0, image->getImageWidth()), Utils::getRandomIntBetweenBounds(0, image->getImageHeight())};
                //std::cout << "New Point locaction: " << points[i].xPosition << ", " << points[i].yPosition << std::endl;
            };
        }
        void processPattern();

    private:
        POINT *getNearestPoint(uint32_t xPosition, uint32_t yPosition, float * outDistance);
        POINT *getNearestPointWrap(uint32_t xPosition, uint32_t yPosition, float * outDistance);
        bool wrap;
        POINT *points;
        CHANNEL channel;
        bool transparent;
        uint32_t numberOfPoints;
};
#endif