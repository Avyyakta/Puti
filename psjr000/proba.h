#ifndef PROBA_H
#define PROBA_H

#include <QObject>

class Proba : public QObject
{
    Q_OBJECT
public:
    explicit Proba(QObject *parent = 0);
    ~Proba();

signals:

public slots:
};

#endif // PROBA_H
