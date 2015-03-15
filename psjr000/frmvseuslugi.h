#ifndef FRMVSEUSLUGI_H
#define FRMVSEUSLUGI_H

#include "ui_frmvseuslugi.h"

class FrmVseUslugi : public QWidget, private Ui::FrmVseUslugi
{
    Q_OBJECT

public:
    explicit FrmVseUslugi(QWidget *parent = 0);
    ~FrmVseUslugi();

public slots:

protected:
    void changeEvent(QEvent *e);
};

#endif // FRMVSEUSLUGI_H
