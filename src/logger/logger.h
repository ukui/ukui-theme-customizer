#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>

class logger: public QObject
{
        Q_OBJECT
signals:
    void msgChanged(const QString & s);

public:
    logger() = default;
    ~logger() = default;
    void log(const QString & s) {
        if (s != m_msg) {
            m_msg = s;
            emit msgChanged(m_msg);
        }
    }
    QString m_msg;
}standardLog;

#endif // LOGGER_H
