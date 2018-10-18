#include "InvertColors.h"

#include <qimage.h>

InvertColors::InvertColors()
{}

InvertColors::~InvertColors()
{}

QImage * InvertColors::modify(QImage * image)
{
    QImage* modifiedImage=nullptr;
    if (image != nullptr) {
        modifiedImage = new QImage(image->width(), image->height(), QImage::Format_RGB32);

        for (int i = 0; i < image->width(); i++) {
            for (int j = 0; j < image->height(); j++) {
                QColor color = image->pixelColor(i, j);
                modifiedImage->setPixel(i, j, qRgb(255 - color.red(), 255 - color.green(), 255 - color.blue()));
            }
        }
    }
    return modifiedImage;
}
