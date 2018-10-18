#pragma once
#include "IImageModifier.h"

class QImage;

class InvertColors:public IImageModifier
{
public:
    InvertColors();
    ~InvertColors();

    QImage* modify(QImage* image);
};