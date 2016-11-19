#include <stdio.h>
#include <stdlib.h>
#include <libconfig.h>

int
cweb_check_config(config_t *config)
{
	if(! config_read_file(config, "sample.conf"))
	{
		fprintf(stderr, "%s:%d - %s\n", config_error_file(config),
			config_error_line(config), config_error_text(config));
		config_destroy(config);
		return CONFIG_FALSE;
	}
	return CONFIG_TRUE;
}

int
main (int argc, char **argv)
{
	int retval = 0;
	config_t cfg;
	config_setting_t *setting, *vhost;
	const char *str;

	config_init(&cfg);

	/* Read the file. If there is an error, report it and exit. */
	retval = cweb_check_config(&cfg);
	if (retval == CONFIG_FALSE)
		return EXIT_FAILURE;

	/* Get the store name. */
	if(config_lookup_string(&cfg, "version", &str))
		printf("Cweb version: %s\n\n", str);
	else
		fprintf(stderr, "No 'version' setting in configuration file.\n");

	/* Output a list of all books in the inventory. */
	vhost = config_lookup(&cfg, "vhost");
	if (vhost == NULL)
		return 2;
	vhost = config_lookup(&cfg, "vhost.default");
	if (vhost == NULL)
		return 3;
	vhost = config_lookup(&cfg, "vhost.default.dir");
	if (vhost == NULL)
		return 4;
	if(vhost != NULL)
	{
		int count = config_setting_length(vhost);
		int i;

		for(i = 0; i < count; ++i) {
			config_setting_t *site = config_setting_get_elem(vhost, i);

			/* Only output the record if all of the expected fields are present. */
			const char *src, *lib, *cc;

			if(!(config_setting_lookup_string(site, "src", &src)
				&& config_setting_lookup_string(site, "lib", &lib)
				&& config_setting_lookup_string(site, "cc", &cc)))
				continue;
			printf("[%d]\t%-12s  %-12s  %-12s\n", i, src, lib, cc);
		}
		putchar('\n');
	}

  /* Output a list of all movies in the inventory. */
  setting = config_lookup(&cfg, "inventory.movies");
  if(setting != NULL)
  {
    unsigned int count = config_setting_length(setting);
    unsigned int i;

    printf("%-30s  %-10s   %-6s  %s\n", "TITLE", "MEDIA", "PRICE", "QTY");
    for(i = 0; i < count; ++i)
    {
      config_setting_t *movie = config_setting_get_elem(setting, i);

      /* Only output the record if all of the expected fields are present. */
      const char *title, *media;
      double price;
      int qty;

      if(!(config_setting_lookup_string(movie, "title", &title)
           && config_setting_lookup_string(movie, "media", &media)
           && config_setting_lookup_float(movie, "price", &price)
           && config_setting_lookup_int(movie, "qty", &qty)))
        continue;

      printf("%-30s  %-10s  $%6.2f  %3d\n", title, media, price, qty);
    }
    putchar('\n');
  }

  config_destroy(&cfg);
  return(EXIT_SUCCESS);
}
