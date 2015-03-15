#include <QMessageBox>

#include "kolyosa.h"

#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setupUi(this);

    ___instum = mainToolBar;
    ___podskaz = mainStatusBar;
    ___dela = mainMenuBar;
    ___okno = this;

    QMenu* menu0 = mainMenuBar->addMenu(QApplication::tr("Перво-наперво"));
//    QMenu* menu1 = mainMenuBar->addMenu(QApplication::tr("Управление"));

    QWidget* w = (QWidget*)( (*___plugs)["izvozcik"]->addNewObj("vse_uclugi","mainCentralWidget", this) );
    if (w == nullptr) {
        QString serr = QApplication::tr("При создании главного окна дополнением произошла ошибка!!!\nВыход...");
        ___err(serr);
    } else setCentralWidget(w);

    QObject* proba = (*___plugs)["izvozcik"]->addNewObj("proba","proba1", nullptr);

//    QMenu* menu999 = mainMenuBar->addMenu(QApplication::tr("Помощь..."));

    {
        menu0->addSeparator();
        QAction* actSetup = menu0->addAction(QIcon("://kcontrol.png"),"Установки...");
        menu0->addSeparator();
        QAction* actExit = menu0->addAction(QIcon("://window_list.png"),"Выход...");

        mainToolBar->addSeparator();
        mainToolBar->addActions(QList<QAction*>() << actSetup);
        mainToolBar->addSeparator();
        mainToolBar->addActions(QList<QAction*>() << actExit);

        connect(actExit, SIGNAL(triggered()), qApp, SLOT(closeAllWindows()));
        connect(actSetup, SIGNAL(triggered()), this, SLOT(runSetup()));
    };

    restoreState(___stt->value("stte").toByteArray());
    restoreGeometry(___stt->value("geom").toByteArray());

    bool tbshw = ___stt->value("main/tbsh").toBool();
    mainToolBar->setVisible(tbshw);
    if (tbshw)
        mainToolBar->restoreGeometry(___stt->value("main/tbgm").toByteArray());
    tbshw = ___stt->value("main/stsh").toBool();
    mainStatusBar->setVisible(tbshw);
}

MainWindow::~MainWindow() {
    (*___plugs)["izvozcik"]->deleteObj("proba1");

    if (___stt->value("main/tbsh").toBool() == true)
        ___stt->setValue(
                    "main/tbgm",
                    mainToolBar->saveGeometry()
                    );
    else ___stt->remove("main/tbgm");
    ___stt->setValue("geom", saveGeometry());
    ___stt->setValue("stte", saveState());
}

void MainWindow::changeEvent(QEvent *e) {
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::runSetup() {
    QDialog* dlg = (QDialog*)( (*___plugs)["izvozcik"]->addNewObj("vse_setups","dialogSetups", this) );
    if (dlg == nullptr) return;
    dlg->exec();
    if(!((*___plugs)["izvozcik"]->deleteObj(dlg)))
        delete dlg;
}
