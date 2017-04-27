# Сборка
 OS: Ubuntu 16.04
Компилятор: g++ (6.2.0)
Зависимости: libmysqlclient (5.7)

Нужна БД mysql на порту 3306;
имя базы maksi;
имя таблицы clients; 
структура таблицы = 
> ( id int(11) NOT NULL AUTO_INCREMENT,
>  name char(15) DEFAULT NULL,
>  fom char(25) DEFAULT NULL,
>  tel char(12) DEFAULT NULL,
>  PRIMARY KEY (id) )