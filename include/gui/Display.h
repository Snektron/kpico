#ifndef DISPLAY_H
#define DISPLAY_H

#include <QQuickFramebufferObject>
#include <picore/PluginEngine.h>

class Display: public QQuickFramebufferObject
{
	Q_OBJECT
private:

public:
	Display();
	QQuickFramebufferObject::Renderer* createRenderer() const;
};

#endif // DISPLAY_H
