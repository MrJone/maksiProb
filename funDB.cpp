#include "funDB.h"

int serchDB(MYSQL *_connection)
{
	MYSQL_RES *tmpResult;
	MYSQL_ROW tmpRow;

	printf("Select: \n"
			"\x1b[1m1 - Serch of NAME\x1b[0m\n"
			"\x1b[1m2 - Serch of SECOND NAME\x1b[0m\n"
			"\x1b[1m3 - Serch of TEL\x1b[0m\n"
			"\x1b[1m4 - Back\x1b[0m\n"
			"> ");
	int menuSelect;
	if(scanf("%d", &menuSelect) != 1)
	{
		err_msg("Invalid input data!");
	}

	char inputData[16];

	switch(menuSelect)
	{
		case 1:
		{
			printf("Enter serch name:\n> ");
			if(scanf("%15s", inputData) < 1)
			{
				err_msg("Invalid input data!");
				return 1;
			} putchar('\n');

			char query[] = "Select name, fom, tel from clients WHERE name = \'";
			int size = (strlen(query)+strlen(inputData));
			char *_query = new char[size];

			strcpy(_query, query);
			strcat(_query, inputData);
			strcat(_query, "\'");

			const char * const_query = (const char*)_query;
			viewDB(_connection, const_query);
			return 0;
		}
		case 2:
			break;
		case 3:
			break;
		case 4:
			putchar('\n');
			return 0;
			break;
		default:
			err_msg("Invalid range data!");
			return 1;
			break;
	}
}

int insertDB(MYSQL *_connection)
{

}

int viewDB(MYSQL *_connection, const char* _query)
{
	MYSQL_RES *tmpResult;
	MYSQL_ROW tmpRow;

	if(mysql_query(_connection, _query) != 0)
	{
		err_msg(mysql_error(_connection));
		return -1;
	}

	tmpResult = mysql_store_result(_connection);
	if(tmpResult == NULL)
	{
		err_msg(mysql_error(_connection));
		return -1;
	}

	int _tmp;

	printf("\x1b[47;30mName                     |"
		"Second Name              |"
		"Telephone #              |\x1b[0m\n");

	while((tmpRow = mysql_fetch_row(tmpResult)) != NULL)
	{
		for (int i = 0; i < 3; i++)
		{
			printf("%s", tmpRow[i]);
			_tmp = (25 - strlen(tmpRow[i]));
			for (int j = 0; j < _tmp; j++)
				putchar(' ');
			putchar('|');
		}
		putchar('\n');
	}
	putchar('\n');
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
		Для всёт не реализованой фичи...
	*/
}