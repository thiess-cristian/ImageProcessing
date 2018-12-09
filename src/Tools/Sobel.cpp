#include "Sobel.h"
#include "qimage.h"

Sobel::Sobel(size_t t1, size_t t2):
    m_Sx({-1, 0, 1,
          -2, 0, 2,
          -1, 0, 1}),
    m_Sy({-1,-2,-1,
           0, 0, 0,
           1, 2, 1}),
    m_gridSize(3),
    m_t1(t1),
    m_t2(t2)
{
    
}

QImage * Sobel::modify(QImage * image)
{
    if (image == nullptr) {
        return nullptr;
    }

    QImage* modifiedImage = new QImage(image->copy(QRect(0, 0, image->width(), image->height())));

    size_t border = m_gridSize / 2;

    m_grad.resize(image->width()*image->height());
    m_edgeDir.resize(image->width()*image->height());

    for (size_t i = border; i < image->width() - border; i++) {
        for (size_t j = border; j < image->height() - border; j++) {
            modifiedImage->setPixelColor(i, j, getSobelColor(image, i, j));
        }
    }
    return modifiedImage;
}

std::vector<double> Sobel::getGradient() const
{
    return m_grad;
}

std::vector<double> Sobel::getEdgeDirection() const
{
    return m_edgeDir;
}

QColor Sobel::getSobelColor(QImage * image, int x, int y)
{

    size_t border = m_gridSize / 2;

    double sumX = 0;
    double sumY = 0;
    size_t k = 0;
    for (size_t i = x - border; i <= x + border; i++) {
        for (size_t j = y - border; j <= y + border; j++) {
            double value = qGray(image->pixel(i, j));
            sumX += value*m_Sx[k];
            sumY += value*m_Sy[k];
            k++;
        }
    }
   
    double value = std::abs(sumX) + std::abs(sumY);

    m_grad[x*image->height() + y] = value;

    m_edgeDir[x*image->height() + y]=angle(sumX, sumY);

    if (value > m_t2) {
        value = 0;
    }
    else if (value < m_t1) {
        value = 255;
    }
    auto col = 255 - value;
    return QColor(col, col, col);
}

double Sobel::angle(double sumX, double sumY)
{
    auto thisAngle = (atan2(sumX, sumY) / 3.14159) * 180.0;
    auto returnedAngle = 0.0;

    if (((thisAngle < 22.5) && (thisAngle > -22.5)) || (thisAngle > 157.5) || (thisAngle < -157.5)) {
        returnedAngle = 0;
    }
    if (((thisAngle > 22.5) && (thisAngle < 67.5)) || ((thisAngle < -112.5) && (thisAngle > -157.5))) {
        returnedAngle = 45;
    }
    if (((thisAngle > 67.5) && (thisAngle < 112.5)) || ((thisAngle < -67.5) && (thisAngle > -112.5))) {
        returnedAngle = 90;
    }
    if (((thisAngle > 112.5) && (thisAngle < 157.5)) || ((thisAngle < -22.5) && (thisAngle > -67.5))) {
        returnedAngle = 135;
    }
    return returnedAngle;
}
