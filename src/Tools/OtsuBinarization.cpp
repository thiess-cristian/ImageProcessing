#include "OtsuBinarization.h"
#include "GrayscaleHistogram.h"
#include "BinaryImage.h"

#include <qimage.h>

OtsuBinarization::OtsuBinarization()
{}

OtsuBinarization::~OtsuBinarization()
{}

QImage * OtsuBinarization::modify(QImage * image)
{
    if (image == nullptr) {
        return nullptr;
    }

    GrayscaleHistogram histogram(image);

    const std::map<size_t,size_t>& histogramValues = histogram.getHistogramValues();
    size_t numOfPixels = image->width()*image->height();


    std::map<size_t, double> cumulativeProb;
    std::map<size_t, double> mean;

    cumulativeProb[0] = 0.0;
    mean[0] = 0.0;

    const size_t maxColor = 256;
    for (size_t color = 1; color < maxColor; color++) {

        double colorProb = static_cast<double>(histogramValues.at(color)) / numOfPixels;

        cumulativeProb[color] = cumulativeProb[color - 1] + colorProb;
        mean[color] = mean[color - 1] + static_cast<double>(color)*colorProb;
    }

    size_t threshold = 0;
    double maxVariance = 0.0;


    std::map<size_t, double> variance;
    for (size_t color = 0; color < maxColor - 1; color++) {
        
        if (cumulativeProb[color] != 0.0 && cumulativeProb[color] != 1.0) {
            variance[color] = pow(mean[maxColor - 1] * cumulativeProb[color] - mean[color], 2) / (cumulativeProb[color] * (1.0 - cumulativeProb[color]));
        }

        if (variance[color] > maxVariance) {
            maxVariance = variance[color];
            threshold = color;
        }
    }

    QImage* modifiedImage = new QImage(image->width(), image->height(), QImage::Format_RGB32);

    BinaryImage binary;

    binary.computeBinarization(image, modifiedImage, threshold);

    return modifiedImage;
}
