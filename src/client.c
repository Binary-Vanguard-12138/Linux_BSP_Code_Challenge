#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <signal.h>
#include <limits.h>
#include "atshared.h"

static volatile sig_atomic_t interrupted;

static void error(char *message);
static void compare_timestamp(uint64_t servertime);
static void handle_interrupt(int signum);
static void print_usage(char *name);
static void connect_to_server(char *hostname, int port);

/**
 * Main function, parsing command line arguments and setting up the socket connection.
 */
int main(int argc, char **argv)
{
	int port = 0;
	struct sigaction act;
	char hostname[HOST_NAME_MAX];
	int option = 0;

	if (argc != 5) {
		print_usage(argv[0]);
		exit(-1);
	}

	while ((option = getopt(argc, argv,"h:p:")) != -1) {
		switch (option) {
		case 'p' :
			<... fill in ...>
			break;
		case 'h' :
			<... fill in ...>
			break;
		default:
			print_usage(argv[0]);
			exit(-1);
			break;
		}
	}

	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	act.sa_handler = handle_interrupt;
	sigaction(SIGINT, &act, NULL);

	connect_to_server(hostname, port);

	return 0;
}

/**
 * Connect to the server process, given the hostname and port.
 */
static void connect_to_server(char *hostname, int port)
{
	int socketfd;
	struct hostent *server;
	struct sockaddr_in serveraddr;
	char *time_message = TIMELINE;
	socklen_t addrlen = sizeof(serveraddr);
	uint64_t timestamp = 0;

	<... fill in ...>
	if (socketfd < 0) {
		error("ERROR opening socket");
	}

	<... fill in ...>
	if (server == NULL) {
		error("Hostname cannot be resolved.");
	}

	memset(&serveraddr, 0, sizeof(serveraddr));

	serveraddr.sin_family = AF_INET;
	memcpy(&serveraddr.sin_addr, server->h_addr_list[0], server->h_length);
	serveraddr.sin_port = htons(port);

	printf("Starting to poll the server %s on port %d\n", hostname, port);
	while (!interrupted) {
		if (sendto(socketfd, time_message, strlen(time_message), 0,
		           (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0) {
			error("Failed to send message to server.");
		} else {
			int recvlen = recvfrom(socketfd, &timestamp, sizeof(uint64_t), 0,
			                       (struct sockaddr *)&serveraddr, &addrlen);
			if (recvlen == sizeof(uint64_t)) {
				timestamp = ntohll(timestamp);
				compare_timestamp(timestamp);
			}
		}
		if (!interrupted) {
			sleep(1);
		}
	}

	printf("\nClosing the socket.\n");
	close(socketfd);
}

/**
 * Generic error function for printing a message.
 */
static void error(char *message)
{
	perror(message);
	exit(-1);
}

/**
 * Compare the timestamp received from the server with our own timestamp and
 * print the absolute difference to standard output.
 */
static void compare_timestamp(uint64_t servertime)
{
	uint64_t mytime = get_time_since_epoch();

	<... fill in ...>

	printf("Client: %lu ms, Server: %lu ms, Abs. diff: %lu ms\n", mytime, servertime, diff);
}

/**
 * Signal handling function called on a user interrupt.
 */
static void handle_interrupt(int signum)
{
	interrupted = 1;
}

/**
 * Print the application usage.
 */
static void print_usage(char *name)
{
	printf("Usage: %s -h <server hostname> -p <server port>\n", name);
}

