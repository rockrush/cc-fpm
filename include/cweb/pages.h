#ifndef _HAS_PLUGINS_H
#define _HAS_PLUGINS_H

//申明结构体
struct support {
	int kern_ver;
	long long distro;	/* support 64 distros */
	int pages;
};

struct page {
	char *desc;
	char *base;
	void *handler;
	int (* check_support)(struct support *p);
	int (* get)(struct evbuffer *ret_buf);
	struct page *next;
};
#endif	/* _HAS_PLUGINS_H */
