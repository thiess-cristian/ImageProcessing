#pragma once
#include "IImageModifier.h"
#include <vector>
#include <qcolor.h>


namespace VectorMedianFilterGrid
{
    enum class GridSize
    {
        Grid3x3 = 3,
        Grid5x5 = 5
    };
}



class VectorMedianFilter :public IImageModifier
{
public:
    VectorMedianFilter(VectorMedianFilterGrid::GridSize size);
    ~VectorMedianFilter();

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

private:
    void setNeighbors(QImage* image, size_t x, size_t y,std::vector<QColor>& neighbors) const;
    QColor getNearestColor(const std::vector<QColor>& colors)const;
    size_t m_gridSize = 0;
};