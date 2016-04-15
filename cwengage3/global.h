#ifndef GLOBAL_H
#define GLOBAL_H


#include <QThread>

#include "window.h"
//#include "udpclientthread.h"
//#include "tcpclientthread.h"
//#include "eventdata.h"
//#include "eventmanager.h"

namespace Global
{

extern bool				quit;

class Sleeper : public QThread
{
public:
	static void usleep(unsigned long usecs){QThread::usleep(usecs);}
	static void msleep(unsigned long msecs){QThread::msleep(msecs);}
	static void sleep(unsigned long secs){QThread::sleep(secs);}
};

extern Window			*window;
//extern UdpClientThread	*udp_thread;
//extern TcpClientThread	*tcp_thread;
//extern EventManager		*manager;

extern const QString	UDP_BROADCAST_ADDRESS;	// the only hardcoded info
extern const quint32	UDP_PORT;
extern const quint32	UDP_BUFFER_LENGTH;

struct ServerTcp {
	QString	addr;
	quint16	port;
};
struct ClientCon {
	char iface_name[16];				// eth or wlan
	char iface_ip[16];
	char iface_mac[18];
};

//extern ServerTcp	server;				// tcp communication ip and port
//extern ClientCon	client;				// client mac address, network iface

//extern EventData	event;				// event data
extern QString		storage_root;		// media and other files go here
extern QString		storage_media;		// media directory
extern QString		storage_messages;	// message lists
}

#endif // GLOBAL_H
