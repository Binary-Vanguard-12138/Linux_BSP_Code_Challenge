all: server client


server: src/server.c src/atshared.c src/atshared.h
	gcc src/server.c src/atshared.c -o bin/server

client: src/client.c src/atshared.c src/atshared.h
	gcc src/client.c src/atshared.c -o bin/client

clean_server:
	rm -f bin/server

clean_client:
	rm -f bin/client

clean: clean_server clean_client


