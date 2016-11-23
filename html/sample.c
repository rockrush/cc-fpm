#include <stdio.h>
#include <stdlib.h>
#include <event.h>
#include "../include/cweb/pages.h"

struct page config;

/* 加载动态库的自动初始化函数 */
void _init(void) {
	/* 调用主程序的注册函数 */
//	_register(&config);
}

/* 返回0表示该模块支持当前系统 */
static int check_support(struct support *p) {
	if (p->kern_ver < 197120)
		return -1;
	// if (p->distro & LOCAL_DISTRO_MASK = NUM)
	//	do_something();
	printf("[PAGE] newly added: %s.\n", config.desc);
	return 0;
}

/* Generating page */
static int get(struct evbuffer *ret_buf) {
	evbuffer_add_printf(ret_buf, "<!doctype html>\n<html lang=zh>\n<head>\n\t<title>Sample</title>\n</head>\n<body>\n</body>\n</html>\n");
	return 0;
}

/* 模块配置 */
struct page config = {
	.desc = "Sample", /* 模块简短描述，建议用漏洞名 */
	.base = "sample.html",
	.check_support = check_support,
	.get = get,
};
