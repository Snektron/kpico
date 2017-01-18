#ifndef DISPLAYFRAMEBUFFER_H
#define DISPLAYFRAMEBUFFER_H

#include <QOpenGLFramebufferObject>
#include <QQuickFramebufferObject>
#include <QQuickItem>
#include "gui/DisplayRenderer.h"

class DisplayFrameBuffer: public QQuickFramebufferObject::Renderer
{
private:
	QQuickFramebufferObject *parent;
	DisplayRenderer *renderer;

public:
	DisplayFrameBuffer();
	QOpenGLFramebufferObject* createFramebufferObject(const QSize &size);
	void synchronize(QQuickFramebufferObject *item);
	void render();
	~DisplayFrameBuffer();
};

#endif // DISPLAYFRAMEBUFFER_H
