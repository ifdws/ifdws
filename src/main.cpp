#include "network.hpp"
#include "request.hpp"
#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;

int main(int argc, char** argv) {
	string buffer;
	string response_buffer;

	int port = 8080;
	std::map<string, string> response_headers;

	response_headers["Server"] = "ifsfs";
	response_headers["Content-type"] = get_mime_header(HTML_MIMETYPE, CHARSET_UTF8);

	network_init(port);

	cout << "Listening at http://localhost:";
	cout << port;
	cout << endl;

	for (;;) {
		accept_connection();

		buffer = read_data();
		response_buffer = handle_input(buffer, response_headers);

		if (response_buffer == CLOSE_CONNECTION) {
			close_socket();
		}

		send_data(response_buffer);

		close_socket();
	}

	// Stop server

	close_server();

	// Clean up memory

	free(&buffer);
	free(&response_buffer);
	free(&response_headers);

	return 0;
}