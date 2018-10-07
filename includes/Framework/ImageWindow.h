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
    void loadGreyscale();
    void loadColor();
    void invertColors();
    void mirrorImage();
    void binaryImage();
    void histogram();
    void selectImage();

private:

    void setModifiedImage(QImage* image);

    QImage* loadImage();

    ProcessedImageScene* m_initialImage;
    ProcessedImageScene* m_modifiedImage;
    Ui_ImageWindow *ui;
};
