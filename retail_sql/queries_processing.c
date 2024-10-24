#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "queries.h"

char name_fruit[256];

int execute_query(MYSQL* conn, const char* query, MYSQL_BIND* bind, MYSQL_BIND* result_bind, unsigned long num_params)
{
	MYSQL_STMT* stmt = mysql_stmt_init(conn);
	if (stmt == NULL)
	{
		fprintf(stderr, "mysql_stmt_init() failed.\n");
		return EXIT_FAILURE;
	}

	if (mysql_stmt_prepare(stmt, query, strlen(query)))
	{
		fprintf(stderr, "mysql_stmt_prepare failed.\n");
		mysql_stmt_close(stmt);
		return EXIT_FAILURE;
	}

	if (mysql_stmt_bind_param(stmt, bind))
	{
		fprintf(stderr, "mysql_stmt_bind_param failed.\n");
		mysql_stmt_close(stmt);
		return EXIT_FAILURE;
	}

	if (mysql_stmt_execute(stmt))
	{
		fprintf(stderr, "mysql_stmt_execute() failed.\n");
		mysql_stmt_close(stmt);
		return EXIT_FAILURE;
	}

	if (mysql_stmt_store_result(stmt) != 0)
	{
		fprintf(stderr, "mysql_stmt_store_result() failed.\n");
	       	mysql_stmt_close(stmt);
		return EXIT_FAILURE;
	}

	if (mysql_stmt_bind_result(stmt, result_bind) != 0)
	{
		fprintf(stderr, "mysql_stmt_bind_result() failed.\n");
		mysql_stmt_close(stmt);
		return EXIT_FAILURE;
	}
	
	int fetch_status;
	while ((fetch_status = mysql_stmt_fetch(stmt)) == 0)
	{
    		strcat(results, "<li>");
		strcat(results, name_fruit);
		strcat(results, "</li>");
    		
	}

	if (fetch_status == 1)
	{
		fprintf(stderr, "mysql_stmt_fetch() failed.\n");
		mysql_stmt_close(stmt);
		free(results);
		return EXIT_FAILURE;
	}

	mysql_stmt_close(stmt);
	return results;
}
