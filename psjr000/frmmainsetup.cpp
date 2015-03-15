#include "kolyosa.h"
#include "frmmainsetup.h"

FrmMainSetup::FrmMainSetup(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);
    checkBox->setChecked(___stt->value("main/tbsh").toBool());
    checkBox_2->setChecked(___stt->value("main/stsh").toBool());
}

FrmMainSetup::~FrmMainSetup() {
//    ___inf("call FrmMainSetup::~FrmMainSetup()...");
}

void FrmMainSetup::changeEvent(QEvent *e)
{
    QWidget::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void FrmMainSetup::on_checkBox_stateChanged(int arg1) {
    switch(arg1) {
    case Qt::Unchecked: {
        ___stt->setValue("main/tbsh", false);
        if (___instum) ___instum->setVisible(false);
    }; break;
    case Qt::Checked: {
        ___stt->setValue("main/tbsh", true);
        if (___instum) ___instum->setVisible(true);
    }; break;
    }
}

void FrmMainSetup::on_checkBox_2_stateChanged(int arg1)
{
    switch(arg1) {
    case Qt::Unchecked: {
        ___stt->setValue("main/stsh", false);
        if (___podskaz)
            ___podskaz->setVisible(false);
    }; break;
    case Qt::Checked: {
        ___stt->setValue("main/stsh", true);
        if (___podskaz)
            ___podskaz->setVisible(true);
    }; break;
    }
}
