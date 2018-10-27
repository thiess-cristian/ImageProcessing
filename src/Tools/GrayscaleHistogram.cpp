#include "GrayscaleHistogram.h"

#include <qimage.h>

GrayscaleHistogram::GrayscaleHistogram(QImage * image)
{
    computeHistogram(image);
}

GrayscaleHistogram::~GrayscaleHistogram()
{}


void GrayscaleHistogram::computeHistogram(QImage * image)
{
    if (image == nullptr) {
        return;
    }

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

