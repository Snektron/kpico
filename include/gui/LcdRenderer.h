#ifndef DISPLAYRENDERER_H
#define DISPLAYRENDERER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QObject>

class LcdRenderer: public QObject, public QOpenGLFunctions
{
	Q_OBJECT
private:
	QOpenGLShaderProgram *shader;
	QOpenGLTexture *texture;

public:
	LcdRenderer();
	void render();
	~LcdRenderer();

public slots:
	void onLcdChanged();
};

#endif // DISPLAYRENDERER_H
