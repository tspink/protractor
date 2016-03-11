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

/**
 * Signal handler function.
 *
 * Handles incoming signals, and performs the actions associated with them.
 * @param sig The incoming signal number.
 */
static void signal_handler(int sig)
{
	// Check for a SIGINT (which is sent on a Ctrl-C in the terminal)
	if (sig == SIGINT) {
		// Make sure there is a global server instance registered.
		if (server) {
			// Instruct the server to stop.
			server->stop();
		}
	}
}

/**
 * Application entry point.
 *
 * @param argc Number of incoming command-line arguments.
 * @param argv Array of incoming command-line arguments.
 * @return Program exit code.
 */
int main(int argc, char **argv)
{
	// Register the signal handler for the SIGINT signal
	signal(SIGINT, signal_handler);

	// Print out a header
	printf("protractor, version 0.1\n");

	// Create a new server instance.
	server = new ProtractorServer();

	try {
		// Run the server.
		printf("starting server...\n");
		server->run();
	} catch (Exception& ex) {
		// Print out any exceptions that may have occurred, and exit with a
		// failure code.
		printf("error: %s\n", ex.message().c_str());
		return 1;
	}

	// Inform the user the server is stopping.
	printf("server stopped.\n");

	return 0;
}
