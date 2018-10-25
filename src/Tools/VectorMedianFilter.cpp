#include "VectorMedianFilter.h"

VectorMedianFilter::VectorMedianFilter(VectorMedianFilterGrid::GridSize size)
{
    if (size==VectorMedianFilterGrid::GridSize::Grid3x3) {
        m_gridSize = 3;
    } else {
        m_gridSize = 5;
    }
}

VectorMedianFilter::~VectorMedianFilter()
{}

QImage * VectorMedianFilter::modify(QImage * image)
{
    return nullptr;
}
