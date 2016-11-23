#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <event.h>
#include <evhttp.h>
#include <libconfig.h>

#include <cweb/cweb_internal.h>
#include <cweb/pages.h>

void cweb_request_handler(struct evhttp_request *req, void *arg)
{
	struct evbuffer *returnbuffer = evbuffer_new();
	struct page *dest = http_router(req->uri);

	if (dest == NULL) {
		if (strstr(req->uri, ".html") != NULL)
			evbuffer_add_printf(returnbuffer, "<!doctype html>\n<html lang=zh>\n<head>\n\t"
				"<title>404 Not Found</title>\n</head>\n<body>\n</body>\n</html>");
	} else
		dest->get(returnbuffer);
	evhttp_send_reply(req, HTTP_OK, "Client", returnbuffer);
	evbuffer_free(returnbuffer);
	return;
}

int main(int argc, char **argv)
{
	int retval;
	void *handle = NULL;
	short	http_port = 8081;
	// Binds on IPv4 & IPv6, refer to /proc/sys/net/ipv6/bindv6only
	char	*http_addr = "::";
	struct	evhttp *http_server = NULL;

	cweb_init();
	retval = init_pages();
	if (retval) {
		printf("[ERROR] loading of plugins failed.\n");
		return EXIT_FAILURE;
	}

	event_init();
	http_server = evhttp_start(http_addr, http_port);
	evhttp_set_gencb(http_server, cweb_request_handler, NULL);

	fprintf(stderr, "Server started on port %d\n", http_port);
	event_dispatch();

	return(0);
}
