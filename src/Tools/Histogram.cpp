#include "Histogram.h"

#include <qimage.h>

Histogram::Histogram(QImage * image)
{
    for (size_t i = 0; i < 256; i++) {
        m_histogram[i] = 0;
    }

    for (size_t i = 0; i < image->width(); i++) {
        for (size_t j = 0; j < image->height(); j++) {
            auto val = qGray(image->pixel(i, j));
            m_histogram[val]++;
        }
    }
}

Histogram::~Histogram()
{}

const std::map<size_t, size_t>& Histogram::getHistogramValues() const
{
    return m_histogram;
}
