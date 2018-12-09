#pragma once
#include "IImageModifier.h"
#include <vector>
#include <functional>

class QColor;
class QPoint;

class ZhangSuen :public IImageModifier
{
public:
    ZhangSuen();
    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

private:
    bool step(QImage* image, std::function< bool()> neighborCheck);
    void setNeighbors(QImage* image, size_t x, size_t y);
    size_t nrOfTransitions();
    size_t nrOfBlackNeighbors();
    bool checkPixel( std::function< bool()> neighborCheck);
    size_t m_gridSize=3;

    QImage* m_endImage;

    std::vector<QColor> m_neighbors;
    std::vector<QPoint> m_markedPixels;
};