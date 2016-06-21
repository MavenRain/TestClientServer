#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <cstring>

int main(int argc, const char * * argv)
{
	auto client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	auto server = gethostbyname("localhost");
	memcpy(reinterpret_cast<char *>(&address.sin_addr.s_addr), server->h_addr, server->h_length);
	address.sin_port = htons(8080);
	connect(client, reinterpret_cast<sockaddr *>(&address), sizeof address);
	auto first = 42;
	auto second = 9;
	auto third = 72;
	send(client, reinterpret_cast<char *>(&first), 4, 0);
	send(client, reinterpret_cast<char *>(&second), 4, 0);
	send(client, reinterpret_cast<char *>(&third), 4, 0);
}
