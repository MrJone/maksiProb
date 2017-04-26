all:
	gcc -omain ./main.cpp -L/usr/lib/i386-linux-gnu/ -I/usr/include/mysql/ -lmysqlclient
