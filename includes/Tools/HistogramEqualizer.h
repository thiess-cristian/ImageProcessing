#pragma once
#include "IImageModifier.h"
#include <map>

class HistogramEqualizer :public IImageModifier
{
public:
    HistogramEqualizer();
    ~HistogramEqualizer();

    // Inherited via IImageModifier
    virtual QImage * modify(QImage * image) override;

private:
    std::map<size_t, size_t> m_valueCount;

};