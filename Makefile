all: hello

install: hello
	install -o root -m 555 hello /usr/sbin/hello

clean:
	rm hello

