#include "ImageWindow.h"
#include "ui_Imagewindow.h"
#include "ProcessedImageScene.h"

#include "Grayscale.h"
#include "InvertColors.h"
#include "BinaryImage.h"
#include "MirrorImage.h"
#include "HistogramViewer.h"
#include "HistogramEqualizer.h"

#include "ImageModifierFactory.h"
#include "ImageModifierNames.h"

#include <iostream>
#include <memory>

#include <qfiledialog.h>
#include <qgraphicsitem.h>
#include <qevent.h>
#include <qscrollbar.h>

ImageWindow::ImageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui_ImageWindow())
{
    ui->setupUi(this);
    
    m_initialImage = new ProcessedImageScene();
    m_modifiedImage = new ProcessedImageScene();
    ui->graphicsViewModified->setScene(m_modifiedImage);
    ui->graphicsViewInitial->setScene(m_initialImage);

    connect(ui->graphicsViewInitial->horizontalScrollBar(), &QScrollBar::valueChanged,ui->graphicsViewModified->horizontalScrollBar(), &QScrollBar::setValue);
    connect(ui->graphicsViewInitial->verticalScrollBar(),   &QScrollBar::valueChanged,ui->graphicsViewModified->verticalScrollBar(),   &QScrollBar::setValue);

    connect(ui->graphicsViewModified->horizontalScrollBar(), &QScrollBar::valueChanged, ui->graphicsViewInitial->horizontalScrollBar(), &QScrollBar::setValue);
    connect(ui->graphicsViewModified->verticalScrollBar(), &QScrollBar::valueChanged, ui->graphicsViewInitial->verticalScrollBar(), &QScrollBar::setValue);


    connect(m_initialImage, &ProcessedImageScene::selectedImage, m_modifiedImage, &ProcessedImageScene::setSelectedImage);

    connect(ui->actionGreyscale,     &QAction::triggered, this, &ImageWindow::loadGreyscaleImage);
    connect(ui->actionColor,         &QAction::triggered, this, &ImageWindow::loadColorImage);
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


void ImageWindow::loadGreyscaleImage()
{
    std::unique_ptr<QImage> image =std::make_unique<QImage>();
    image.reset(loadImage());

    Grayscale grayscaleModifier;
    QImage* grayscaleImage = grayscaleModifier.modify(image.get());   

    m_initialImage->clear();
    m_initialImage->addImage(grayscaleImage);
}

void ImageWindow::loadColorImage()
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
    Histogram histogram(m_initialImage->getImage());

    HistogramViewer* histogramViewer = new HistogramViewer(histogram);
    histogramViewer->display();
}

void ImageWindow::selectImage()
{
    m_initialImage->toggleSelection();
}

void ImageWindow::colorHistogramEqualization()
{
    ImageModifierFactory factory;

    auto modifier = factory.createNewImageModifier(ImageModifierNames::ColorHistogramEqualization);

    //HistogramEqualizer equalizer;
    QImage* image = modifier->modify(m_initialImage->getImage());
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
