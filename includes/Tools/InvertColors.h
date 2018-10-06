#pragma once

#include <functional>

class QImage;

class InvertColors
{
public:
    InvertColors();
    ~InvertColors();

    static std::function<QImage*(QImage*)> getModifier();

    static QImage* modify(QImage* image);
};