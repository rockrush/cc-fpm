#include <stdio.h>
#include <stdlib.h>
#include "../include/cweb/pages.h"

static int check_support(struct support *);
static int get_root(void);

/* 模块配置 */
struct plugin config = {
	.desc = "Sample plugin", /* 模块简短描述，建议用漏洞名 */
	.check_support = check_support,
	.get_root = get_root,
};

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
	printf("[PLUGIN] newly added: %s.\n", config.desc);
	return 0;
}

/* 提权 */
static int get_root(void) {
	printf("Executing ROOT exploit ...\n");
	return 0;
} 

