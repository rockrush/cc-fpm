CFLAGS += -I.
LDFLAGS_PLUGINS = -shared -fPIC -nostartfiles

.c.mod:
	$(CC) $(CFLAGS) $(LDFLAGS_PLUGINS) -o $@ $<

all: sample.mod test.mod dummy.mod

.PHONY: clean

clean:
	@rm -f *.so
