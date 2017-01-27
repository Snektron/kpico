#include "gui/Lcd.h"
#include "gui/LcdFrameBuffer.h"

Lcd::Lcd()
{
	setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
	setAcceptHoverEvents(true);
}

QQuickFramebufferObject::Renderer* Lcd::createRenderer() const
{
	return new LcdFrameBuffer();
}
