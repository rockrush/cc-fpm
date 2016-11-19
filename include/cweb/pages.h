#ifndef _HAS_PLUGINS_H
#define _HAS_PLUGINS_H

//申明结构体
struct support {
	int kern_ver;
	long long distro;	/* support 64 distros */
	int plugins;
};

struct plugin {
	char *desc;
	int (* check_support)(struct support *p);
	int (* get_root)(void);
};

extern void _register(struct plugin *);
#endif	/* _HAS_PLUGINS_H */
