#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "image/bmpImage.h"
#include "patterns/pointPattern.h"
#include "patterns/rainbowPattern.h"
#include "patterns/lineMessPattern.h"
#include "utils.h"

enum PATTERN
{
    POINTPATTERN,
    RAINBOW,
    LINEMESS,
    TESTPATTERN,
    UNKNOWNPATTERN
};

struct PARAMETERS
{
    char *fileName = nullptr;
    PATTERN selectedPattern;
    CHANNEL selectedChannel;
    uint32_t width = 16;
    uint32_t height = 16;
    int numberOfPoints = 10;
    bool wrap = false;
    bool transparent = false;
    float thickness = 0.0f;
};

PATTERN hashPattern(std::string pattern)
{
    if (pattern == "point")
        return POINTPATTERN;
    if(pattern == "rainbow")
        return RAINBOW;
    if(pattern == "linemess")
        return LINEMESS;
    if (pattern == "test")
        return TESTPATTERN;
    return UNKNOWNPATTERN;
}

CHANNEL hashChannel(std::string channel)
{
    if (channel == "all")
        return ALL;
    if (channel == "red")
        return RED;
    if (channel == "green")
        return GREEN;
    if (channel == "blue")
        return BLUE;
    if (channel == "yellow")
        return YELLOW;
    if (channel == "cyan")
        return CYAN;
    if (channel == "pink")
        return PINK;
    if (channel == "black")
        return BLACK;
    if (channel == "invertedall")
        return INVERTEDALL;
    if (channel == "invertedred")
        return INVERTEDRED;
    if (channel == "invertedgreen")
        return INVERTEDGREEN;
    if (channel == "invertedblue")
        return INVERTEDBLUE;
    if (channel == "invertedyellow")
        return INVERTEDYELLOW;
    if (channel == "invertedcyan")
        return INVERTEDCYAN;
    if (channel == "invertedpink")
        return INVERTEDPINK;
    if (channel == "invertedblack")
        return INVERTEDBLACK;
    return ALL;
}

void processParameters(int argc, char **argv, PARAMETERS *param)
{
    for (uint32_t i = 1; i < argc; i++)
    {
        if ((std::string)argv[i] == "-o")
        {
            if (i + 1 <= argc)
            {
                param->fileName = argv[i + 1];
            }
        }
        if ((std::string)argv[i] == "-p")
        {
            if (i + 1 <= argc)
            {
                param->selectedPattern = hashPattern(argv[i + 1]);
            }
        }
        if ((std::string)argv[i] == "-w")
        {
            if (i + 1 <= argc)
            {
                try
                {
                    param->width = atoi(argv[i + 1]);
                }
                catch (std::bad_cast ex)
                {
                    std::cerr << "Value provided for width is not a number: " << ex.what() << std::endl;
                }
            }
        }
        if ((std::string)argv[i] == "-h")
        {
            if (i + 1 <= argc)
            {
                try
                {
                    param->height = atoi(argv[i + 1]);
                }
                catch (std::bad_cast ex)
                {
                    std::cerr << "Value provided for height is not a number: " << ex.what() << std::endl;
                }
            }
        }
        if ((std::string)argv[i] == "--number-of-points")
        {
            if (i + 1 <= argc)
            {
                try
                {
                    param->numberOfPoints = atoi(argv[i + 1]);
                }
                catch (std::bad_cast ex)
                {
                    std::cerr << "Value provided for number of points is not a number: " << ex.what() << std::endl;
                }
            }
        }
        if ((std::string)argv[i] == "--seed")
        {
            if (i + 1 <= argc)
            {
                Utils::setSeed(atoi(argv[i + 1]));
            }
        }
        if ((std::string)argv[i] == "--channel")
        {
            if (i + 1 <= argc)
            {
                param->selectedChannel = hashChannel(argv[i + 1]);
            }
        }
        if((std::string)argv[i] == "--wrap")
        {
            param->wrap = true;
        }

        if((std::string)argv[i] == "--transparent")
        {
            param->transparent = true;
        }
        if((std::string)argv[i] == "--thickness"){
            if (i + 1 <= argc)
            {
                param->thickness = atoi(argv[i + 1]);
            }
        }
    }
}

int main(int argc, char **argv)
{
    PARAMETERS *param = new PARAMETERS;
    processParameters(argc, argv, param);
    if (argc > 1)
    {
        if (param->fileName != nullptr)
        {
            Image *bmpImage = new BmpImage(param->width, param->height);
            Pattern *patternToUse;
            switch (param->selectedPattern)
            {
            case POINTPATTERN:
                patternToUse = new PointPattern(param->numberOfPoints, bmpImage, param->selectedChannel, param->wrap, param->transparent);
                break;
            case RAINBOW:
                patternToUse = new RainbowPattern(bmpImage);
                break;
            case LINEMESS:
                patternToUse = new LineMessPattern(param->numberOfPoints, bmpImage, param->thickness);
                break; 
            case TESTPATTERN:
                bmpImage->drawLine(bmpImage->getImageWidth(), bmpImage->getImageHeight(), 0, 0, 5, {0, 0, 255, 127});
                bmpImage->drawLine(0, bmpImage->getImageHeight(), bmpImage->getImageWidth(), 0, 5, {0, 0, 255, 127});
                bmpImage->drawLine(0, bmpImage->getImageHeight()/2, bmpImage->getImageWidth(), bmpImage->getImageHeight()/2, 5, {0, 255, 0, 127});
                bmpImage->drawLine(bmpImage->getImageWidth()/2, 0, bmpImage->getImageWidth()/2, bmpImage->getImageHeight(), 5, {255, 0, 0, 127});
                std::cout << "Test pattern reached" << std::endl;
                break;
            default:
                std::cerr << "Unknown pattern or no pattern selected" << std::endl;
                break;
            }
            if(patternToUse != nullptr){
                patternToUse->processPattern();
            }
            uint8_t *imageData = bmpImage->dumpImageInBinaryArray();
            std::ofstream imageFile(param->fileName, std::ios::binary);
            imageFile.write(reinterpret_cast<char *>(imageData), bmpImage->getFileSize());
            imageFile.flush();
            imageFile.close();
        }
    }
    else
    {
        std::cout << "No arguments provided execute with the --help flag for help" << std::endl;
    }
    return 0;
}