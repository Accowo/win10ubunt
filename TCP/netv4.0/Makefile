#Mikefile

server: server.c wrap.c
		gcc $^ -o $@
client: client.c wrap.c
		gcc $^ -o $@
clean: 
	rm -rf server client
