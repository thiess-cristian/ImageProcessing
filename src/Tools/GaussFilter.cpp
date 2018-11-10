#include "GaussFilter.h"
#include <qimage.h>
#include <cmath>

#define _USE_MATH_DEFINES 
#include <math.h>

GaussFilter::GaussFilter():
    m_gridSize(5),
    m_mask(std::vector<double>(m_gridSize*m_gridSize))
{
    double sigma = 1.0;
    
    auto h = [&sigma](double i,double j) {
        return 1 / (2 * M_PI*sigma*sigma)*std::exp(-1 * (i*i + j*j) / (2 * sigma*sigma));
    };

    double sum = 0.0;
    int border = m_gridSize / 2;
    size_t k = 0;
    for (int i = -border; i <= border; i++) {
        for (int j = -border; j <= border; j++) {
            double value = h(i, j);
            m_mask[k++] = value;
            sum += value;
        }
    }

    for ( auto& value : m_mask) {
        value /= sum;
    }

    m_c = 1 / sum;
}

QImage * GaussFilter::modify(QImage * image)
{
    if (image == nullptr) {
        return nullptr;
    }

    QImage* modifiedImage = new QImage(image->copy(QRect(0, 0, image->width(), image->height())));

    size_t border = m_gridSize / 2;
    
    for (size_t i = border; i < image->width() - border; i++) {
        for (size_t j = border; j < image->height() - border; j++) {
            modifiedImage->setPixelColor(i, j, getFilteredColor(image,i,j));
        }
    }

    return modifiedImage;
}

QColor GaussFilter::getFilteredColor(QImage * image, size_t x, size_t y)
{
    size_t border = m_gridSize / 2;

    double sum=0;
    size_t k = 0;
    for (size_t i = x - border; i <= x + border; i++) {
        for (size_t j = y - border; j <= y + border; j++) {
            double value= qGray(image->pixel(i, j));
            sum += value*m_mask[k++];
        }
    }
    sum /= m_c;
    return QColor(sum,sum,sum);
}
