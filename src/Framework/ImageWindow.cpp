#include "ImageWindow.h"
#include "ui_Imagewindow.h"
#include "ProcessedImageScene.h"

#include "Grayscale.h"
#include "HistogramViewer.h"

#include "ImageModifierFactory.h"
#include "ImageModifierNames.h"

#include <iostream>
#include <memory>

#include <qfiledialog.h>
#include <qgraphicsitem.h>
#include <qevent.h>
#include <qscrollbar.h>
#include <QtConcurrent\qtconcurrentrun.h>

ImageWindow::ImageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui_ImageWindow())
{
    ui->setupUi(this);
    
    m_initialImage = new ProcessedImageScene();
    m_modifiedImage = new ProcessedImageScene();
    ui->graphicsViewModified->setScene(m_modifiedImage);
    ui->graphicsViewInitial->setScene(m_initialImage);

    // make scrollbars scroll at the same time
    QObject::connect(ui->graphicsViewInitial->horizontalScrollBar(),  &QScrollBar::valueChanged,ui->graphicsViewModified->horizontalScrollBar(), &QScrollBar::setValue);
    QObject::connect(ui->graphicsViewInitial->verticalScrollBar(),    &QScrollBar::valueChanged,ui->graphicsViewModified->verticalScrollBar(),   &QScrollBar::setValue);
    QObject::connect(ui->graphicsViewModified->horizontalScrollBar(), &QScrollBar::valueChanged,ui->graphicsViewInitial->horizontalScrollBar(),  &QScrollBar::setValue);
    QObject::connect(ui->graphicsViewModified->verticalScrollBar(),   &QScrollBar::valueChanged,ui->graphicsViewInitial->verticalScrollBar(),    &QScrollBar::setValue);

    QObject::connect(ui->horizontalSliderZoom,                        &QSlider::valueChanged,   this,                                            &ImageWindow::sliderZoom);

    //sends an image from a scene to another
    QObject::connect(m_initialImage, &ProcessedImageScene::selectedImage, m_modifiedImage, &ProcessedImageScene::setSelectedImage);

    //connects the menu items to slots
    QObject::connect(ui->actionInvert_colors,                &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionBinary_image,                 &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionMirror_image,                 &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionColor_Histogram_Equalization, &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionOtsu_binarization,            &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->action3x3,                          &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->action5x5,                          &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionCanny,                        &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionGauss_filter,                 &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionSobel,                        &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionZheng_Suen,                   &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionBicubic,                      &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionHough,                        &QAction::triggered, this, &ImageWindow::imageModifierClicked);
    QObject::connect(ui->actionIntermeans,                   &QAction::triggered, this, &ImageWindow::imageModifierClicked);

    QObject::connect(ui->actionGreyscale,                    &QAction::triggered, this, &ImageWindow::loadGreyscaleImage);
    QObject::connect(ui->actionColor,                        &QAction::triggered, this, &ImageWindow::loadColorImage);
    QObject::connect(ui->actionGrayscaleHistogram,           &QAction::triggered, this, &ImageWindow::histogram);
    QObject::connect(ui->actionValueHistogram,               &QAction::triggered, this, &ImageWindow::histogram);

    QObject::connect(ui->actionSelect_image,                 &QAction::triggered, this, &ImageWindow::selectImage);
    QObject::connect(ui->actionMagnifier,                    &QAction::triggered, this, &ImageWindow::magnifyImage);
    QObject::connect(ui->actionMean,                         &QAction::triggered, this, &ImageWindow::meanColors);
    QObject::connect(ui->actionPlotter,                      &QAction::triggered, this, &ImageWindow::plotter);
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

void ImageWindow::histogram()
{
    QAction* selectedItem = dynamic_cast<QAction*>(QObject::sender());

    auto grayscaleHistogram = [](auto image) {
        if (image != nullptr) {
            GrayscaleHistogram histogram(image);

            HistogramViewer* histogramViewer = new HistogramViewer(histogram);
            histogramViewer->display();
        }
    };

    auto valueHistogram = [](auto image) {
        if (image != nullptr) {
            ValueHistogram histogram(image);

            HistogramViewer* histogramViewer = new HistogramViewer(histogram);
            histogramViewer->display();
        }
    };

    if (selectedItem->objectName() == ui->actionGrayscaleHistogram->objectName()) {
        grayscaleHistogram(m_initialImage->getImage());
        grayscaleHistogram(m_modifiedImage->getImage());
    } else if (selectedItem->objectName() == ui->actionValueHistogram->objectName()) {
        valueHistogram(m_initialImage->getImage());
        valueHistogram(m_modifiedImage->getImage());
    }
}

void ImageWindow::selectImage()
{
    m_initialImage->toggleSelection();
}

void ImageWindow::magnifyImage()
{
    m_initialImage->toggleMagnifier();
    m_modifiedImage->toggleMagnifier();
}

void ImageWindow::meanColors()
{
    m_modifiedImage->toggleMean();
    m_initialImage->toggleMean();
}

void ImageWindow::imageModifierClicked()
{
    QAction* selectedItem=dynamic_cast<QAction*>(QObject::sender());

    ImageModifierFactory factory;

    //auto f = [&]() {
        auto modifier = factory.createNewImageModifier(selectedItem->text().toStdString());
        QImage* image = modifier->modify(m_initialImage->getImage());
        delete modifier;
        setModifiedImage(image);
        m_initialImage->setSelectedImage(m_initialImage->getImage());
   // };
   // QtConcurrent::run(f);
}

void ImageWindow::plotter()
{
    m_initialImage->togglePlotter();
}

void ImageWindow::sliderZoom(int value)
{
    double scaleFactor = 0.0;

    if (value < sliderZoomValue) {
        scaleFactor = 1/1.05;
        sliderZoomValue = value;
    } else {
        scaleFactor = 1.05;
        sliderZoomValue = value;
    }

    ui->graphicsViewInitial->scale(scaleFactor, scaleFactor);
    ui->graphicsViewModified->scale(scaleFactor, scaleFactor);
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
