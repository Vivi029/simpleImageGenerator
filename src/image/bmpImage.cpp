#include <map>
#include <cmath>
#include "bmpImage.h"

uint8_t *BmpImage::dumpImageInBinaryArray()
{
    uint8_t *imageData = new uint8_t[bmpHeader.size];
    uint8_t *bmpData = (uint8_t *)&bmpHeader;
    uint8_t *dibData = (uint8_t *)&dibHeader;
    uint8_t *pixelData = (uint8_t *)pixelArray;
    uint32_t position = 0;
    /*bmpHeader.size = __builtin_bswap32(bmpHeader.size);
    bmpHeader.startOfPixelArray = __builtin_bswap32(bmpHeader.startOfPixelArray);
    dibHeader.imageWidth = __builtin_bswap32(dibHeader.imageWidth);
    dibHeader.imageHeight = __builtin_bswap32(dibHeader.imageHeight);
    dibHeader.rawBitmapDataSize = __builtin_bswap32(dibHeader.rawBitmapDataSize);*/
    for (uint32_t i = 0; i < sizeof(bmpHeader); i++)
    {
        imageData[position] = bmpData[i];
        position++;
    }
    for (uint32_t i = 0; i < sizeof(dibHeader); i++)
    {
        imageData[position] = dibData[i];
        position++;
    }
    for (uint32_t i = 0; i < dibHeader.rawBitmapDataSize; i++)
    {
        imageData[position] = pixelData[i];
        position++;
    }
    /*bmpHeader.size = __builtin_bswap32(bmpHeader.size);
    bmpHeader.startOfPixelArray = __builtin_bswap32(bmpHeader.startOfPixelArray);
    dibHeader.imageWidth = __builtin_bswap32(dibHeader.imageWidth);
    dibHeader.imageHeight = __builtin_bswap32(dibHeader.imageHeight);
    dibHeader.rawBitmapDataSize = __builtin_bswap32(dibHeader.rawBitmapDataSize);*/
    return imageData;
}

void BmpImage::placePixel(uint32_t xPosition, uint32_t yPosition, PIXEL pixel)
{
    struct COLOR
    {
        double r, g, b, a;
    };
    if (((dibHeader.imageWidth * (dibHeader.imageHeight - yPosition)) - (dibHeader.imageWidth - xPosition)) <= dibHeader.imageWidth * dibHeader.imageHeight)
    {
        PIXEL *calculatedPixel = (PIXEL *)&pixelArray[((dibHeader.imageWidth * (dibHeader.imageHeight - yPosition)) - (dibHeader.imageWidth - xPosition))];
        COLOR bg = {(double)((uint32_t)calculatedPixel->red / 255.0f), (double)((uint32_t)calculatedPixel->green / 255.0f), (double)((uint32_t)calculatedPixel->blue / 255.0f), (double)((uint32_t)calculatedPixel->alpha / 255.0f)};
        COLOR fg = {(double)((uint32_t)pixel.red / 255.0f), (double)((uint32_t)pixel.green / 255.0f), (double)((uint32_t)pixel.blue / 255.0f), (double)((uint32_t)pixel.alpha / 255.0f)};
        COLOR r;
        r.a = 1 - (1 - fg.a) * (1 - bg.a);                        // 0.75
        r.r = fg.r * fg.a / r.a + bg.r * bg.a * (1 - fg.a) / r.a; // 0.67
        r.g = fg.g * fg.a / r.a + bg.g * bg.a * (1 - fg.a) / r.a; // 0.33
        r.b = fg.b * fg.a / r.a + bg.b * bg.a * (1 - fg.a) / r.a; // 0.00
        calculatedPixel->alpha = 255 * r.a;
        calculatedPixel->blue = 255 * r.b;
        calculatedPixel->green = 255 * r.g;
        calculatedPixel->red = 255 * r.r;
        //pixelArray[((dibHeader.imageWidth * (dibHeader.imageHeight - yPosition)) - (dibHeader.imageWidth - xPosition))] = *(uint32_t *)&calculatedPixel;
    }
}

void BmpImage::drawLine(uint32_t xStartPosition, uint32_t yStartPosition, uint32_t xEndPosition, uint32_t yEndPosition, float thickness, PIXEL color)
{
    int dx = abs(xEndPosition - xStartPosition), sx = xStartPosition < xEndPosition ? 1 : -1;
    int dy = abs(yEndPosition - yStartPosition), sy = yStartPosition < yEndPosition ? 1 : -1;
    /* error value e_xy */
    int err = dx - dy, e2, x2, y2;
    float ed = dx + dy == 0 ? 1 : sqrt((float)dx * dx + (float)dy * dy);

    for (thickness = (thickness + 1) / 2;;)
    {
        /* pixel loop */
        placePixel(xStartPosition, yStartPosition, {color.blue, color.green, color.red, (uint8_t)(color.alpha - (uint8_t)std::max(0, (int)(255 * (abs(err - dx + dy) / ed - thickness + 1))))});
        e2 = err;
        x2 = xStartPosition;
        if (2 * e2 >= -dx)
        {
            /* x step */
            for (e2 += dy, y2 = yStartPosition; e2 < ed * thickness && (yEndPosition != y2 || dx > dy); e2 += dx)
                placePixel(xStartPosition, y2 += sy, {color.blue, color.green, color.red, (uint8_t)(color.alpha - (uint8_t)std::max(0, (int)(255 * (abs(e2) / ed - thickness + 1))))});
            if (xStartPosition == xEndPosition)
                break;
            e2 = err;
            err -= dy;
            xStartPosition += sx;
        }
        if (2 * e2 <= dy)
        {
            /* y step */
            for (e2 = dx - e2; e2 < ed * thickness && (xEndPosition != x2 || dx < dy); e2 += dy)
                placePixel(x2 += sx, yStartPosition, {color.blue, color.green, color.red, (uint8_t)(color.alpha - (uint8_t)std::max(0, (int)(255 * (abs(e2) / ed - thickness + 1))))});
            if (yStartPosition == yEndPosition)
                break;
            err += dx;
            yStartPosition += sy;
        }
    }
}

uint32_t BmpImage::getFileSize()
{
    return bmpHeader.size;
}

uint32_t BmpImage::getImageWidth()
{
    return dibHeader.imageWidth;
}

uint32_t BmpImage::getImageHeight()
{
    return dibHeader.imageHeight;
}
