#include "ImageWindow.h"
#include "ui_Imagewindow.h"
#include "ProcessedImageScene.h"

#include "InvertColors.h"
#include "BinaryImage.h"
#include "MirrorImage.h"
#include "Histogram.h"
#include "HistogramEqualizer.h"

#include <iostream>
#include <memory>

#include <qfiledialog.h>
#include <qgraphicsitem.h>
#include <qevent.h>

ImageWindow::ImageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui_ImageWindow())
{
    ui->setupUi(this);

    ui->actionColor;


    m_initialImage = new ProcessedImageScene();
    m_modifiedImage = new ProcessedImageScene();
    ui->graphicsViewModified->setScene(m_modifiedImage);
    ui->graphicsViewInitial->setScene(m_initialImage);

    connect(m_initialImage, &ProcessedImageScene::selectedImage, m_modifiedImage, &ProcessedImageScene::getSelectedImage);

    connect(ui->actionGreyscale,     &QAction::triggered, this, &ImageWindow::loadGreyscale);
    connect(ui->actionColor,         &QAction::triggered, this, &ImageWindow::loadColor);
    connect(ui->actionInvert_colors, &QAction::triggered, this, &ImageWindow::invertColors);
    connect(ui->actionBinary_image,  &QAction::triggered, this, &ImageWindow::binaryImage);
    connect(ui->actionMirror_image,  &QAction::triggered, this, &ImageWindow::mirrorImage);
    connect(ui->actionHistogram,     &QAction::triggered, this, &ImageWindow::histogram);
    connect(ui->actionSelect_image,  &QAction::triggered, this, &ImageWindow::selectImage);
    connect(ui->actionColor_Histogram_Equalization, &QAction::triggered, this, &ImageWindow::colorHistogramEqualization);
    
}

ImageWindow::~ImageWindow()
{
    delete ui;
}


void ImageWindow::loadGreyscale()
{
    QImage* image=loadImage();
    m_initialImage->clear();
    m_initialImage->addImage(image,true);
}

void ImageWindow::loadColor()
{
    QImage* image = loadImage();

    m_initialImage->clear();
    m_initialImage->addImage(image);
}

void ImageWindow::invertColors()
{
    QImage* image=InvertColors::modify(m_initialImage->getImage());
    setModifiedImage(image);
}

void ImageWindow::mirrorImage()
{
    QImage* image = MirrorImage::modify(m_initialImage->getImage());
    setModifiedImage(image);
}

void ImageWindow::binaryImage()
{
    QImage* image = BinaryImage::modify(m_initialImage->getImage());
    setModifiedImage(image);
    
}

void ImageWindow::histogram()
{
    Histogram* g = new Histogram();
    g->display(m_initialImage->getImage());

}

void ImageWindow::selectImage()
{
    m_initialImage->toggleSelection();

}

void ImageWindow::colorHistogramEqualization()
{
    HistogramEqualizer equalizer;
    QImage* image = equalizer.modify(m_initialImage->getImage());
    setModifiedImage(image);

}

void ImageWindow::setModifiedImage(QImage * image)
{
    if (image != nullptr) {
        m_modifiedImage->clear();
        m_modifiedImage->addImage(image);
    }
}

QImage* ImageWindow::loadImage()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("IMAGE (*.jpg *.jpeg *.png *.bmp)"));
    if (imagePath.length()<5) {
        qDebug("Path too short!");
        return nullptr;
    }
    return new QImage(imagePath);
}
