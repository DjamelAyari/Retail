#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iconv.h>

#include <mysql/mysql.h>
#include "database.h"

MYSQL* db_connect()
{
	MYSQL* conn = mysql_init(NULL);
	if (conn == NULL)
	{
		fprintf(stderr, "mysql_init() failed.\n");
		return NULL;
	}

	if (mysql_real_connect(conn, "127.0.0.1", "root", "Laurine12...", "retail", 3306, NULL, 0))
	{
		if (mysql_set_character_set(conn, "utf8mb4"))
		{
        	fprintf(stderr, "Erreur lors de la configuration de l'encodage : %s\n", mysql_error(conn));
    	}
		else
		{
        	printf("Connexion configurée pour utiliser l'encodage UTF-8.\n");
    	}
		
		
	}
	else
	{
		fprintf(stderr, "mysql_real_connect() failed.\n");
		mysql_close(conn);
		return NULL;
	}

	return conn;
}

void db_disconnect(MYSQL* conn)
{
	if (conn != NULL)
	{
		mysql_close(conn);
	}
}
