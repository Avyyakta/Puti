#include "frmvseuslugi.h"

#include "kolyosa.h"

FrmVseUslugi::FrmVseUslugi(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

}

FrmVseUslugi::~FrmVseUslugi() {
//    ___inf("call FrmVseUslugi::~FrmVseUslugi()");
}

void FrmVseUslugi::changeEvent(QEvent *e)
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
