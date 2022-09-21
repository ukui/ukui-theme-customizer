#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class logger: public QObject
{
        Q_OBJECT
signals:
    void msgChanged(const QString & s);

public:
    static logger & getStandardLogger();
    logger();
    ~logger();
    void log(QString s);

private:
    QString m_msg;
};

#endif // LOGGER_H
