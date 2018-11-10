#pragma once
#include "IImageModifier.h"
#include <vector>
#include <qcolor>

class Sobel :public IImageModifier
{
public:
    Sobel();
    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

    std::vector<double> getGradient() const;
    std::vector<double> getEdgeDirection() const;

private:

    QColor getSobelColor(QImage* image, int x, int y);
    double angle(double sumX, double sumY);

    size_t m_gridSize;
    
    std::vector<double> m_Sy;
    std::vector<double> m_Sx;

    std::vector<double> m_grad;
    std::vector<double> m_edgeDir;
};