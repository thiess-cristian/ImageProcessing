#pragma once
#include "IImageModifier.h"

namespace VectorMedianFilterGrid
{
    enum class GridSize
    {
        Grid3x3,
        Grid5x5
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
    size_t m_gridSize = 0;
};