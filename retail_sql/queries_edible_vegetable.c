#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <iconv.h>

#include "../retail_server/header.h"
#include "database.h"
#include "queries.h"

int queries_edible_vegetable(int client_socket, char *request_path, MYSQL* db_conn)
{
	printf("QUERIES_2\n");
	printf("Entrée dans la fonction queries_edible !\n");

	MYSQL *mysql = mysql_init(db_conn);
	if (!mysql)
	{
    	fprintf(stderr, "mysql_init() failed\n");
    	return EXIT_FAILURE;
	}
			
	char query_edible[4095] = "SELECT name_vegetable, variety_vegetable, latin_name_vegetable, origine_edible, price_edible, quantity_stock, month_gathering "
                   "FROM vegetable "
                   "JOIN edible ON vegetable.id_vegetable = edible.id_vegetable "
				   "LEFT JOIN stock ON edible.id_edible = stock.id_edible "
                   "JOIN gathering ON vegetable.id_vegetable = gathering.id_vegetable ";

	printf("Print de la requête SQL préparée: %s\n", query_edible);

	if (mysql_ping(db_conn))
	{
    	fprintf(stderr, "Lost connection to MySQL server: %s\n", mysql_error(db_conn));
    	// Réinitialiser la connexion
    	mysql_close(db_conn);
    	db_conn = mysql_init(NULL);
    	if (!mysql_real_connect(db_conn, "127.0.0.1", "root", "Laurine12...", "retail", 3306, NULL, 0))
		{
        	fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(db_conn));
        	return -1;
    	}
	}

	if (mysql_query(db_conn, query_edible))
	{
    	fprintf(stderr, "%s\n", mysql_error(db_conn));
		return -1;
    // Handle query error
	}
	printf("mysql_query OK !\n");

	MYSQL_RES *result = mysql_store_result(db_conn);
	if (result == NULL)
	{
    	fprintf(stderr, "Error storing result: %s\n", mysql_error(db_conn));
		return -1;
    // Handle result error
	}
	printf("mysql_store_result OK !\n");
	
	// Prepare HTTP response
	char response_header[] = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n";
	printf("response header OK !\n");

	// Send response header
    send(client_socket, response_header, strlen(response_header), 0);
	printf("send OK !\n");

	send(client_socket, "[", 1, 0);
    int first_row = 1;

	MYSQL_ROW row;
	while ((row = mysql_fetch_row(result)))
	{
		// Check for NULL values
		char *name_vegetable = row[0] ? row[0] : "NULL";           // First column: name_vegetable
		char *variety_vegetable = row[1] ? row[1] : "NULL";        // Second column: variety_vegetable
		char *latin_name_vegetable = row[2] ? row[2] : "NULL";     // Third column: latin_name_vegetable
		char *origine_edible = row[3] ? row[3] : "NULL";           // Fourth column: origine_edible
		float price_edible = row[4] ? atof(row[4]) : 0.0;          // Fifth column: price_edible
		int quantity_stock = row[5] ? atoi(row[5]) : 0;            // Sixth column: quantity_stock
		char *month_gathering = row[6] ? row[6] : "NULL";		   // Seventh column: month_gathering
	
		// Étape 4 : Afficher la valeur après avoir récupéré le résultat
		printf("Fetched data: %s, %s, %s, %s, %f, %d, %s\n",
            name_vegetable, variety_vegetable, latin_name_vegetable, origine_edible,
            price_edible, quantity_stock, month_gathering);

		if (!first_row) {
            send(client_socket, ",", 1, 0); // Séparation entre les objets JSON
        }
        first_row = 0;

		char row_data[512];
        sprintf(row_data,
                "{\"name_vegetable\":\"%s\", \"variety_vegetable\":\"%s\", \"latin_name_vegetable\":\"%s\", "
                "\"origine_edible\":\"%s\", \"price_edible\":%f, \"quantity_stock\":%d, \"month_gathering\":\"%s\"}",
                name_vegetable, variety_vegetable, latin_name_vegetable, origine_edible,
                price_edible, quantity_stock, month_gathering);
        send(client_socket, row_data, strlen(row_data), 0);
    }

	mysql_free_result(result);
	printf("result free OK !\n");
	
	send(client_socket, "]", 1, 0);
	printf("Send JSON OK !\n");
	mysql_close(db_conn);
	db_conn = NULL;  // Avoid dangling pointer
	printf("mysql_close OK !\n");
	close(client_socket);
	printf("socket closed OK !\n");



	return(0);
}