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

    bool operator>(const Peak& peak);
    bool operator>(double values);

};

class Hough :public IImageModifier
{
public:

    Hough(Display display=Display::Edges);

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

private:
    std::vector<int> m_matrix;
    int m_matrixWidth;
    int m_matrixHeight;
    int m_imgWidth;
    int m_imgHeight;

    int m_threshold;

    std::vector<Peak> findPeaks2(const std::vector<int>& values);

    Display m_display;
};