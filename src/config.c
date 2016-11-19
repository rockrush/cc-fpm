#include <cweb/error_code.h>
#include <cweb/config.h>

/* read config file, called when program starts */
int
cweb_cfg_read(char *path)
{
	int retval = 0;

	return CWEB_ERR_FAILURE;
}

/* write config file, may be called by a config util */
int
cweb_cfg_write(char *path)
{
	return CWEB_ERR_FAILURE;
}

/* check if the config file specified is written correctly */
int
cweb_cfg_syntax_check(char *path)
{
	return CWEB_ERR_CFG_SYNTAX;
}

int
main (void)
{
	int retval = 0;
	/* test config file */
	// is_file(config_file);
	/* syntax check on config file */
	retval = cweb_cfg_syntax_check(CWEB_CFG_FILE);
//	if (retval != CWEB_ERR_CFG_SYNTAX)
//		return retval;

	/* read config file */
	retval = cweb_cfg_read(CWEB_CFG_FILE);
	
	return CWEB_ERR_SUCCESS;
}
