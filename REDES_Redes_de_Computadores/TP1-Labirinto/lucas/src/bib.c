#include "bib.h"

void logexit(const char* msg){
	perror(msg);
	exit(EXIT_FAILURE);
}

int addrparse(const char* addrstr, const char* portstr, struct sockaddr_storage* storage) {
	if (!addrstr || !portstr) return -1;

	uint16_t port = (uint16_t)atoi(portstr);

	if (port == 0) return -1;

	port = htons(port);

	struct in_addr inaddr4;
	if(inet_pton(AF_INET, addrstr, &inaddr4)) {
		struct sockaddr_in* addr4 = (struct sockaddr_in *)storage;
		addr4->sin_family = AF_INET;
		addr4->sin_port = port;
		addr4->sin_addr = inaddr4;
		return 0;
	}

	struct in6_addr inaddr6;
	if(inet_pton(AF_INET6, addrstr, &inaddr6)) {
		struct sockaddr_in6* addr6 = (struct sockaddr_in6 *)storage;
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = port;
		memcpy(&(addr6->sin6_addr), &inaddr6, sizeof(inaddr6));
		return 0;
	}

	return -1;
}

void addrtostr(const struct sockaddr* addr, char* str, size_t strsize) {
	
	int version;
	char addrstr[INET6_ADDRSTRLEN+1] = "";
	uint16_t port;

	if (addr->sa_family == AF_INET) {
		version = 4;
		const struct sockaddr_in* addr4 = (const struct sockaddr_in *)addr;

		if (!inet_ntop(AF_INET, &(addr4->sin_addr), addrstr, INET6_ADDRSTRLEN+1)) logexit("ntop");

		port = ntohs(addr4->sin_port);
	} else if (addr->sa_family == AF_INET6) {
		version = 6;
		const struct sockaddr_in6* addr6 = (const struct sockaddr_in6 *)addr;

		if (!inet_ntop(AF_INET6, &(addr6->sin6_addr), addrstr, INET6_ADDRSTRLEN+1)) logexit("ntop");

		port = ntohs(addr6->sin6_port);
	} else logexit("unknown protocol");

	if(str) snprintf(str, strsize, "IPV%d %s %hu", version, addrstr, port);
}

int server_sockaddr_init(const char* protocol, const char* portstr, struct sockaddr_storage* server_storage){
	uint16_t port = (uint16_t)atoi(portstr);

	if (port == 0) return -1;

	port = htons(port);

	memset(server_storage, 0, sizeof(*server_storage));

	if (strcmp(protocol, "v4") == 0) {
		struct sockaddr_in* addr4 = (struct sockaddr_in *)server_storage;
		addr4->sin_family = AF_INET;
		addr4->sin_port = port;
		addr4->sin_addr.s_addr = INADDR_ANY;
		return 0;
	} else if (strcmp(protocol, "v6") == 0) {
		struct sockaddr_in6* addr6 = (struct sockaddr_in6 *)server_storage;
		addr6->sin6_family = AF_INET6;
		addr6->sin6_port = port;
		addr6->sin6_addr = in6addr_any;
		return 0;
	} else logexit("unknown protocol");

	return -1;
}