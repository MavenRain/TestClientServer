#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <thread>
#include <string>

using namespace std;

int main(int argc, const char * * argv)
{
	auto listener = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	cout << "Socket retrieved\n";
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(8080);
	bind(listener, reinterpret_cast<struct sockaddr *>(&address), sizeof(address));
	cout << "Socket bound\n";
	listen(listener, 10);
	cout << "Socket listening\n";
	while(1)
	{
		auto client = accept(listener, nullptr, nullptr);
		cout << "Client connected\n";
		thread { [&client]
		{
			while(1)
			{
				char buffer[4];
				int received = 0;
				auto index = buffer;
				while (received < 4)
				{
					auto bytes = recv(client, index, 4, 0);
					index += bytes;
					received += bytes;
				}
				cout << to_string(* reinterpret_cast<int *>(buffer)) << "\n";
			}
		} }.detach();
	}							
}
