#include <iostream>

#ifndef _PIXEL_
#define _PIXEL_
struct PIXEL{
    uint8_t blue;
    uint8_t green;
    uint8_t red;
    uint8_t alpha;
};
#endif

#ifndef _IMAGE_
#define _IMAGE_
class Image{
    public:
        Image(uint32_t width, uint32_t height);
        virtual void placePixel(uint32_t xPosition, uint32_t yPosition, PIXEL pixel){};
        virtual void drawLine(uint32_t xStartPosition, uint32_t yStartPosition, uint32_t xEndPosition, uint32_t yEndPosition, float thickness, PIXEL color){};
        virtual uint8_t* dumpImageInBinaryArray(){return nullptr;};
        virtual uint32_t getFileSize(){return 0;};
        virtual uint32_t getImageWidth(){return 0;};
        virtual uint32_t getImageHeight(){return 0;};
    private:
        uint32_t width;
        uint32_t height;
};
#endif