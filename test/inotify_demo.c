#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/inotify.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define EVENT_BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main(void)
{
	int length, i = 0;
	int fd;
	int wd;
	char buffer[EVENT_BUF_LEN];

	/*creating the INOTIFY instance*/
	fd = inotify_init();
	if (fd < 0) {
		perror("inotify_init");
		return EXIT_FAILURE;
	}

	/*adding the “/tmp” directory into watch list, not monitoring subdir as default. */
	wd = inotify_add_watch(fd, "/tmp", IN_CREATE | IN_DELETE);

	for (;;) {
		i = 0;
		length = read(fd, buffer, EVENT_BUF_LEN);
		if (length < 0)
			perror("read");

		/*actually read return the list of change events happens. */
		while (i < length) {
			struct inotify_event *event = (struct inotify_event *) &buffer[i];

			if ((event->len < 1) || (event->mask & IN_ISDIR))
				continue;
			if (event->mask & IN_CREATE)
				printf("File %s created.\n", event->name);
			else if (event->mask & IN_DELETE)
				printf("File %s deleted.\n", event->name);

			i += EVENT_SIZE + event->len;
		}
	}
	inotify_rm_watch(fd, wd);
	close(fd);
	return EXIT_SUCCESS;
}
