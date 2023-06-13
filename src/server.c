#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <signal.h>
#include "atshared.h"

#define BUFSIZE 8

static void handle_interrupt(int signum);
static void write_time_stamp(int socketfd, struct sockaddr_in remote);
static void await_requests(int socketfd);
static int server_init(int port);
static void print_usage(char *name);

static volatile sig_atomic_t interrupted;

int main(int argc, char **argv)
{
	struct sigaction act;
	int port = 0;
	int retval = 0;
	int option;

	if (argc != 3) {
		print_usage(argv[0]);
		exit(-1);
	}

	while ((option = getopt(argc, argv,"h:p:")) != -1) {
		switch (option) {
		case 'p' :
			port = atoi(optarg);
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

	int socketfd = server_init(port);
	<... fill in ...>

	printf("The time synchronization server is up and running on port %d. Close it down using CTRL-C.\n", port);

	await_requests(socketfd);

	printf("Closing socket\n");
	if (close(socketfd) < 0) {
		fprintf(stderr, "Failed to close the main socket.\n");
		retval = -1;
	}

	return retval;
}

static void handle_interrupt(int signum)
{
	interrupted = 1;
}

/**
 * Write the current server timestamp in milliseconds. The time is the epoch time.
 */
static void write_time_stamp(int socketfd, struct sockaddr_in remote)
{
	uint64_t timestamp;
	socklen_t addrlen = sizeof(remote);

	timestamp = htonll(get_time_since_epoch());

	if (sendto(socketfd, <... fill in ...>) != sizeof(uint64_t)) {
		perror("Failed to send a client response");
	}
}

/**
 * Parse the received client message.
 *
 * The message needs to contain 'TIME\n', otherwise it is ignored.
 */
static void handle_message(int socketfd, struct sockaddr_in remote, char *message)
{
	int reqlength = sizeof(TIMELINE) - 1;

	if (strlen(message) == reqlength &&
	    !strncmp(TIMELINE, message, reqlength)) {
		write_time_stamp(socketfd, remote);
	}
}

/**
 * Await client requests for the server time.
 */
static void await_requests(int socketfd)
{
	struct sockaddr_in remote;
	socklen_t addrlen = sizeof(remote);
	int recvlen;
	char buffer[BUFSIZE];
	while (!interrupted) {
		recvlen = recvfrom(socketfd, buffer, BUFSIZE, 0, (struct sockaddr *)&remote, &addrlen);
		if (recvlen > 0) {
			buffer[recvlen] = 0;
			handle_message(socketfd, remote, buffer);
		}
	}
}

/**
 * Initialize the UDP socket.
 * As a simple version we listen on all interfaces.
 */
static int server_init(int port)
{
	struct sockaddr_in socketaddr;
	int socketfd;
	int enable = 1;

	memset(&socketaddr, 0, sizeof(socketaddr));
	socketaddr.sin_family = AF_INET;
	socketaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	socketaddr.sin_port = htons(port);

	if ((socketfd = <... fill in ...>) == -1) {
		fprintf(stderr, "Failed to open a socket for port: %d\n", port);
		return -1;
	}

	if (bind(<... fill in ...>) < 0) {
		fprintf(stderr, "Failed to bind the socket.\n");
		return -1;
	}

	if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0) {
		fprintf(stderr, "setsockopt(SO_REUSEADDR) failed\n");
		return -1;
	}

	return socketfd;
}

static void print_usage(char *name)
{
	printf("Usage: %s -p <port>\n", name);
}

