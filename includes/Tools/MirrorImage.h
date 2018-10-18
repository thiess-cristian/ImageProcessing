#pragma once
#include "IImageModifier.h"

class QImage;

class MirrorImage:public IImageModifier
{
public:
    MirrorImage();
    ~MirrorImage();

    QImage* modify(QImage* image);
};