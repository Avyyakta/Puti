#include "kolyosa.h"
#include "dlgsetup.h"

DlgSetup::DlgSetup(QWidget *parent) :
    QDialog(parent)
{
    setupUi(this);

    {
        if (!(___plugs->isEmpty())) {
//            ___soob("0");
            QStringList slp = ___plugs->keys();
            if (!(slp.isEmpty())) {
//                ___soob("1");
                foreach(QString v, slp) {
//                    ___soob(v);
                    QWidget* w = (QWidget*)((*___plugs)[v]->addNewObj("page_setup",v+"_pgStp", stackedWidget));
                    if (w) {
                        stackedWidget->addWidget(w);
                        QWidget* pgStpW = new QWidget();
                        pgStpW->setGeometry(page->geometry());
                        QVBoxLayout* vrtStpL = new QVBoxLayout(pgStpW);
                        vrtStpL->setObjectName(QString("vbl_%1").arg((qlonglong)vrtStpL));
                        QLabel* lbl = new QLabel(pgStpW);
                        lbl->setObjectName(QString("lbl_%1").arg((qlonglong)lbl));
                        if (!(w->windowIcon().isNull())) {
                            lbl->setPixmap(w->windowIcon().pixmap(label_5->width()-3, label_5->height()-3));
                        }
                        else lbl->setText("***");
                        vrtStpL->addWidget(lbl);
                        toolBox->addItem(pgStpW, w->windowTitle());
                    };
                };
            };
        };
    };

    int cp = ___stt->value("main/stnp",(int)0).toInt();
    if (cp >= toolBox->count()) cp = toolBox->count() - 1;
    toolBox->setCurrentIndex(cp);
    splitter->restoreState(___stt->value("main/stss").toByteArray());
    splitter->restoreGeometry(___stt->value("main/stsg").toByteArray());

    restoreGeometry(___stt->value("main/stgm").toByteArray());

}

DlgSetup::~DlgSetup() {
    ___stt->setValue("main/stgm", saveGeometry());
    ___stt->setValue("main/stsg", splitter->saveGeometry());
    ___stt->setValue("main/stss", splitter->saveState());
    ___stt->setValue("main/stnp", toolBox->currentIndex());
    ___stt->sync();
//    ___inf("call DlgSetup::~DlgSetup()...");

}

void DlgSetup::changeEvent(QEvent *e) {
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}
