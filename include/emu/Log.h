#ifndef KPICO_LOG_H
#define KPICO_LOG_H

#include <QObject>
#include <QString>

extern "C"
{
#include <z80e/log/log.h>
}

class Log: public QObject
{
	Q_OBJECT
private:
	log_t *mLog;

public:
	Log();
	~Log();
	log_t* log();

signals:
	void message(loglevel_t level, QString message);
};

#endif // KPICO_LOG_H
