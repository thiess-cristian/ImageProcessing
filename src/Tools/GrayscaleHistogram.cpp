#include "GrayscaleHistogram.h"

#include <qimage.h>

GrayscaleHistogram::GrayscaleHistogram(QImage * image)
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

GrayscaleHistogram::~GrayscaleHistogram()
{}

const std::map<size_t, size_t>& GrayscaleHistogram::getHistogramValues() const
{
    return m_histogram;
}
