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

        for (int i = 0; i < image->width(); i++) {
            for (int j = 0; j < image->height(); j++) {
                auto val = qGray(image->pixel(i, j));
                //std::cout << val << std::endl;
                if (val<alpha) {
                    modifiedImage->setPixel(i, j, qRgb(0, 0, 0));
                } else {
                    modifiedImage->setPixel(i, j, qRgb(255, 255, 255));
                }
            }
        }
    }
    return modifiedImage;
}
