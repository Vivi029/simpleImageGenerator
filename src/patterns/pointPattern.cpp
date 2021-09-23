#include <cmath>
#include "pointPattern.h"

void PointPattern::processPattern(){
    for(uint32_t i = 0; i < image->getImageHeight(); i++){
        for(uint32_t j = 0; j < image->getImageWidth(); j++){
            float distance = 0.0f;
            POINT * nearestPoint = (wrap) ? getNearestPointWrap(j, i, &distance) : getNearestPoint(j, i, &distance);
            /*uint32_t xDiference = nearestPoint->xPosition - j;
            uint32_t yDiference = nearestPoint->yPosition - i;
            float distance = sqrt(xDiference*xDiference + yDiference*yDiference);*/
            switch(channel){
                case ALL:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? 255-distance:0), (uint8_t)((distance < 255) ? 255-distance:0), (uint8_t)((distance < 255) ? 255-distance:0), (transparent)? (uint8_t)((distance < 255) ? 255-distance: 0) : (uint8_t)255});
                    break;
                case RED:
                    image->placePixel(j, i, {0, 0, (uint8_t)((distance < 255) ? 255-distance:0), (transparent)? (uint8_t)((distance < 255) ? 255-distance: 0) : (uint8_t)255});
                    break;
                case GREEN:
                    image->placePixel(j, i, {0, (uint8_t)((distance < 255) ? 255-distance:0), 0, (transparent)? (uint8_t)((distance < 255) ? 255-distance: 0) : (uint8_t)255});
                    break;
                case BLUE:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? 255-distance:0), 0, 0, (transparent)? (uint8_t)((distance < 255) ? 255-distance: 0) : (uint8_t)255});
                    break;
                case YELLOW:
                    image->placePixel(j, i, {0, (uint8_t)((distance < 255) ? 255-distance:0), (uint8_t)((distance < 255) ? 255-distance:0), (transparent)? (uint8_t)((distance < 255) ? 255-distance: 0) : (uint8_t)255});
                    break;
                case CYAN:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? 255-distance:0), (uint8_t)((distance < 255) ? 255-distance:0), 0, (transparent)? (uint8_t)((distance < 255) ? 255-distance: 0) : (uint8_t)255});
                    break;
                case PINK:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? 255-distance:0), 0, (uint8_t)((distance < 255) ? 255-distance:0), (transparent)? (uint8_t)((distance < 255) ? 255-distance: 0) : (uint8_t)255});
                    break;
                case BLACK:
                    image->placePixel(j, i, {0, 0, 0, (transparent)? (uint8_t)((distance < 255) ? 255-distance: 0) : (uint8_t)255});
                    break;
                case INVERTEDALL:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? distance: 255), (uint8_t)((distance < 255) ? distance: 255), (uint8_t)((distance < 255) ? distance: 255), (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
                case INVERTEDRED:
                    image->placePixel(j, i, {0, 0, (uint8_t)((distance < 255) ? distance: 255), (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
                case INVERTEDGREEN:
                    image->placePixel(j, i, {0, (uint8_t)((distance < 255) ? distance: 255), 0, (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
                case INVERTEDBLUE:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? distance: 255), 0, 0, (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
                case INVERTEDYELLOW:
                    image->placePixel(j, i, {0, (uint8_t)((distance < 255) ? distance: 255), (uint8_t)((distance < 255) ? distance: 255), (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
                case INVERTEDCYAN:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? distance: 255), (uint8_t)((distance < 255) ? distance: 255), 0, (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
                case INVERTEDPINK:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? distance: 255), 0, (uint8_t)((distance < 255) ? distance: 255), (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
                case INVERTEDBLACK:
                    image->placePixel(j, i, {0, 0, 0, (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
                default:
                    image->placePixel(j, i, {(uint8_t)((distance < 255) ? 255-distance:0), (uint8_t)((distance < 255) ? 255-distance:0), (uint8_t)((distance < 255) ? 255-distance:0), (transparent)? (uint8_t)((distance < 255) ? distance: 255) : (uint8_t)255});
                    break;
            }
        }
    }
}

POINT * PointPattern::getNearestPoint(uint32_t xPosition, uint32_t yPosition, float * outDistance){
    POINT * nearestPoint;
    float previousShortestDistance;
        for(uint32_t i = 0; i < numberOfPoints; i++){
            int xDiference = xPosition - points[i].xPosition;
            int yDiference = yPosition - points[i].yPosition;
            float distance = sqrt(xDiference*xDiference + yDiference*yDiference);
            if(i == 0 || distance < previousShortestDistance){
                previousShortestDistance = distance;
                nearestPoint = &points[i];
                //std::cout << "Nearest point determined: " << nearestPoint->xPosition << ", " << nearestPoint->yPosition << " for coordinates: " << xPosition << ", " << yPosition << std::endl;
            }
        }
    *outDistance = previousShortestDistance;
    return nearestPoint;
}

POINT * PointPattern::getNearestPointWrap(uint32_t xPosition, uint32_t yPosition, float * outDistance){
    POINT * nearestPoint;
    float previousShortestDistance;
        for(uint32_t i = 0; i < numberOfPoints; i++){
            int xDiference = xPosition - points[i].xPosition;
            int yDiference = yPosition - points[i].yPosition;
            int negativeXDiference = (image->getImageWidth() - xPosition) - points[i].xPosition;
            int negativeYDiference = (image->getImageHeight() - yPosition) - points[i].yPosition;
            float distance = sqrt(xDiference*xDiference + yDiference*yDiference);
            float negativeXDistance = sqrt(negativeXDiference*negativeXDiference + yDiference*yDiference);
            float negativeYDistance = sqrt(xDiference*xDiference + negativeYDiference*negativeYDiference);
            float negativeDistance = sqrt(negativeXDiference*negativeXDiference + negativeYDiference*negativeYDiference);
            if(i == 0 || distance < previousShortestDistance || negativeXDistance < previousShortestDistance || negativeYDistance < previousShortestDistance || negativeDistance < previousShortestDistance){
                previousShortestDistance = (distance < negativeXDistance && distance < negativeYDistance && distance < negativeDistance) ? distance : (negativeXDistance < negativeYDistance && negativeXDistance < negativeDistance) ? negativeXDistance : (negativeYDistance < negativeDistance) ? negativeYDistance : negativeDistance;
                nearestPoint = &points[i];
                //std::cout << "Nearest point determined: " << nearestPoint->xPosition << ", " << nearestPoint->yPosition << " for coordinates: " << xPosition << ", " << yPosition << std::endl;
            }
        }
    *outDistance = previousShortestDistance;
    return nearestPoint;
}