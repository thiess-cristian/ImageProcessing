#pragma once
#include "IHistogram.h"

class ColorHistogram :public IHistogram
{
public:
    ColorHistogram(QImage* image);
    ~ColorHistogram();

private:
    // Inherited via IHistogram
    virtual void computeHistogram(QImage * image) override;
};