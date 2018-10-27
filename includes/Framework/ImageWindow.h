#pragma once

#include <QMainWindow>
#include <memory>

class Ui_ImageWindow;
class ProcessedImageScene;

class ImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = 0);
    ~ImageWindow();

protected slots:
    void loadGreyscaleImage();
    void loadColorImage();
    void histogram();
    void selectImage();
    void magnifyImage();
    void meanColors();
    void imageModifierClicked();
    void plotter();

    void sliderZoom(int value);

private:
    int sliderZoomValue=50;
    void setModifiedImage(QImage* image);

    QImage* loadImage();

    ProcessedImageScene* m_initialImage;
    ProcessedImageScene* m_modifiedImage;
    Ui_ImageWindow *ui;
};
