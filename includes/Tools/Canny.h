#pragma once

#include "IImageModifier.h"
#include <qcolor.h>
#include <vector>

class Canny :public IImageModifier
{
public:
    Canny();

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;


private:
    void nonMaxSuppression(QImage * image, size_t x, size_t y, 
                           const std::vector<double>& gradient, 
                           const std::vector<double>& edgeDir,
                           std::vector<double>& resultGradient);
    QColor hysteresisThresholding(QImage * image, size_t x, size_t y, const std::vector<double>& gradient);

    size_t m_t1;
    size_t m_t2;
};