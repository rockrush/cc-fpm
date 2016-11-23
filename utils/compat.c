#include <stdio.h>
#include <sys/utsname.h>
#include <linux/version.h>

int kernel_version(void)
{
	int major, minor, patch;
	struct utsname buf;
	int retval = uname(&buf);
	if (retval)
		return -1;
	sscanf(buf.release, "%d.%d.%d", &major, &minor, &patch);
	return KERNEL_VERSION(major, minor, patch);
}
