#pragma once

#include <QMainWindow>

class Ui_ImageWindow;


class ImageWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ImageWindow(QWidget *parent = 0);
    ~ImageWindow();

private:
    Ui_ImageWindow *ui;
};
