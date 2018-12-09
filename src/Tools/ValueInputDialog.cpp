#include "ValueInputDialog.h"
#include <qformlayout.h>
#include <qlabel.h>
#include <qlist.h>
#include <qlineedit.h>
#include <qdialogbuttonbox.h>

ValueInputDialog::ValueInputDialog(size_t nrFields):m_nrFields(nrFields),QDialog(),form(this)
{
    // Add some text above the fields
    form.addRow(new QLabel("Values"));

    // Add the lineEdits with their respective labels

    for (int i = 0; i < m_nrFields; ++i) {
        QLineEdit *lineEdit = new QLineEdit(this);
        QString label = QString("Value %1").arg(i + 1);
        form.addRow(label, lineEdit);

        m_fields << lineEdit;
    }

    // Add some standard buttons (Cancel/Ok) at the bottom of the dialog
    //QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    QDialogButtonBox* buttonBox=new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    form.addRow(buttonBox);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

std::vector<double> ValueInputDialog::show()
{
    std::vector<double> values;

    if (this->exec() == QDialog::Accepted) {    
        for (QLineEdit * lineEdit : m_fields) {
            values.push_back(lineEdit->text().toDouble());
        }
    }
    return values;
}
