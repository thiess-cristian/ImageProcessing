#pragma once
#include "IImageModifier.h"

class QImage;

class BinaryImage:public IImageModifier
{
public:
    BinaryImage();
    ~BinaryImage();

    QImage* modify(QImage* image);
};