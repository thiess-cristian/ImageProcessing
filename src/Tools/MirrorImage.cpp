#include "MirrorImage.h"

#include <qimage.h>

MirrorImage::MirrorImage()
{}

MirrorImage::~MirrorImage()
{}

QImage * MirrorImage::modify(QImage * image)
{
    QImage* modifiedImage = nullptr;
    if (image != nullptr) {
        modifiedImage = new QImage(image->width(), image->height(), QImage::Format_RGB32);

        for (int i = 0; i < image->width(); i++) {
            for (int j = 0; j < image->height(); j++) {
                QColor color = image->pixelColor(i, j);               
                modifiedImage->setPixelColor(image->width()-i-1, j, color);
            }
        }
    }
    return modifiedImage;
}
