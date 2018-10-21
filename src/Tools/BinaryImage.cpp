#include "BinaryImage.h"

#include <qimage.h>
#include <qinputdialog.h>
#include <qdir.h>
#include <iostream>

BinaryImage::BinaryImage()
{

}

BinaryImage::~BinaryImage()
{

}

QImage * BinaryImage::modify(QImage * image)
{
    bool ok;
    int alpha = QInputDialog::getInt(nullptr, QObject::tr("QInputDialog::getInteger()"),
                                 QObject::tr("Percentage:"), 150, 0, 256, 1, &ok);

    QImage* modifiedImage = nullptr;
    if (image != nullptr) {

        if (!ok) {
            return image;
        }

        modifiedImage = new QImage(image->width(), image->height(), QImage::Format_RGB32);
        computeBinarization(image, modifiedImage, alpha);

    }
    return modifiedImage;
}

void BinaryImage::computeBinarization(QImage * input, QImage * output, int threshold)
{
    for (size_t i = 0; i < input->width(); i++) {
        for (size_t j = 0; j < input->height(); j++) {
            if (qGray(input->pixel(i, j))<threshold) {
                output->setPixel(i, j, qRgb(0, 0, 0));
            } else {
                output->setPixel(i, j, qRgb(255, 255, 255));
            }
        }
    }
}
