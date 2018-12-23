#include "Bicubic.h"
#include "ValueInputDialog.h"
#include <math.h>
#include <qimage.h>

Bicubic::Bicubic()
{}

QImage * Bicubic::modify(QImage * image)
{
    ValueInputDialog dialog(1);

    auto scale = dialog.show()[0];

    QImage* modifiedImage = new QImage(image->width()*scale, image->height()*scale, QImage::Format_RGB32);
 
    for (int i = 0;  i < modifiedImage->width(); i++) {
        double x = double(i) / double(modifiedImage->width() - 1);
        for (int j = 0; j < modifiedImage->height(); j++) {
            double y = double(j) / double(modifiedImage->height() - 1);
            auto sample = sampleWhole(image, x, y);

            modifiedImage->setPixelColor(i, j, sample);
        }
    }



    return modifiedImage;
}

double Bicubic::bound(double x, double min, double max)
{
    if (x < min) { 
        return min; 
    } else if (x > max) { 
        return max; 
    }
    return x;
}

double Bicubic::cubicPolynomial(double a, double b, double c, double d, double x)
{
    double sa = -a / 2.0 + (3.0*b) / 2.0 - (3.0*c) / 2.0 + d / 2.0;
    double sb = a - (5.0*b) / 2.0 + 2.0*c - d / 2.0;
    double sc = -a / 2.0 + c / 2.0;
    
    return sa*std::pow(x, 3) + sb*std::pow(x, 2) + sc*x + b;
}

QColor Bicubic::getPixel(QImage * image, double x, double y)
{
    int xCoord = bound(x, 0, image->width() - 1);
    int yCoord = bound(y, 0, image->height() - 1);

    double r = image->pixelColor(xCoord, yCoord).red();
    double g = image->pixelColor(xCoord, yCoord).green();
    double b = image->pixelColor(xCoord, yCoord).blue();

    return QColor(r, g, b);
}

QColor Bicubic::samplePixel(QImage * image, double x, double y)
{
    int xCoord = static_cast<int>(image->width()*x);
    int yCoord = static_cast<int>(image->height()*y);

    return getPixel(image,xCoord,yCoord);
}

QColor Bicubic::sampleWhole(QImage * image, double x, double y)
{
    double offsetX = x*image->width() - 0.5;
    int xInt = static_cast<int>(offsetX);
    double xFract = offsetX - floor(offsetX);

    double offsetY = y*image->height() - 0.5;
    int yInt = static_cast<int>(offsetY);
    double yFract = offsetY - floor(offsetY);

    auto firstRow = getRow(image, xInt, yInt, -1);
    auto secondRow = getRow(image, xInt, yInt, 0);
    auto thirdRow = getRow(image, xInt, yInt, 1);
    auto fourthRow = getRow(image, xInt, yInt, 2);

    auto col1Red = cubicPolynomial(firstRow[0].red(),firstRow[1].red(),firstRow[2].red(),firstRow[3].red(),xFract);
    auto col2Red = cubicPolynomial(secondRow[0].red(), secondRow[1].red(), secondRow[2].red(), secondRow[3].red(), xFract);
    auto col3Red = cubicPolynomial(thirdRow[0].red(), thirdRow[1].red(), thirdRow[2].red(), thirdRow[3].red(), xFract);
    auto col4Red = cubicPolynomial(fourthRow[0].red(), fourthRow[1].red(), fourthRow[2].red(), fourthRow[3].red(), xFract);
    auto resRed = cubicPolynomial(col1Red, col2Red, col3Red, col4Red, yFract);

    auto col1Blue = cubicPolynomial(firstRow[0].blue(), firstRow[1].blue(), firstRow[2].blue(), firstRow[3].blue(), xFract);
    auto col2Blue = cubicPolynomial(secondRow[0].blue(), secondRow[1].blue(), secondRow[2].blue(), secondRow[3].blue(), xFract);
    auto col3Blue = cubicPolynomial(thirdRow[0].blue(), thirdRow[1].blue(), thirdRow[2].blue(), thirdRow[3].blue(), xFract);
    auto col4Blue = cubicPolynomial(fourthRow[0].blue(), fourthRow[1].blue(), fourthRow[2].blue(), fourthRow[3].blue(), xFract);
    auto resBlue = cubicPolynomial(col1Blue, col2Blue, col3Blue, col4Blue, yFract);

    auto col1Green = cubicPolynomial(firstRow[0].green(), firstRow[1].green(), firstRow[2].green(), firstRow[3].green(), xFract);
    auto col2Green = cubicPolynomial(secondRow[0].green(), secondRow[1].green(), secondRow[2].green(), secondRow[3].green(), xFract);
    auto col3Green = cubicPolynomial(thirdRow[0].green(), thirdRow[1].green(), thirdRow[2].green(), thirdRow[3].green(), xFract);
    auto col4Green = cubicPolynomial(fourthRow[0].green(), fourthRow[1].green(), fourthRow[2].green(), fourthRow[3].green(), xFract);
    auto resGreen = cubicPolynomial(col1Green, col2Green, col3Green, col4Green, yFract);

    return QColor(bound(resRed,0,255), bound(resGreen,0,255), bound(resBlue,0,255));
}

std::vector<QColor> Bicubic::getRow(QImage * image, int x, int y, int rowIndex)
{
    std::vector<QColor> rows;

    for (int i = -1; i < 3; i++) {
        rows.push_back(getPixel(image,x+i,y+rowIndex));
    }
    return rows;
}
