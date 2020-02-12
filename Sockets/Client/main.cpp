#include <winsock.h>
#include <stdio.h>
#include <string>
#include <iostream>

using std::string;

int main(int argc, char* argv[])
{
	WSADATA wsa_data;
	if (WSAStartup(0x0202, &wsa_data) || wsa_data.wVersion != 0x0202)
		return -1;

	SOCKET s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (s == INVALID_SOCKET)
		return -1;

	SOCKADDR_IN sa;
	sa.sin_family = AF_INET;
	sa.sin_port = htons(1026);
	sa.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	int sizeof_sa = sizeof(sa);

	SOCKADDR_IN nsa;
	int sizeof_nsa = sizeof(nsa);

	string request;
	while (true) {
		std::cout << "request = ";
		getline(std::cin, request);
		if (sendto(s, request.c_str(), request.length() + 1, 0, (SOCKADDR*)&sa, sizeof_sa) == SOCKET_ERROR)
			return -1;
		char buffer[1024];
		if (recvfrom(s, buffer, sizeof(buffer), 0, (SOCKADDR*)&nsa, &sizeof_nsa) == SOCKET_ERROR)
			return -1;
		std::cout << buffer << '\n';
	}
	closesocket(s);
	WSACleanup();

	system("pause");
	return 0;
}