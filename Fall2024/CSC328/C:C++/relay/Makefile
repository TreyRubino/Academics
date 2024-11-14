all: relay client

relay: relay_node.c
	gcc -pthread relay_node.c -o relay_node

client: client.c
	gcc client.c -o client

clean:
	rm -f relay_node client

PHONY: ~clean
