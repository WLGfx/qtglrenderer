#ifndef WINDOW_H
#define WINDOW_H

#include <QDebug>

#include <QOpenGLWindow>
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QMatrix4x4>
#include <QQuaternion>
#include <QVector2D>
#include <QBasicTimer>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include <QFont>
#include <QFontMetrics>
#include <QString>
#include <QPainter>

#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

//class Window : public QOpenGLWidget, protected QOpenGLFunctions
class Window : public QOpenGLWindow, protected QOpenGLFunctions
{
	Q_OBJECT

public:
	explicit Window();
	~Window();

	QVector2D		mouse_press_position;
	bool			mouse_left_button;
	bool			mouse_right_button;

	int				width, height;

	QOpenGLShaderProgram	shader_color;
	QOpenGLShaderProgram	shader_texture;
	QOpenGLShaderProgram	shade_yuv;

	int shader_color_attrib_vertex;
	int shader_color_attrib_color;

	int shader_texture_attrib_avertex;
	int shader_texture_attrib_atexture;
	int shader_texture_attrib_acolor;
	int shader_texture_uniform_texture;

protected:
	void mousePressEvent(QMouseEvent *e) Q_DECL_OVERRIDE;
	void mouseReleaseEvent(QMouseEvent *e) Q_DECL_OVERRIDE;

	void initializeGL() Q_DECL_OVERRIDE;
	void resizeGL(int w, int h) Q_DECL_OVERRIDE;
	void paintGL() Q_DECL_OVERRIDE;

	void initShaders();
	void initTextures();

private:
	void			create_shaders();

	QString			label = "";
	bool			label_show = false;
	QPoint			label_pos;
	QRect			label_rect;
	QFont			font;
	QFontMetrics	*metrics;

public slots:
	void			show_message(QString message);
	void			hide_message();

private slots:
	void			screen_init();
};

#endif // WINDOW_H
