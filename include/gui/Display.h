#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>

class Display: public QQuickFramebufferObject
{
	Q_OBJECT
public:
	Display();
	QQuickFramebufferObject::Renderer* createRenderer() const;
};

#endif // DISPLAY_H
