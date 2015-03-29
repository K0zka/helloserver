all: hello

install: hello
	mkdir -p $(DESTDIR)/usr/sbin/
	install -m 555 hello $(DESTDIR)/usr/sbin/hello

clean:
	rm hello

