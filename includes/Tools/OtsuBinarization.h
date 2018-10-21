#pragma once
#include "IImageModifier.h"

class QImage;


class OtsuBinarization :public IImageModifier
{
public:
    OtsuBinarization();
    ~OtsuBinarization();

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;
private:

};