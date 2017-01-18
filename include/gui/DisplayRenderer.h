#ifndef DISPLAYRENDERER_H
#define DISPLAYRENDERER_H

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QObject>

class DisplayRenderer: public QObject, public QOpenGLFunctions
{
	Q_OBJECT
private:
	QOpenGLShaderProgram *shader;
	QOpenGLTexture *texture;

public:
	DisplayRenderer();
	void render();
	~DisplayRenderer();
};

#endif // DISPLAYRENDERER_H
