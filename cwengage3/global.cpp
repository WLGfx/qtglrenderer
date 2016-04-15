#include "global.h"

namespace Global {

bool			quit = false;

Window			*window;
//UdpClientThread *udp_thread;
//TcpClientThread	*tcp_thread;
//EventManager	*manager;

const QString	UDP_BROADCAST_ADDRESS = "239.255.255.255";
const quint32	UDP_PORT = 4999;
const quint32	UDP_BUFFER_LENGTH = 64;

ServerTcp		server;
ClientCon		client;

//EventData		event;	// holds all event data
QString			storage_root;
QString			storage_media = "media/";
QString			storage_messages = "messages/";
}
