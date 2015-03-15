#ifndef DLGSETUP_H
#define DLGSETUP_H

#include "ui_dlgsetup.h"

class DlgSetup : public QDialog, private Ui::DlgSetup
{
    Q_OBJECT

public:
    explicit DlgSetup(QWidget *parent = 0);
    ~DlgSetup();

protected:
    void changeEvent(QEvent *e);
private slots:
};

#endif // DLGSETUP_H
