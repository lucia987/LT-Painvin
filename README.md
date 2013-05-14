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
