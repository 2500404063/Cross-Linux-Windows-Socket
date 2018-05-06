#ifndef sun_socket_define
#define sun_socket_define
typedef unsigned int Sun_SOCKET;
#ifdef _MSC_VER
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <thread>
#pragma comment(lib,"ws2_32.lib")
class __declspec(dllexport) sun_socket
{
private:
#ifdef _MSC_VER
	WSADATA wsa;
#endif
public:
	sun_socket();
	~sun_socket();
	int sun_listen(Sun_SOCKET *obj, const char* ip, unsigned int port, int backlog);
	Sun_SOCKET sun_accept(Sun_SOCKET obj, sockaddr_in *eip);
	int sun_send(Sun_SOCKET obj, char* data, int length);
	int sun_recv(Sun_SOCKET obj, char* buffer, int length);
	void sun_send_async(Sun_SOCKET obj, char* data, int length);
	void sun_recv_async(Sun_SOCKET obj, char* buffer, int length);
	int sun_stop(Sun_SOCKET obj);
	int sun_stop_hard(Sun_SOCKET obj);
	void sun_getip(sockaddr_in eip, char* ip, int size_ip);
	void sun_getport(sockaddr_in eip, unsigned short *port);
};
#endif

#if defined (__GNUC__) || defined(__GNUG__)
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <thread>

class sun_socket
{
public:
	sun_socket();
	~sun_socket();
	int sun_listen(Sun_SOCKET *obj, const char* ip, unsigned int port, int backlog);
	Sun_SOCKET sun_accept(Sun_SOCKET obj, sockaddr_in *eip);
	int sun_send(Sun_SOCKET obj, char* data, int length);
	int sun_recv(Sun_SOCKET obj, char* buffer, int length);
	void sun_send_async(Sun_SOCKET obj, char* data, int length);
	void sun_recv_async(Sun_SOCKET obj, char* buffer, int length);
	int sun_stop(Sun_SOCKET obj);
	int sun_stop_hard(Sun_SOCKET obj);
	void sun_getip(sockaddr_in eip, char* ip, int size_ip);
	void sun_getport(sockaddr_in eip, unsigned short *port);
};
#endif

#endif // !sun_socket

