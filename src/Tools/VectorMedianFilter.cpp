#include "VectorMedianFilter.h"

#include <qimage.h>
#include <qcolor.h>
#include <iostream>
#include <limits.h>

VectorMedianFilter::VectorMedianFilter(VectorMedianFilterGrid::GridSize size):
    m_gridSize(static_cast<size_t>(size))
{
}

VectorMedianFilter::~VectorMedianFilter()
{}

QImage * VectorMedianFilter::modify(QImage * image)
{
    if (image == nullptr) {
        return nullptr;
    }
    QImage* modifiedImage = new QImage(image->copy(QRect(0, 0, image->width(), image->height())));

    size_t border = m_gridSize / 2;
    std::vector<QColor> neighborColors;
    for (size_t i = border; i < image->width() - border; i++) {
        for (size_t j = border; j < image->height() - border; j++) {
            setNeighbors(image, i, j, neighborColors);

            modifiedImage->setPixelColor(i, j, getNearestColor(neighborColors));
        }
    }
    return modifiedImage;
}

void VectorMedianFilter::setNeighbors(QImage* image, size_t x, size_t y,std::vector<QColor>& neighbors) const
{
    neighbors.clear();
    size_t border = m_gridSize / 2;
    for (size_t i = x - border; i <= x + border; i++) {
        for (size_t j = y - border; j <= y + border; j++) {
            neighbors.push_back(image->pixelColor(i, j));
        }
    }
}

QColor VectorMedianFilter::getNearestColor(const std::vector<QColor>& colors) const
{
    size_t numColors = m_gridSize*m_gridSize;
    std::vector<double> distanceVec(numColors*numColors);

    double distance;
    for (size_t i = 0; i < colors.size(); i++) {
        for (size_t j = 0; j < colors.size(); j++) {
            distance = sqrt(pow(colors[i].red() - colors[j].red(), 2) + 
                            pow(colors[i].blue() - colors[j].blue(), 2) + 
                            pow(colors[i].green() - colors[j].green(), 2));

            distanceVec[i + j*numColors] = distance;
        }
    }
    
    double minDistace = std::numeric_limits<double>::max();
    size_t colorIndex=0;
    for (size_t i = 0; i < numColors; i++) {
        double distanceSum=0.0;

        for (size_t j = 0; j < numColors; j++) {
            distanceSum += distanceVec[i + j*numColors];
        }

        if (distanceSum < minDistace) {
            minDistace = distanceSum;
            colorIndex = i;
        }
    }
    return colors[colorIndex];
}
