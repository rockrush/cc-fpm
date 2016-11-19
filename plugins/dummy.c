#include <stdio.h>
#include <stdlib.h>
#include "../include/cweb/pages.h"

static int check_support(struct support *);
static int get_root(void);

struct plugin config = {
	.desc = "Sample plugin",
	.check_support = check_support,
	.get_root = get_root,
};

//void _init(void) {
//	_register(&config);
//}

static int get_root(void) {
	return 0;
} 

static int check_support(struct support *p) {
	return 0;
}
