#pragma once

#include <map>

class QImage;

class GrayscaleHistogram
{
public:
    GrayscaleHistogram(QImage* image);
    ~GrayscaleHistogram();

    const std::map<size_t, size_t>& getHistogramValues() const ;

private:
    std::map<size_t, size_t> m_histogram;

};