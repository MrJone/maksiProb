#include <mysql.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

#define COLOR_ERR "\x1b[31;1m"
#define COLOR_NORMAL "\x1b[0m"

char getch();
void err_msg(char* _msg);
void err_msg(const char* _msg);

int viewDB(MYSQL *_connection, const char* _query);
int serchDB(MYSQL *_connection);
int insertDB(MYSQL *_connection);
