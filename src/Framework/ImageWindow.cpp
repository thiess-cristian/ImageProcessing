#include "ImageWindow.h"
#include "ui_Imagewindow.h"


ImageWindow::ImageWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui_ImageWindow())
{
    ui->setupUi(this);
}

ImageWindow::~ImageWindow()
{
    delete ui;
}