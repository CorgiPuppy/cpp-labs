#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "../include/Constants.h"

int main()
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	char buffer[1024] = {0};

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		std::cerr << "Ошибка создания сокета" << std::endl;
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(Constants::PORT);

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
	{
		std::cerr << "Ошибка подключения к серверу" << std::endl;
		return -1;
	}

	while (true)
	{
		int valread = read(sock, buffer, sizeof(buffer));
		if (valread == 0) break;
		std::cout << buffer;
		memset(buffer, 0, sizeof(buffer));
	}

	close(sock);

	return 0;
}
