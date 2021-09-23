#include "lineMessPattern.h"

void LineMessPattern::processPattern(){
    if (numberOfPoints > 0)
    {
        for (uint32_t i = 0; i < numberOfPoints - 1; i++)
        {
            image->drawLine(points[i].xPosition, points[i].yPosition, points[i + 1].xPosition, points[i + 1].yPosition, thickness, {(uint8_t)Utils::getRandomIntBetweenBounds(0, 255), (uint8_t)Utils::getRandomIntBetweenBounds(0, 255), (uint8_t)Utils::getRandomIntBetweenBounds(0, 255), 255});
        }
    }
}