TARGET = cweb tinyweb

CFLAGS += -Iinclude -g
LDFLAGS += -lconfig -levent -lpthread -ldl
CC = clang

all: ${TARGET}

tinyweb: src/utils/tinyweb.c
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $^
	@echo $(CFLAGS)

cweb: src/main.c src/cweb_args.c
	$(CC) $(CFLAGS) -o $@ $(LDFLAGS) $^

.PHONY: clean
clean:
	@rm ${TARGET}
