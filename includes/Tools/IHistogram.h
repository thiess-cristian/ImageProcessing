#pragma once

#include <map>

class QImage;

enum class HistogramType
{
    Grayscale,
    Color,
    Value
};

class IHistogram
{
public:
    const std::map<size_t, size_t>& getHistogramValues() const
    {
        return m_histogram;
    }

    HistogramType getType()const
    {
        return m_type;
    }

protected:
    virtual void computeHistogram(QImage* image)=0;

    std::map<size_t, size_t> m_histogram;
    HistogramType m_type;

};