/**
 * src/main.cpp
 *
 * Protractor :: Copyright (C) University of Edinburgh 2016
 * All Rights Reserved
 */
#include <protractor.h>
#include <server.h>
#include <stdio.h>
#include <sys/signal.h>

using namespace protractor;

static ProtractorServer *server;

static void signal_handler(int sig)
{
	if (sig == SIGINT) {
		if (server) {
			server->stop();
		}
	}
}

int main(int argc, char **argv)
{
	signal(SIGINT, signal_handler);

	printf("protractor, version 0.1\n");

	server = new ProtractorServer();

	try {
		printf("starting server...\n");
		server->run();
	} catch (Exception& ex) {
		printf("error: %s\n", ex.message().c_str());
		return 1;
	}
	printf("stopping server...\n");

	return 0;
}
