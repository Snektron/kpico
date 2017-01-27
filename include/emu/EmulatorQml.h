#ifndef CONNECTORS_H
#define CONNECTORS_H

#include <QObject>
#include <QUrl>

class AsicQml: public QObject
{
	Q_OBJECT
signals:
	void onLcdChanged();
	void loadRom(QUrl filename);
};

class DebuggerQml: public QObject
{
	Q_OBJECT
signals:
	void command(QString command);
};

#endif // CONNECTORS_H
