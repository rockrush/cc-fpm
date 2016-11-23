extern char *pages_dir;

void cmdline_args(int argc, char *argv[]);
void cweb_init(void);
int init_pages(void);
struct page *http_router(char *uri);
