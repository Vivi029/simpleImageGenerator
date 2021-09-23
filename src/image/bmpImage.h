#include "image.h"

//Use pragma when using VC++ and use __attribute__((packed)) when using gcc 
//#pragma packed(1)
struct BMPHEADER{
    uint16_t identifier = 0x4D42;
    uint32_t size;
    uint32_t applicationSpecific = 0x00000000;
    uint32_t startOfPixelArray;
} __attribute__((packed));

struct DIBHEADER{
    uint32_t headerSize = 124;
    uint32_t imageWidth;
    uint32_t imageHeight;
    uint16_t nbrOfPlanes = 1;
    uint16_t nbrOfBitsPerPixel = 32;
    uint32_t bitmapCompression = 3;
    uint32_t rawBitmapDataSize;
    uint32_t printResolutionHorizontal = 2835;
    uint32_t printResolutionVertical = 2835;
    uint32_t numberOfColorsInColorPalette = 0x00000000;
    uint32_t importantColors = 0x00000000;
    uint32_t redChannelBitMask = 0x00FF0000;
    uint32_t greenChannelBitMask = 0x0000FF00;
    uint32_t blueChannelBitMask = 0x000000FF;
    uint32_t alphaChannelBitMask = 0xFF000000;
    uint32_t lcsWindowsColorSpace = 0x57696E20;
    long redXCoordinate = 0x0000000000000000;
    long redYCoordinate = 0x0000000000000000;
    long redZCoordinate = 0x0000000000000000;
    long greenXCoordinate = 0x0000000000000000;
    long greenYCoordinate = 0x0000000000000000;
    long greenZCoordinate = 0x0000000000000000;
    long blueXCoordinate = 0x0000000000000000;
    long blueYCoordinate = 0x0000000000000000;
    uint32_t gammaRed = 0x000000FF;
    uint32_t gammaGreen = 0x0000FF00;
    uint32_t gammaBlue = 0x00FF0000;

} __attribute__((packed));

class BmpImage: public Image{
    public:
        BmpImage(uint32_t width, uint32_t height) : Image(width, height) {
            pixelArray = new uint32_t[width * height];
            bmpHeader.size = sizeof(bmpHeader) + sizeof(dibHeader) + sizeof(uint32_t) * (width * height);
            bmpHeader.startOfPixelArray = sizeof(bmpHeader) + sizeof(dibHeader);
            dibHeader.imageWidth = width;
            dibHeader.imageHeight = height;
            dibHeader.rawBitmapDataSize = sizeof(uint32_t) * (width * height);
            pixelArray = new uint32_t[width * height];
        };
        void placePixel(uint32_t xPosition, uint32_t yPosition, PIXEL pixel);
        void drawLine(uint32_t xStartPosition, uint32_t yStartPosition, uint32_t xEndPosition, uint32_t yEndPosition, float thickness, PIXEL color);
        uint8_t* dumpImageInBinaryArray();
        uint32_t getFileSize();
        uint32_t getImageWidth();
        uint32_t getImageHeight();
    private:
        uint32_t * pixelArray;
        BMPHEADER bmpHeader;
        DIBHEADER dibHeader;
};