#include "global.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Window w;
	w.show();
	Global::window = &w;

	Global::udp_thread = new UdpClientThread();
	Global::tcp_thread = new TcpClientThread();
	Global::manager = new EventManager();

	return a.exec();
}
