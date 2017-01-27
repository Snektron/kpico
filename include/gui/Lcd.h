#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>

class Lcd: public QQuickFramebufferObject
{
	Q_OBJECT
public:
	Lcd();
	QQuickFramebufferObject::Renderer* createRenderer() const;

signals:
	void lcdChanged();
};

#endif // DISPLAY_H
