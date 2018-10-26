#pragma once
#include "IHistogram.h"

class ValueHistogram :public IHistogram
{
public:
    ValueHistogram(QImage* image);
    ~ValueHistogram();

private:
    // Inherited via IHistogram
    virtual void computeHistogram(QImage * image) override;
};