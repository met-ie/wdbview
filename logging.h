#ifndef LOGGING_H
#define LOGGING_H

#include <QDebug>

namespace internal
{
class Logger
{
public:
    Logger(const char * function)
    {
        qDebug() << function;
    }
    ~Logger()
    {
        qDebug() << "done";
    }
};
}


#define LOG_FUNCTION internal::Logger logger_(__func__);


#endif // LOGGING_H
