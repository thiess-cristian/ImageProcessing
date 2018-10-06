#include "ImageWindow.h"
#include "ui_Imagewindow.h"
#include "ProcessedImageScene.h"

#include "InvertColors.h"
#include "BinaryImage.h"

#include <iostream>
#include <memory>

#include <qfiledialog.h>
#include <qgraphicsitem.h>

ImageWindow::ImageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui_ImageWindow())
{
    ui->setupUi(this);

    ui->actionColor;


    m_initialImage = new ProcessedImageScene();
    m_modifiedImage = new ProcessedImageScene();

    connect(ui->actionGreyscale,     &QAction::triggered, this, &ImageWindow::loadGreyscale);
    connect(ui->actionColor,         &QAction::triggered, this, &ImageWindow::loadColor);
    connect(ui->actionInvert_colors, &QAction::triggered, this, &ImageWindow::invertColors);
    connect(ui->actionBinary_image,  &QAction::triggered, this, &ImageWindow::binaryImage);
    
}

ImageWindow::~ImageWindow()
{
    delete ui;
}

void ImageWindow::loadGreyscale()
{
    QImage* image=getImage();
    m_initialImage->clear();
    m_initialImage->addImage(image,true);

    ui->graphicsViewInitial->setScene(m_initialImage);

}

void ImageWindow::loadColor()
{
    QImage* image = getImage();

    m_initialImage->clear();
    m_initialImage->addImage(image);

    ui->graphicsViewInitial->setScene(m_initialImage);
}

void ImageWindow::invertColors()
{
    QImage* image=InvertColors::modify(m_initialImage->getImage());
    if (image != nullptr) {
        m_modifiedImage->clear();
        m_modifiedImage->addImage(image);

        ui->graphicsViewModified->setScene(m_modifiedImage);
    }
}

void ImageWindow::mirrorImage()
{}

void ImageWindow::binaryImage()
{
    QImage* image = BinaryImage::modify(m_initialImage->getImage());
    if (image != nullptr) {
        m_modifiedImage->clear();
        m_modifiedImage->addImage(image);

        ui->graphicsViewModified->setScene(m_modifiedImage);
    }
}

void ImageWindow::histogram()
{}

QImage* ImageWindow::getImage()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("IMAGE (*.jpg *.jpeg *.png *.bmp)"));
    if (imagePath.length()<5) {
        qDebug("Path too short!");
        return nullptr;
    }
    return new QImage(imagePath);
}
