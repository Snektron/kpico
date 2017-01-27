#ifndef DISPLAYFRAMEBUFFER_H
#define DISPLAYFRAMEBUFFER_H

#include <QOpenGLFramebufferObject>
#include <QQuickFramebufferObject>
#include <QQuickItem>
#include "gui/LcdRenderer.h"

class LcdFrameBuffer: public QQuickFramebufferObject::Renderer
{
private:
	QQuickFramebufferObject *parent;
	LcdRenderer *renderer;

public:
	LcdFrameBuffer();
	QOpenGLFramebufferObject* createFramebufferObject(const QSize &size);
	void synchronize(QQuickFramebufferObject *item);
	void render();
	~LcdFrameBuffer();
};

#endif // DISPLAYFRAMEBUFFER_H
