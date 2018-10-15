#pragma once

#include "IImageModifier.h"

class QImage;

class Grayscale:public IImageModifier
{
public:
    Grayscale();
    ~Grayscale();

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;
};