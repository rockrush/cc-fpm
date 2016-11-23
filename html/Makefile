CC = clang
CFLAGS += -I.
LDFLAGS_PLUGINS = -shared -fPIC -nostartfiles

%.html: %.c
	$(CC) $(CFLAGS) $(LDFLAGS_PLUGINS) -o $@ $<
	@strip $@

all: sample.html test.html dummy.html

.PHONY: clean

clean:
	@rm -f *.html
