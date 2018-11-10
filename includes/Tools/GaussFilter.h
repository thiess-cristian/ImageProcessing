#pragma once
#include "IImageModifier.h"
#include <vector>
#include <qcolor.h>

class GaussFilter :public IImageModifier
{
public:
    GaussFilter();
    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

private:

    QColor getFilteredColor(QImage* image, size_t i, size_t j);

    size_t m_gridSize;
    std::vector<double> m_mask;
    double m_c;
};
