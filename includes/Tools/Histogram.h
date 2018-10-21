#pragma once

#include <map>

class QImage;

class Histogram
{
public:
    Histogram(QImage* image);
    ~Histogram();

    const std::map<size_t, size_t>& getHistogramValues() const ;

private:
    std::map<size_t, size_t> m_histogram;

};