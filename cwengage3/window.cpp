#include "global.h"

#include <QMouseEvent>
#include <QTimer>
#include <QDir>

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniEnvironment>
#include <QtAndroidExtras/QAndroidJniObject>
#endif

Window::Window()
	//: QOpenGLWidget(parent)
{
	width = this->geometry().width();
	height = this->geometry().height();
	font = QFont("Arial", 28, QFont::Bold);
	metrics = new QFontMetrics(font);
	this->resize(1024, 768);
	QTimer::singleShot(550, this, SLOT(screen_init()));

#ifdef Q_OS_ANDROID
	// set full screen for android
	//QTimer::singleShot(300, this, SLOT(showFullScreen()));
#endif

#if defined(Q_OS_LINUX) && defined(Q_OS_ANDROID)
	QAndroidJniObject mediaDir = QAndroidJniObject::callStaticObjectMethod("android/os/Environment", "getExternalStorageDirectory", "()Ljava/io/File;");
	QAndroidJniObject mediaPath = mediaDir.callObjectMethod( "getAbsolutePath", "()Ljava/lang/String;" );

	Global::storage_root = mediaPath.toString() + "/engage/";

	QAndroidJniEnvironment env;
	if (env->ExceptionCheck()) { env->ExceptionClear(); } // catch java exception
#endif

#if defined(Q_OS_LINUX) && !defined(Q_OS_ANDROID)
	Global::storage_root = QDir().homePath() + "/engage/";
#endif

#if defined(Q_OS_WIN32) || defined(Q_OS_WIN64)
	Global::storage_root = "C:/engage/";
#endif
}

Window::~Window()
{
	makeCurrent();

	Global::quit = true;
	Global::Sleeper::sleep(1);

	//delete Global::udp_thread;
	//delete Global::tcp_thread;

	doneCurrent();

	delete metrics;
}

void Window::mousePressEvent(QMouseEvent *e) {
	mouse_press_position = QVector2D(e->localPos());
	mouse_left_button = e->buttons() & Qt::LeftButton;
	mouse_right_button = e->buttons() & Qt::RightButton;
}

void Window::mouseReleaseEvent(QMouseEvent *e) {
	mouse_press_position = QVector2D(e->localPos());
	mouse_left_button = e->buttons() & Qt::LeftButton;
	mouse_right_button = e->buttons() & Qt::RightButton;
}

void Window::initializeGL() {
	initializeOpenGLFunctions();
	//glClearColor(Global::manager->red, Global::manager->green, Global::manager->blue, 1);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//glEnable(GL_DEPTH);

	create_shaders();
}

void Window::resizeGL(int w, int h) {
	width = w;
	height = h;
	qDebug() << "Size = " << w << h;
}

void Window::paintGL() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (label_show) {
		QPainter p(this);
		p.setFont(font);
		p.setPen(QColor(Qt::GlobalColor::white));
		p.drawText(QRect(label_pos, label_rect.size()),Qt::AlignCenter , label);
		p.end();
		//qDebug() << "update";
		//Global::Sleeper::sleep(1);
	}

	//Global::manager->render_modules();
}

void Window::show_message(QString message) {
	label = message;
	label_rect = metrics->boundingRect(QRect(0,0,width,height), 0, message);
	label_pos.setX((width / 2) - (label_rect.width() / 2));
	label_pos.setY((height / 2) - (label_rect.height() / 2));
	label_show = true;
	update();
}

void Window::hide_message() {
	label_show = false;
	label = "";
	update();
}

// Called when the screen has been initialised

void Window::screen_init() {
	qDebug() << "screen_init";
	show_message("CompanionWave Engage\n\nLocating broadcast server");
	//Global::udp_thread->start();
}

void Window::create_shaders() {
	shader_color.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/vcolor.fsh");
	shader_color.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vcolor.vsh");
	if (!shader_color.link()) qDebug() << "Color shader compile error " << shader_color.log();
	shader_color.bind();
	shader_color_attrib_vertex = shader_color.attributeLocation("a_vertex");
	shader_color_attrib_color = shader_color.attributeLocation("a_colorin");
	qDebug() << "shader_color" << shader_color.log() << shader_color_attrib_vertex << shader_color_attrib_color;

	shader_texture.addShaderFromSourceFile(QOpenGLShader::Fragment, ":/vtexture.fsh");
	shader_texture.addShaderFromSourceFile(QOpenGLShader::Vertex, ":/vtexture.vsh");
	if (!shader_texture.link()) qDebug() << "Texture shader compile error " << shader_texture.log();
	shader_texture.bind();
	shader_texture_attrib_avertex = shader_texture.attributeLocation("a_vertex");
	shader_texture_attrib_atexture = shader_texture.attributeLocation("a_texcoord");
	shader_texture_attrib_acolor = shader_texture.attributeLocation("a_colorin");
	shader_texture_uniform_texture = shader_texture.uniformLocation("u_texture");
	qDebug() << "shader_texture" << shader_texture.log()
			 << shader_texture_attrib_avertex << shader_texture_attrib_atexture
			 << shader_texture_attrib_acolor << shader_texture_uniform_texture;
}
