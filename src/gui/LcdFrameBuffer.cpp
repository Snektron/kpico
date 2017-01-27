#include "gui/LcdFrameBuffer.h"
#include <QQuickWindow>
#include <QObject>
#include "gui/Lcd.h"

LcdFrameBuffer::LcdFrameBuffer():
	parent(Q_NULLPTR),
	renderer(Q_NULLPTR)
{}

QOpenGLFramebufferObject* LcdFrameBuffer::createFramebufferObject(const QSize &size)
{
	QOpenGLFramebufferObjectFormat format;
	return new QOpenGLFramebufferObject(size, format);
}

void LcdFrameBuffer::synchronize(QQuickFramebufferObject *item)
{
	this->parent = item;

	if (!renderer)
	{
		renderer = new LcdRenderer();
		Lcd *d = qobject_cast<Lcd*>(item);
		QObject::connect(d, SIGNAL(lcdChanged()), renderer, SLOT(onLcdChanged()));
	}
}

void LcdFrameBuffer::render()
{
	if (renderer)
		renderer->render();
	if (parent)
		parent->window()->resetOpenGLState();
}

LcdFrameBuffer::~LcdFrameBuffer()
{
	if (renderer)
		delete renderer;
}
