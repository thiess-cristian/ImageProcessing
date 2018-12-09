#pragma once

#include <qdialog.h>
#include <qlist.h>
#include <qlineedit.h>
#include <qformlayout.h>

class ValueInputDialog :public QDialog
{
public:
    ValueInputDialog(size_t fields);
    std::vector<double> ValueInputDialog::show();

private:
    size_t m_nrFields;
    QList<QLineEdit *> m_fields;
    QFormLayout form;
};