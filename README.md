==== ABOUT ====

The client sends the text in an input text file as an ADFGVX
encoded message to a server. Before sending, the message 
comprised of only A, D, F, G, V and X characters is compressed
in a manner that sends 2 characters in one byte.
The server decompressed the ADFGVX message and decrypts it, writing it
to a log file named host<client_hostname>port<client_port>.log.
The server accepts MAX_CLIENTS connections and reads their messages in a
non blocking manner using epoll.
However, the server write to the log file is a blocking operation.
Enhancements to this client server application would involve
* using separate threads for:
	* handling incoming connections
	* reading ADFGVX messages from socket
	* decompressing and decrypting received 
messages
	* writing decompressed messages to file
* using a hash to keep socket-file associations on the server
(currently, a limited vector is used and lookup time is O(n))
* using threads for substitution and transposition on both client and
  server

==== USAGE ====
RUN CLIENT:
1. make runclient
OR
2. ./client 
	--server=SERVER_HOSTNAME
	--port=SERVER_PORT
	--tkey=TRANSPOSE_KEY
	--skey=SUBSTITUTE_KEY
	--file=INPUT_FILE
	-h, --help

RUN SERVER:
1. make runserver
OR
2. ./server 
	--port=SERVER_PORT
	--tkey=TRANSPOSE_KEY
	--skey=SUBSTITUTE_KEY
	-h, --help
