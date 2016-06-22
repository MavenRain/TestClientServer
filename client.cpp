#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, const char * * argv)
{
	auto client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in address;
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr("127.0.0.1");
	address.sin_port = htons(8080);
	connect(client, reinterpret_cast<sockaddr *>(&address), sizeof address);
	auto first = 42;
	auto second = 9;
	auto third = 72;
	send(client, reinterpret_cast<char *>(&first), 4, 0);
	send(client, reinterpret_cast<char *>(&second), 4, 0);
	send(client, reinterpret_cast<char *>(&third), 4, 0);
}
