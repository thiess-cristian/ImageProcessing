#include "Grayscale.h"

#include <qimage.h>

Grayscale::Grayscale()
{}

Grayscale::~Grayscale()
{}

QImage * Grayscale::modify(QImage * image)
{
    QImage* modifiedImage = nullptr;
    if (image != nullptr) {
        modifiedImage = new QImage(image->width(), image->height(), QImage::Format_RGB32);

        for (int i = 0; i < image->width(); i++) {
            for (int j = 0; j < image->height(); j++) {
                char cl = qGray(image->pixel(i, j));
                modifiedImage->setPixelColor(i, j, qRgb(cl, cl, cl));
            }
        }
    }
    return modifiedImage;
}
