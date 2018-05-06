#include "sun_socket.h"

sun_socket::sun_socket()
{
#ifdef _MSC_VER
	WSAStartup(MAKEWORD(2, 2), &this->wsa);
#endif
#if defined (__GNUC__) || defined(__GNUG__)

#endif

}

sun_socket::~sun_socket()
{
#ifdef _MSC_VER
	WSACleanup();
#endif
#if defined (__GNUC__) || defined(__GNUG__)

#endif
}

int sun_socket::sun_listen(Sun_SOCKET *obj, const char* ip, unsigned int port, int backlog) {
#ifdef _MSC_VER
	*obj = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in eip;
	eip.sin_family = AF_INET;
	eip.sin_port = htons(port);
	inet_pton(AF_INET, ip, &eip.sin_addr.S_un.S_addr);
	bind(*obj, (sockaddr*)&eip, sizeof(eip));
	return ::listen(*obj, backlog);
#endif
#if defined (__GNUC__) || defined(__GNUG__)
	*obj = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in eip;
	eip.sin_family = PF_INET;
	eip.sin_port = htons(port);
	eip.sin_addr.s_addr = inet_addr(ip);
	bind(*obj, (sockaddr*)&eip, sizeof(eip));
	return ::listen(*obj, backlog);
#endif

}

Sun_SOCKET sun_socket::sun_accept(Sun_SOCKET obj, sockaddr_in *eip)
{
	socklen_t len = sizeof(sockaddr_in);
	Sun_SOCKET temp = accept(obj, (sockaddr*)eip, &len);
	return temp;
}

int sun_socket::sun_send(Sun_SOCKET obj, char * data, int length)
{
	return send(obj, data, length, 0);
}

int sun_socket::sun_recv(Sun_SOCKET obj, char * buffer, int length)
{
	return recv(obj, buffer, length, 0);
}

void sun_socket::sun_send_async(Sun_SOCKET obj, char * data, int length)
{
	std::thread th_temp(&sun_socket::sun_send, this, obj, data, length);
	th_temp.detach();
}

void sun_socket::sun_recv_async(Sun_SOCKET obj, char * buffer, int length)
{
	std::thread th_temp(&sun_socket::sun_recv, this, obj, buffer, length);
	th_temp.detach();
}

int sun_socket::sun_stop(Sun_SOCKET obj)
{
#ifdef _MSC_VER
	return shutdown(obj, SD_BOTH);
#endif // _MSC_VER
#if defined (__GNUC__) || defined(__GNUG__)
	return shutdown(obj, SHUT_RDWR);
#endif // defined
}

int sun_socket::sun_stop_hard(Sun_SOCKET obj)
{
#ifdef _MSC_VER
	return closesocket(obj);
#endif // _MSC_VER
#if defined (__GNUC__) || defined(__GNUG__)
	return close(obj);
#endif // defined
}

void sun_socket::sun_getip(sockaddr_in eip, char *ip, int size_ip)
{
	inet_ntop(AF_INET, &eip.sin_addr, ip, size_ip);
}

void sun_socket::sun_getport(sockaddr_in eip, unsigned short *port)
{
	*port = ntohs(eip.sin_port);
}
