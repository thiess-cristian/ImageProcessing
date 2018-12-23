#pragma once

#include "IImageModifier.h"
#include <vector>

enum class Display
{
    Edges,
    Matrix
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

    QImage* displayEdges(QImage* image);
    QImage* displayMatrix(QImage* image);

    Display m_display;
};