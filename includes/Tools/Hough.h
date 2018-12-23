#pragma once

#include "IImageModifier.h"
#include <vector>

enum class Display
{
    Edges,
    Matrix
};

struct Peak
{
    Peak(double r, double theta, double val);
    double m_r;
    double m_theta;
    double m_val;

};

class Hough :public IImageModifier
{
public:

    Hough(Display display=Display::Edges);

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

private:
    std::vector<int> m_matrix;
    size_t m_matrixWidth;
    size_t m_matrixHeight;

    std::vector<Peak> findPeaks(const std::vector<int>& values);

    Display m_display;
};