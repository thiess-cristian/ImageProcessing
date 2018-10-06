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

public slots:
    void loadGreyscale();
    void loadColor();
    void invertColors();

private:
    QImage* getImage();

    ProcessedImageScene* m_initialImage;
    ProcessedImageScene* m_modifiedImage;
    Ui_ImageWindow *ui;
};
