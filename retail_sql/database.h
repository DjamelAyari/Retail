#ifndef DATABASE_H
#define DATABASE_H

#include <mysql/mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include "../retail_server/header.h"

MYSQL* db_connect();
void db_disconnect(MYSQL* conn);

#endif
