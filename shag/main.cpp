#include "mainwindow.h"
#include <QApplication>
#include <QSettings>
#include "kolyosa.h"

int main(int argc, char *argv[])
{   int ret_code = -1;
    {   QApplication a(argc, argv);
        {   Logger currentLogger(&a);
            {   QSettings currentSettings(
                            QApplication::applicationFilePath().replace(QRegExp("\\.exe$"),".ini").replace(QRegExp("\\.EXE$"),".ini"),
                            QSettings::IniFormat,
                            &a
                            );
                ___stt = &currentSettings;
//                {   PrgPlugins currentPlgins(&a);
                {   PLuginsMap plgMap;
//                    ___plugs = &plgMap;
                    {   MainWindow w;
                        w.show();

                        ret_code = a.exec();
                    };
                }; // ___plugs = nullptr;
            }; ___stt = nullptr;
        };
    };
    return ret_code;
}
