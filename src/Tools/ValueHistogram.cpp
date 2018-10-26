#include "ValueHistogram.h"
#include <qimage.h>

ValueHistogram::ValueHistogram(QImage * image)
{
    computeHistogram(image);
}

ValueHistogram::~ValueHistogram()
{}

void ValueHistogram::computeHistogram(QImage * image)
{
    for (size_t i = 0; i < 256; i++) {
        m_histogram[i] = 0;
    }

    for (size_t i = 0; i < image->width(); i++) {
        for (size_t j = 0; j < image->height(); j++) {
            auto val = image->pixelColor(i, j).value();
            m_histogram[val]++;
        }
    }
}
