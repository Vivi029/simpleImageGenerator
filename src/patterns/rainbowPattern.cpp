#include <cmath>
#include "../utils.h"
#include "rainbowPattern.h"

void RainbowPattern::processPattern(){
    uint8_t r=0,g=0,b=0;
    for(uint32_t i = 0; i < image->getImageHeight(); i++){
        for(uint32_t j = 0; j < image->getImageWidth(); j++){
            //Not Good but it'll do for now
            Utils::HSVtoRGB(sqrt((i+j))*(image->getImageWidth()/360), 100, 100, &r, &g, &b);
            image->placePixel(j, i, {r, g, b, 255});
        }
    }
}