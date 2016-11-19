#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <getopt.h>
#include <string.h>
#include <linux/version.h>

#include <cweb/pages.h>
#include <cweb/cweb_internal.h>
#include "../config.h"

/* Some variables */
char *plugins_dir = NULL;
struct plugin_list {
	int id;
	struct plugin *p;
	struct plugin_list *prev;
};

struct support sys_info;
struct plugin_list *plugin_list_head = NULL;
int candidates[256];	/* supports no more than 256 candidates */

/* 供动态库使用的注册函数 */
void _register(struct plugin *p) {
	struct plugin_list *plugin_item = NULL;

	plugin_item = malloc(sizeof(struct plugin_list));
	if (plugin_item == NULL) {
		printf("malloc failed: %s\n", p->desc);
		exit(-1);
	}
	sys_info.plugins += 1;
	plugin_item->id = sys_info.plugins;
	plugin_item->p = p;
	plugin_item->prev = plugin_list_head;
	plugin_list_head = plugin_item;
}

static int load_plugins(char *dir)
{
	DIR *dir_s = NULL;
	void *handler = NULL;
	struct dirent *file = NULL;
	struct plugin *plugin_config = NULL;
	char plugin_file[128];
	char *file_ext = NULL;

	/* check for necessary vars */
	if (dir == NULL)
		dir = "plugins/";	/* take "plugins/" as default */

	dir_s = opendir(dir);
	while ((file = readdir(dir_s)) != NULL) {
		sprintf(plugin_file, "%s%s", dir, file->d_name);
		file_ext = strrchr(plugin_file, '.');
		if (file_ext == NULL)
			continue;
		else if (strcmp(file_ext, ".mod"))
			continue;
		handler = dlopen(plugin_file, RTLD_LAZY);
		if (handler == NULL) {
			printf("[WARNING] loading of plugin %s failed, file is %s, reason is %s.\n", file->d_name, plugin_file, dlerror());
			continue;
		} else {
			plugin_config = (struct plugin *)dlsym(handler, "config");
			_register(plugin_config);
			printf("plugin %s loaded.\n", file->d_name);
		}
	}
	return EXIT_SUCCESS;
}

/* initialization */
void cweb_init()
{
	plugins_dir = WEB_DIR;
	sys_info.plugins = 0;
	sys_info.kern_ver = KERNEL_VERSION(3, 12, 0);
}

int main(int argc, char *argv[]) {
	int retval;
	void *handle = NULL;

	/* init some global variables */
	cweb_init();
	/* read commandline options */
	cweb_args(argc, argv);

	/* load plugins */
	retval = load_plugins(plugins_dir);
	if (retval) {
		printf("[ERROR] loading of plugins failed.\n");
		return EXIT_FAILURE;
	}

	if(plugin_list_head != NULL)
		plugin_list_head->p->check_support(&sys_info);
	return EXIT_SUCCESS;
}
