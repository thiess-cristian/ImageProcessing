#pragma once


class QImage;

class MirrorImage
{
public:
    MirrorImage();
    ~MirrorImage();

    static QImage* modify(QImage* image);

private:


};