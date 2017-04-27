all: main.o funDB.o
	g++ -omain ./main.o ./funDB.o -L/usr/lib/i386-linux-gnu/ -I/usr/include/mysql/ -lmysqlclient
main.o: 
	g++ -c ./main.cpp -L/usr/lib/i386-linux-gnu/ -I/usr/include/mysql/ -lmysqlclient
funDB.o:
	g++ -c ./funDB.cpp -L/usr/lib/i386-linux-gnu/ -I/usr/include/mysql/ -lmysqlclient
clear:
	rm -rf ./*.o