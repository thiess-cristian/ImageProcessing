#pragma once

class QImage;

class IImageModifier
{
public:
    virtual QImage* modify(QImage* image)=0;

};