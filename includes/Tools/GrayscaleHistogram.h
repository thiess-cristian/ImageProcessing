#pragma once

#include "IHistogram.h"
#include <map>

class GrayscaleHistogram:public IHistogram
{
public:
    GrayscaleHistogram(QImage* image);
    ~GrayscaleHistogram();

private:
    // Inherited via IHistogram
    virtual void computeHistogram(QImage * image) override;
};