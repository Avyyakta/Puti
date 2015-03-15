#include <QMutex>
#include <QDateTime>
#include <QTextStream>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMessageBox>

#include "logger.h"

bool Logger::___reject_file() {
    if (___file.size() < MAX_LOG_FILE_SIZE) return true;
    QString oldNm = ___file.fileName();
    QString newNm = QApplication::applicationFilePath().remove(QRegExp("\\.exe$")).remove(QRegExp("\\.so{0,1}$")).append(QDateTime::currentDateTime().toString("_yyyyMMddhhmmsszzz")).append(".log");
    ___file.close();
    ___vld = ___file.rename(oldNm, newNm);
    if (!___vld) {
        QMessageBox mb(QMessageBox::Critical, QApplication::tr("Ошибка..."), QApplication::tr("При переименовании старого лог-файла (%1) произошла ошибка...\nОшибка : %2").arg(___file.fileName()).arg(___file.errorString())); mb.exec();
        return false;
    };
    ___vld = ___file.open(QIODevice::Text|QIODevice::Append|QIODevice::WriteOnly);
    if (!___vld) {
        QMessageBox mb(QMessageBox::Critical, QApplication::tr("Ошибка..."), QApplication::tr("При создании нового лог-файла (%1) произошла ошибка...\nОшибка : %2").arg(___file.fileName()).arg(___file.errorString())); mb.exec();
        return false;
    };
    return true;
}

Logger::Logger(QObject *parent) :
    QObject(parent),
    ___showDT(true),
    ___file(),
    ___vld(false),
    ___lastStr(),
    ___sprtr(' ')
{
    ___file.setFileName(QApplication::applicationFilePath().remove(QRegExp("\\.exe$")).remove(QRegExp("\\.so{0,1}$")).append(".log"));
    ___vld = ___file.open(QIODevice::Text|QIODevice::Append|QIODevice::WriteOnly);
    if (!___vld) {
        QMessageBox mb(QMessageBox::Critical, QApplication::tr("Ошибка..."), QApplication::tr("При открытии лог-файла (%1) произошла ошибка...\nОшибка : %2").arg(___file.fileName()).arg(___file.errorString())); mb.exec();
        return;
    };
    ___reject_file();
    {
        QTextStream ts(&___file); ts.setCodec("UTF-8");
        ts << "\n" << QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz ")
           << QString("═══ Start ═════════════════════════════════════════════════╗");
        ts.flush(); ___file.flush();
    };
    ___lastLogger = this;
}

Logger::~Logger() {
    {
        QTextStream ts(&___file); ts.setCodec("UTF-8");
        ts << "\n" << QDateTime::currentDateTime().toString("yyyyMMddhhmmsszzz ")
           << QString("═══ Stop ══════════════════════════════════════════════════╝\n");
        ts.flush(); ___file.flush();
    };
    if (___vld)
        if (___file.isOpen())
            ___file.close();
    ___lastStr.clear();
}

void Logger::write(const QString& msg, bool bapp) {
    if (this == nullptr) return;
    if (!___vld) return;
    ___lastStr = msg;
    if (___lastStr.isEmpty() && !___showDT) return;
    QTextStream ts(&___file); ts.setCodec("UTF-8");
    QMutex mutex; mutex.lock();
    if (!bapp) {
        ts << "\n";
        if (___showDT)
            ts << QDateTime::currentDateTime().toString("MMddhhmmss ");
    }
    ts << ___lastStr; ts.flush(); ___file.flush(); ___reject_file();
    mutex.unlock();
}

Logger& Logger::__wr(const QString& msg, enum LoggerWriteType wt, bool bapp) {
    Logger* _this = this;
    if (_this == nullptr) {
        if (___lastLogger == nullptr) return *_this;
        _this = ___lastLogger;
    };
    if (!_this->___vld) return *_this;
    _this->___lastStr = msg;
    if (_this->___lastStr.isEmpty() && !___showDT) return *this;
    QTextStream ts(&_this->___file); ts.setCodec("UTF-8");
    QString pre = "";
    QMutex mutex; mutex.lock();
    if (!bapp) {
        ts << "\n";
        if (___showDT) pre = QDateTime::currentDateTime().toString("MMddhhmmss");
        switch (wt) {
        case error:       pre.append(QApplication::tr(" Ошибка:\n\t")); break;
        case warning:     pre.append(QApplication::tr(" Предупреждение:\n\t")); break;
        case information: pre.append(QApplication::tr(" Информация:\n\t")); break;
        default: break;
        };
    } else ts << ___sprtr;
    ts << pre << _this->___lastStr;
    ts.flush(); _this->___file.flush(); _this->___reject_file();
    mutex.unlock();
    return *this;
}

Logger& log(const QString& msg, enum LoggerWriteType wt) {
    Logger* lg = Logger::___lastLogger; if (lg==nullptr) return *lg;
    return lg->__wr(msg, wt, false);
}

Logger* Logger::___lastLogger = nullptr;
