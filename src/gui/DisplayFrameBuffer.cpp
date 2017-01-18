#include "gui/DisplayFrameBuffer.h"
#include <QQuickWindow>

DisplayFrameBuffer::DisplayFrameBuffer():
	parent(Q_NULLPTR),
	renderer(Q_NULLPTR)
{}

QOpenGLFramebufferObject* DisplayFrameBuffer::createFramebufferObject(const QSize &size)
{
	QOpenGLFramebufferObjectFormat format;
	return new QOpenGLFramebufferObject(size, format);
}

void DisplayFrameBuffer::synchronize(QQuickFramebufferObject *item)
{
	this->parent = item;

	if (!renderer)
		renderer = new DisplayRenderer();
}

void DisplayFrameBuffer::render()
{
	if (renderer)
		renderer->render();
	if (parent)
		parent->window()->resetOpenGLState();
}

DisplayFrameBuffer::~DisplayFrameBuffer()
{
	if (renderer)
			delete renderer;
}
