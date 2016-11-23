#include <getopt.h>
#include <stdlib.h>
#include <cweb/cweb_internal.h>

char *optarg = NULL;
const char *short_options = "p:";
struct option long_options[] = {
	{"pages", no_argument, NULL, 'p'},
	{ NULL, 0, NULL, 0 }
};

void
cmdline_args (int argc, char *argv[])
{
	int c;
	while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
	switch(c) {
		case 'p':
			pages_dir = optarg;
		default:
			continue;
	}
	}
}
