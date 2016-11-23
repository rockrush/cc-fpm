#include <stdlib.h>
#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <getopt.h>
#include <string.h>
#include <event.h>

#include <cweb/compat.h>
#include <cweb/pages.h>
#include <cweb/cweb_internal.h>
#include <cweb/config.h>

char *pages_dir = "html/";
struct page *pages_list = NULL;
struct support sys_info;

/* 供动态库使用的注册函数 */
void load_page(struct page *p) {
	sys_info.pages += 1;
	p->next = pages_list;
	pages_list = p;
}

int init_pages(void)
{
	void *handler = NULL;
	struct dirent *file = NULL;
	struct page *new_page = NULL;
	char page_path[128];
	char *file_ext = NULL;
	DIR *dir_s = opendir(pages_dir);

	while ((file = readdir(dir_s)) != NULL) {
		sprintf(page_path, "%s%s", pages_dir, file->d_name);
		file_ext = strrchr(page_path, '.');
		if (file_ext == NULL)
			continue;
		else if (strcmp(file_ext, ".html"))
			continue;
		handler = dlopen(page_path, RTLD_LAZY);
		if (handler == NULL) {
			printf("[WARNING] loading of page %s failed, reason is %s.\n", page_path, dlerror());
			continue;
		} else {
			new_page = (struct page *)dlsym(handler, "config");
			load_page(new_page);
			new_page->handler = handler;
		}
	}
	return EXIT_SUCCESS;
}

/* initialization */
void cweb_init(void)
{
	sys_info.pages = 0;
	sys_info.kern_ver = kernel_version();
}

struct page *http_router(char *uri)
{
	struct page *cur_page = pages_list;
	/* Separate GET params */
	char *get_params = strchr(uri, '?');
	if (get_params != NULL) {
		get_params[0] = '\0';
		get_params++;
	}
	while (cur_page != NULL) {
		if (strcmp(uri+1, cur_page->base) == 0) {
			printf("[ROUTE] %s, %s\n", uri, cur_page->base);
			return cur_page;
		}
		cur_page = cur_page->next;
	}
	printf("[ROUTE](fail) %s\n", uri);
	return NULL;	/* TODO: 404 page */
}

#ifdef CWEB_TEST
int main(int argc, char *argv[])
{
	int retval;
	void *handle = NULL;

	cweb_init();
	cmdline_args(argc, argv);

	retval = init_pages();	/* load pages */
	if (retval) {
		printf("[ERROR] loading of pages failed.\n");
		return EXIT_FAILURE;
	}

	struct page *cur_page = pages_list;
	while (cur_page != NULL) {
		cur_page->check_support(&sys_info);
		cur_page = cur_page->next;
	}
	return EXIT_SUCCESS;
}
#endif
