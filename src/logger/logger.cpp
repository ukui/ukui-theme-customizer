#include "logger.h"

static logger standardLog;

void logger::log(QString s) {
    if (s != m_msg) {
        m_msg = s;
        emit msgChanged(m_msg);
    }
}

logger::logger::logger() {}

logger::~logger() noexcept {}

logger& logger::getStandardLogger() {
    return standardLog;
}

