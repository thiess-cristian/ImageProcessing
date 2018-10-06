#include "ImageWindow.h"
#include "ui_Imagewindow.h"
#include "ProcessedImageScene.h"

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

    connect(ui->actionGreyscale, &QAction::triggered, this, &ImageWindow::loadGreyscale);
    connect(ui->actionColor, &QAction::triggered, this, &ImageWindow::loadColor);
    
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

QImage* ImageWindow::getImage()
{
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open file"), "", tr("IMAGE (*.jpg *.jpeg *.png *.bmp)"));
    if (imagePath.length()<5) {
        qDebug("Path too short!");
        return nullptr;
    }
    return new QImage(imagePath);
}
