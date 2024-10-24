#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <iconv.h>

#include "../retail_server/header.h"
#include "database.h"
#include "queries.h"

int queries_seed_vegetable(int client_socket, char *request_path, MYSQL* db_conn)
{
	printf("QUERIES_2\n");
	printf("Entrée dans la fonction queries_seed_vegetable !\n");

	MYSQL *mysql = mysql_init(db_conn);
	if (!mysql)
	{
    	fprintf(stderr, "mysql_init() failed\n");
    	return EXIT_FAILURE;
	}
			
	char query_seed[4095] = "SELECT name_vegetable, variety_vegetable, latin_name_vegetable, origine_seed, price_seed, quantity_stock, month_gathering, month_cultivation, floor_type, quantity_sun_need, quantity_water_need "
                   "FROM vegetable "
                   "JOIN seed ON vegetable.id_vegetable = seed.id_vegetable "
				   "LEFT JOIN stock ON seed.id_seed = stock.id_seed "
                   "JOIN gathering ON vegetable.id_vegetable = gathering.id_vegetable "
				   "JOIN cultivation ON vegetable.id_vegetable = cultivation.id_vegetable "
                   "JOIN floor_type ON vegetable.id_vegetable = floor_type.id_vegetable "
                   "JOIN sun_need ON vegetable.id_vegetable = sun_need.id_vegetable "
                   "JOIN water_need ON vegetable.id_vegetable = water_need.id_vegetable ";

	printf("Print de la requête SQL préparée: %s\n", query_seed);

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

	if (mysql_query(db_conn, query_seed))
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
		char *name_vegetable = row[0] ? row[0] : "NULL";
		char *variety_vegetable = row[1] ? row[1] : "NULL";
		char *latin_name_vegetable = row[2] ? row[2] : "NULL";
		char *origine_seed = row[3] ? row[3] : "NULL";
		float price_seed = row[4] ? atof(row[4]) : 0.0;
		int quantity_stock = row[5] ? atoi(row[5]) : 0;
		char *month_gathering = row[6] ? row[6] : "NULL";
		char *month_cultivation = row[7] ? row[7] : "NULL";
		char *floor_type = row[8] ? row[8] : "NULL";
		char *quantity_sun_need = row[9] ? row[9] : "NULL";
		char *quantity_water_need = row[10] ? row[10] : "NULL";
	
		// Étape 4 : Afficher la valeur après avoir récupéré le résultat
		printf("Fetched data: %s, %s, %s, %s, %f, %d, %s, %s, %s, %s, %s\n",
            name_vegetable, variety_vegetable, latin_name_vegetable, origine_seed,
            price_seed, quantity_stock, month_gathering, month_cultivation,
			floor_type, quantity_sun_need, quantity_water_need);

		if (!first_row) {
            send(client_socket, ",", 1, 0); // Séparation entre les objets JSON
        }
        first_row = 0;

		char row_data[512];
sprintf(row_data,
        "{\"name_vegetable\":\"%s\", \"variety_vegetable\":\"%s\", \"latin_name_vegetable\":\"%s\", "
        "\"origine_seed\":\"%s\", \"price_seed\":%f, \"quantity_stock\":%d, \"month_gathering\":\"%s\", "
        "\"month_cultivation\":\"%s\", \"floor_type\":\"%s\", \"quantity_sun_need\":\"%s\", \"quantity_water_need\":\"%s\"}",
        name_vegetable, variety_vegetable, latin_name_vegetable, origine_seed,
        price_seed, quantity_stock, month_gathering, month_cultivation, floor_type, quantity_sun_need, quantity_water_need);
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