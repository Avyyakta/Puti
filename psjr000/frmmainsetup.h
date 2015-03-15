#ifndef FRMMAINSETUP_H
#define FRMMAINSETUP_H

#include "ui_frmmainsetup.h"

class FrmMainSetup : public QWidget, private Ui::FrmMainSetup
{
    Q_OBJECT

public:
    explicit FrmMainSetup(QWidget *parent = 0);
    ~FrmMainSetup();

protected:
    void changeEvent(QEvent *e);
private slots:
    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
};

#endif // FRMMAINSETUP_H
