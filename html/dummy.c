#include <stdio.h>
#include <stdlib.h>
#include <event.h>
#include "../include/cweb/pages.h"

struct page config;

void _init(void) {
	//_register(&config);
}

static int get(struct evbuffer *ret_buf) {
	evbuffer_add_printf(ret_buf, "<!doctype html>\n<html lang=zh>\n<head>\n\t<title>Dummy</title>\n</head>\n<body>\n</body>\n</html>\n");
	return 0;
}

static int check_support(struct support *p) {
	printf("[PLUGIN] newly added: %s.\n", config.desc);
	return 0;
}

struct page config = {
	.desc = "Dummy",
	.base = "dummy.html",
	.check_support = check_support,
	.get = get,
};
