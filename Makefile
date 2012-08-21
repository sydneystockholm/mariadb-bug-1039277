ZDBPATH=`pkg-config --variable=includedir zdb`
CFLAGS+=-std=c99 -Wall -g -pthread -I$(ZDBPATH)/zdb
LDFLAGS+=-lzdb

run: build
	@./test

build:
	@$(CC) $(CFLAGS) $(LDFLAGS) -o test test.c

clean:
	@rm -f ./test
