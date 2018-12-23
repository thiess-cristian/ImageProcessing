#pragma once

#include "IImageModifier.h"
#include <qcolor.h>
#include <vector>

class Canny :public IImageModifier
{
public:
    Canny(bool input=true);

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

    std::vector<double> getGradient() const;
    std::vector<double> getEdgeDir() const;
    std::vector<double> getAngles() const;

private:
    void nonMaxSuppression(QImage * image, size_t x, size_t y, 
                           const std::vector<double>& gradient, 
                           const std::vector<double>& edgeDir,
                           std::vector<double>& resultGradient);
    QColor hysteresisThresholding(QImage * image, size_t x, size_t y, const std::vector<double>& gradient);

    std::vector<double> m_gradient;
    std::vector<double> m_edgeDir;
    std::vector<double> m_resultGrad;
    std::vector<double> m_angles;

    bool m_input;

    size_t m_t1;
    size_t m_t2;
};