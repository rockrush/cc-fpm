TARGET = cweb tinyweb

CFLAGS += -Iinclude -g
LDFLAGS += -lconfig -levent -lpthread -ldl
CC = clang

all: ${TARGET}

tinyweb: binding/tinyweb.c src/main.c utils/compat.c
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $^

cweb: src/main.c src/cmdline_args.c utils/compat.c
	$(CC) $(CFLAGS) -DCWEB_TEST -o $@ $(LDFLAGS) $^

.PHONY: clean
clean:
	@rm -f ${TARGET} html/*.mod
