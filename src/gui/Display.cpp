#include "gui/Display.h"
#include "gui/DisplayFrameBuffer.h"

Display::Display()
{
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	setAcceptHoverEvents(true);
}

QQuickFramebufferObject::Renderer* Display::createRenderer() const
{
	return new DisplayFrameBuffer();
}
