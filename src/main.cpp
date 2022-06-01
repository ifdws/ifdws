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

		if (!request.valid) {
			close_socket();
			continue;
		}

		if (request.route == "/") {
			html = "<head>\n\t<title>ifdws!</title>\n\t<style>\n\t\t* {\n\t\t\tmargin: 0;\n\t\t}\n\t\t\n\t\tbody {\n\t\t\twidth: 100vw;\n\t\t\theight: 100vh;\n\t\t\tdisplay: flex;\n\t\t\tjustify-content: center;\n\t\t\talign-items: center;\n\t\t\tbackground-color: #222222;\n\t\t\tcolor: #ffffff;\n\t\t\tfont-family: 'Roboto', Arial, sans-serif;\n\t\t}\n\t\t\n\t\th1 {\n\t\t\tfont-size: 20vw;\n\t\t}\n\t</style>\n\t\n\t<script>\n\t\tlet i = 0;\n\t\t\n\t\tconst text = [\n\t\t\t\"ifdws!\",\n\t\t\t\"ifdws!!\",\n\t\t\t\"ifdws!!!\"\n\t\t];\n\t\t\n\t\tsetInterval(() => {\n\t\t\tdocument.getElementById(\"ifdws\").innerText = text[i];\n\t\t\ti = (i + 1) % text.length;\n\t\t}, 500);\n\t</script>\n</head>\n\n<body>\n\t<h1 id=\"ifdws\">ifdws!</h1>\n</body>";

			response_headers = create_headers();

			response_headers["Content-type"] = get_mime_header(HTML_MIMETYPE, CHARSET_UTF8);

			response_buffer = respond(create_response(RESPONSE_200, html, response_headers));
		} else {
			response_buffer = respond(create_response(RESPONSE_404, "404 not found", create_headers()));
		}

		if (response_buffer == "") {
			close_socket();
		}

		send_data(response_buffer);

		close_socket();
	}

	// Stop server

	close_server();

	return 0;
}