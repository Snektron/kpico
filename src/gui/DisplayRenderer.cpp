#include "gui/DisplayRenderer.h"

const float vertices[] =
{
	-1, -1,
	 1, -1,
	-1,  1,
	 1,  1
};

const float texcoords[] =
{
	0, 0,
	1, 0,
	0, 1,
	1, 1
};

DisplayRenderer::DisplayRenderer()
{
	initializeOpenGLFunctions();
	shader = new QOpenGLShaderProgram();
	shader->addShaderFromSourceFile(QOpenGLShader::Vertex, QStringLiteral(":/shaders/Display.vsh"));
	shader->addShaderFromSourceFile(QOpenGLShader::Fragment, QStringLiteral(":/shaders/Display.fsh"));
	shader->bindAttributeLocation("aVertices", 0);
	shader->bindAttributeLocation("aTexCoords", 1);
	shader->link();

	texture = new QOpenGLTexture(QImage(":/textures/palette.png").mirrored());
	texture->setMinificationFilter(QOpenGLTexture::Nearest);
	texture->setMagnificationFilter(QOpenGLTexture::Nearest);

	shader->bind();
	shader->setUniformValue("uTexture", 0);
	shader->release();
}

void DisplayRenderer::render()
{
	shader->bind();

	shader->enableAttributeArray(0);
	shader->setAttributeArray(0, GL_FLOAT, vertices, 2);
	shader->enableAttributeArray(1);
	shader->setAttributeArray(1, GL_FLOAT, texcoords, 2);

	texture->bind(0);

	glDisable(GL_DEPTH_TEST);

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	shader->disableAttributeArray(1);
	shader->disableAttributeArray(0);

	shader->release();
}

DisplayRenderer::~DisplayRenderer()
{
	delete shader;
	delete texture;
}
