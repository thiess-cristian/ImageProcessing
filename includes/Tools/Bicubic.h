#pragma once
#include "IImageModifier.h"
#include <qcolor.h>
#include <vector>
#include <tuple>

class Bicubic :public IImageModifier
{
public:
    Bicubic();
    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

private:
    double bound(double x,double min,double max);
    double cubicPolynomial(double a, double b, double c, double d, double x);
    QColor getPixel(QImage * image, double x, double y);
    QColor samplePixel(QImage * image,double x,double y);
    QColor sampleWhole(QImage * image, double x, double y);
    std::vector<QColor> getRow(QImage * image, int x, int y, int rowIndex);
};

