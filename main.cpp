#include <mysql.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>


#include "funDB.h"

#define SQL_DB "maksi"
#define SQL_PORT 0

struct Status
{
	bool work;
	int numEnd;
};

int main()
{
	MYSQL *connector, 
		mysql;
	mysql_init(&mysql);

	char logIn[20], 
		passwd[40],
		host[150];

	printf("Welcom!\nEnter login: ");
	if (scanf("%20s", logIn) != 1)
	{
		err_msg("Invalid login!");
		return 1;
	} scanf("%*[^\n]"); //clear buff scanf

	printf("Enter password: ");
	if (scanf("%40s", passwd) != 1)
	{
		err_msg("Invalid password!");
		return 1;
	} scanf("%*[^\n]"); //clear buff scanf

	printf("Enter host addres: ");
	if (scanf("%150s", host) != 1)
	{
		err_msg("Invalid addres!");
		return 1;
	} scanf("%*[^\n]"); //clear buff scanf

	const char* c_host = (const char*)host;
	const char* c_logIn = (const char*)logIn;
	const char* c_passwd = (const char*)passwd;


	connector = mysql_real_connect(&mysql,
		c_host,
		c_logIn,
		c_passwd,
		SQL_DB,
		SQL_PORT, 
		NULL,
		0);

	if (connector == NULL)	//connection faild
	{
		err_msg(mysql_error(&mysql));
		return 1;
	}

	printf("Connected to \x1b[1m%s\x1b[0m\n", host);

	Status stat;
		stat.work = true;

	int menuSelect = 0;

	while (stat.work)
	{
		printf("Select: \n"
			"\x1b[1m1 - View\x1b[0m [View base clients]\n"
			"\x1b[1m2 - Serch\x1b[0m [Serch in base clients]\n"
			"\x1b[1m3 - Insert\x1b[0m [Insert data to base clients]\n"
			"\x1b[1m4 - Quit\x1b[0m [Close this program and disconnect]\n"
			"> ");
		if(scanf("%d", &menuSelect) != 1)
		{
			err_msg("Invalid input data!");
			continue;
		}
		switch(menuSelect)
		{
			case 1:
				if (viewDB(connector, "Select name, fom, tel from clients") != 0)
				{
					stat.work = false;
					stat.numEnd = -1;
				}
				break;
			case 2:
				if ((stat.numEnd = serchDB(connector)) < 0)
				{
					stat.work = false;
					stat.numEnd = -1;
				}
				break;
			case 3:
				if (insertDB(connector) != 0)
				{
					stat.work = false;
					stat.numEnd = -1;
				}
				break;
			case 4:
				stat.work = false;
				stat.numEnd = 0;
				break;
			default:
				err_msg("Invalid range data!");
				break;
		}
	}

	mysql_close(connector);
	printf("Disconnected!\nProgram closed code (%d)\nGood bay!\n", stat.numEnd);

	return stat.numEnd;
}


