#include "emu/Log.h"

void logCbk(void *data, loglevel_t level, const char *part, const char *message, va_list args)
{
	Q_UNUSED(part)

	Log *log = (Log*) data;
	emit log->message(level, QString::vasprintf(message, args));
	va_end(args);
}

Log::Log():
	mLog(init_log_z80e(logCbk, this, L_DEBUG))
{}

Log::~Log()
{
	free_log(mLog);
}

log_t* Log::log()
{
	return mLog;
}
