#pragma once
#include "IImageModifier.h"
#include <vector>
#include <qcolor>

class Sobel :public IImageModifier
{
public:
    Sobel(size_t t1 = 60, size_t t2 = 100);
    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

    std::vector<double> getGradient() const;
    std::vector<double> getEdgeDirection() const;

private:

    size_t m_t1 = 60;
    size_t m_t2 = 100;

    QColor getSobelColor(QImage* image, int x, int y);
    double angle(double sumX, double sumY);

    size_t m_gridSize;
    
    std::vector<double> m_Sy;
    std::vector<double> m_Sx;

    std::vector<double> m_grad;
    std::vector<double> m_edgeDir;
};