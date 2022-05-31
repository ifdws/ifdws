#include "network.hpp"
#include "request.hpp"
#include "response.hpp"
#include <iostream>
#include <stdio.h>
#include <map>
using namespace std;

int main(int argc, char** argv) {
	std::map<string, string> response_headers;
	string response_buffer;
	Request request;
	string html;

	int port = 8080;

	network_init(port);

	cout << "Listening at http://localhost:";
	cout << port;
	cout << endl;

	for (;;) {
		accept_connection();

		request = parse_request(read_data());
		
		html = "<head><title>ifdws!</title></head><body>";
		html += "<h1>ifdws is online!</h1>";
		html += "<p>Route: ";
		html += request.route;
		html += "</p>";
		html += "</body>";

		response_headers = create_headers();

		response_headers["Content-type"] = get_mime_header(HTML_MIMETYPE, CHARSET_UTF8);

		response_buffer = respond(create_response(RESPONSE_200, html, response_headers));

		if (response_buffer == CLOSE_CONNECTION) {
			close_socket();
		}

		send_data(response_buffer);

		close_socket();
	}

	// Stop server

	close_server();

	return 0;
}