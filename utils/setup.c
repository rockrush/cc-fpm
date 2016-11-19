#include <lockfile.h>
#include <stdlib.h>
#include <libconfig.h>

int
cweb_check_config(config_t *config, const char *config_file)
{
	int retval = 0;

	retval = config_read_file(config, "sample.conf");
	if (retval == CONFIG_FALSE) {
		printf("[ERROR] [%s][Line %d]: %s\n", config_error_file(config),
			config_error_line(config), config_error_text(config));
		return CONFIG_FALSE;
	}
	return CONFIG_TRUE;
}

int
main (int argc, char *argv[])
{
	int retval = 0;
	config_t config;
	const char **value = NULL;

	config_init(&config);
	retval = cweb_check_config(&config, "sample.conf");
	if (retval == CONFIG_FALSE) {
		config_destroy(&config);
		return EXIT_FAILURE;
	}

//	retval = config_write_file(&config, "new.conf");
//	if (retval == CONFIG_FALSE)
//		return EXIT_FAILURE;
	retval = config_lookup_string(&config, "server.bind", value);
	printf("Result: %s\n", *value);
	

	printf("[OK] config file has no error\n");
	config_destroy(&config);
	return EXIT_SUCCESS;
}
