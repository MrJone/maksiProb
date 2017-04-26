#include <mysql.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>


#define SQL_DB "maksi"
#define SQL_PORT 0

#define COLOR_ERR "\x1b[31;1m"
#define COLOR_NORMAL "\x1b[0m"


struct Status
{
	bool work;
	int numEnd;
};

char getch();

int viewDB(MYSQL *_connection);

void err_msg(char* _msg);
void err_msg(const char* _msg);

int main()
{
	MYSQL *connector, 
		mysql;
	MYSQL_RES *sqlRes;
	MYSQL_ROW sqlRow;
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
		//TODO: main process
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
				if (viewDB(connector) != 0)
				{
					stat.work = false;
					stat.numEnd = 1;
				}
				break;
			case 2:
				break;
			case 3:
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



int viewDB(MYSQL *_connection)
{
	MYSQL_RES *tmpResult;
	MYSQL_ROW tmpRow;

	if(mysql_query(_connection, "Select name, fom, tel from clients") != 0)
	{
		err_msg(mysql_error(_connection));
		return 1;
	}

	tmpResult = mysql_store_result(_connection);
	if(tmpResult == NULL)
	{
		err_msg(mysql_error(_connection));
		return 1;
	}

	int _tmp;

	while((tmpRow = mysql_fetch_row(tmpResult)) != NULL)
	{
		printf("\x1b[47;30mName                |"
			"Second Name              |"
			"Telephone #              |\x1b[0m\n");
		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < sizeof(tmpRow[i])/sizeof(char); j++, _tmp++)
			{
				putchar(tmpRow[i][j]);
			}
			for (int k = 0; k < (25 - _tmp); k++)
				putchar(' ');
			putchar('|');
			_tmp = 0;
		}
	}

	mysql_free_result(tmpResult);
	return 0;
}

void err_msg(char *_msg)
{
	fprintf(stderr, "%s%s%s\n", COLOR_ERR, _msg, COLOR_NORMAL);
}

void err_msg(const char *_msg)
{
	fprintf(stderr, "%s%s%s\n", COLOR_ERR, _msg, COLOR_NORMAL);
}

char getch()
{
	struct termios tmpTerm, normalTerm;
	int _char;
	tcgetattr(STDIN_FILENO,&normalTerm);
		//get attr from normal terminal
	tmpTerm = normalTerm;
		//copy to tmp
	tmpTerm.c_lflag &= ~(ICANON|ECHO);
		//off echo and verification by ENTER
	tcsetattr(STDIN_FILENO, TCSANOW, &tmpTerm);
		//setup attr NOW (TCSANOW)
	_char = getchar();

	tcsetattr(STDIN_FILENO, TCSANOW, &normalTerm);
		//return to normal attr
	return _char;

	/*
		Нелохой такой велосипед :D
	*/
}