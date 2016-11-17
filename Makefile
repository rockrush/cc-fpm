TARGET = inotify_demo

all: ${TARGET}

.PHONY: clean
clean:
	@rm ${TARGET}
