#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QApplication>

#include "kolyosa_global.h"

enum LoggerWriteType {
    none,
    error,
    warning,
    information
};

class _SHARED_EXPORT Logger : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool showDateTime MEMBER ___showDT)
    Q_PROPERTY(QString log READ getLog WRITE setLog)

    bool    ___showDT;
    QFile   ___file;
    bool    ___vld;
    QString ___lastStr;
    QChar   ___sprtr;

    static Logger* ___lastLogger;

    bool ___reject_file();

    friend Logger& log(const QString& msg, enum LoggerWriteType wt);
    friend int ::qMain(int argc, char *argv[]);
public:
    explicit Logger(QObject *parent = 0) _SHARED_EXPORT;
    ~Logger() _SHARED_EXPORT;

    Logger& __wr(const QString& msg, enum LoggerWriteType wt = none, bool bapp = false) _SHARED_EXPORT;

    bool getDateTimeShow() { return ___showDT; }

    QString getLog() { return ___lastStr; }
    void setLog(const QString& msg) { __wr(msg, none, true); }
    void setSeparator(const QChar& c) { ___sprtr = c; }

    Logger& operator<<(const QString& msg) { return __wr(msg, none, true); }

    static Logger& getLogger() { return *___lastLogger; }

signals:

public slots:
    void setDateTimeShow(bool v) { ___showDT = v; }
    void write(const QString& msg, bool bapp = false) _SHARED_EXPORT;

};

extern _SHARED_EXPORT Logger& log(const QString& msg, enum LoggerWriteType wt = none);

#define ___log Logger::getLogger()

#define ___err(a) ::log((a), LoggerWriteType::error)
#define ___wrn(a) ::log((a), LoggerWriteType::warning)
#define ___inf(a) ::log((a), LoggerWriteType::information)
#define ___wrt(a) ::log((a), LoggerWriteType::none)

#define __err ::log("", LoggerWriteType::error)
#define __wrn ::log("", LoggerWriteType::warning)
#define __inf ::log("", LoggerWriteType::information)
#define __wrt ::log("", LoggerWriteType::none)

#define _err Logger::getLogger().__wr("", LoggerWriteType::error)
#define _wrn Logger::getLogger().__wr("", LoggerWriteType::warning)
#define _inf Logger::getLogger().__wr("", LoggerWriteType::information)
#define _wrt Logger::getLogger().__wr("", LoggerWriteType::none)

#ifdef IS_DEBUG
#define MAX_LOG_FILE_SIZE (1024*4)
#else
#define MAX_LOG_FILE_SIZE (1024*1024*64)
#endif

#endif // LOGGER_H
