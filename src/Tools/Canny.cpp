#include "Canny.h"
#include "GaussFilter.h"
#include "Sobel.h"
#include <qimage.h>



Canny::Canny()
{
   m_t1 = 60;
   m_t2 = 100;
}

QImage * Canny::modify(QImage * image)
{
    GaussFilter gaussFilter;
    QImage* gaussImage = gaussFilter.modify(image);

    Sobel sobel;
    QImage* sobelImage = sobel.modify(gaussImage);

    std::vector<double> gradient=sobel.getGradient();
    std::vector<double> edgeDir = sobel.getEdgeDirection();
    std::vector<double> resultGrad(gradient.size());

    QImage* modifiedImage = new QImage(image->copy(QRect(0, 0, image->width(), image->height())));

    for (size_t i = 1; i < image->width()-1; i++) {
        for (size_t j = 1; j < image->height()-1; j++) {

            nonMaxSuppression(sobelImage, i, j, gradient, edgeDir, resultGrad);
            modifiedImage->setPixelColor(i, j, hysteresisThresholding(sobelImage, i, j, resultGrad));
        }
    }

    return modifiedImage;
}


void Canny::nonMaxSuppression(QImage * image, size_t x, size_t y,const std::vector<double>& gradient, const std::vector<double>& edgeDir,std::vector<double>& resultGradient)
{
    int angle = edgeDir[x*image->height() + y];
    double pixelGrad = gradient[x*image->height() + y];
    switch (angle) {
        case 0: {
            double eastPixel = gradient[(x + 1)*image->height() + y];
            double westPixel = gradient[(x - 1)*image->height() + y];

            if (pixelGrad < eastPixel || pixelGrad < westPixel) {
                resultGradient[x*image->height() + y] = 0;
            } else {
                resultGradient[x*image->height() + y] = pixelGrad;
            }
            break;
        }
        case 45: {
            double northEastPixel = gradient[(x + 1)*image->height() + y - 1];
            double southWestPixel = gradient[(x - 1)*image->height() + y + 1];

            if (pixelGrad < northEastPixel || pixelGrad < southWestPixel) {
                resultGradient[x*image->height() + y] = 0;
            } else {
                resultGradient[x*image->height() + y] = pixelGrad;
            }
            break;
        }
        case 90: {
            double northPixel = gradient[x*image->height() + y - 1];
            double southPixel = gradient[x*image->height() + y + 1];

            if (pixelGrad < northPixel || pixelGrad < southPixel) {
                resultGradient[x*image->height() + y] = 0;
            } else {
                resultGradient[x*image->height() + y] = pixelGrad;
            }

            break;
        }
        case 135: {
            double northWestPixel = gradient[(x - 1)*image->height() + y - 1];
            double southEastPixel = gradient[(x + 1)*image->height() + y + 1];

            if (pixelGrad < northWestPixel || pixelGrad < southEastPixel) {
                resultGradient[x*image->height() + y] = 0;
            } else {
                resultGradient[x*image->height() + y] = pixelGrad;
            }
            break;
        }
        default:
            break;
    }
}

QColor Canny::hysteresisThresholding(QImage * image, size_t x, size_t y,const std::vector<double>& gradient)
{
    if (abs(gradient[x*image->height() + y]) <= m_t1) {
        return QColor(0, 0, 0);
    } else if (abs(gradient[x*image->height() + y]) > m_t2) {
        return QColor(255, 255, 255);
    } else {

        for (size_t i = x - 1; i <= x + 1; i++) {
            for (size_t j = y - 1; j <= y + 1; j++) {
                if (abs(gradient[i*image->height() + j]) > m_t2) {
                    return QColor(255, 255, 255);
                }
            }
        }
        return QColor(0, 0, 0);
    }
}

