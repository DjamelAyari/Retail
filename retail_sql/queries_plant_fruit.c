#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <iconv.h>

#include "../retail_server/header.h"
#include "database.h"
#include "queries.h"

int queries_plant_fruit(int client_socket, char *request_path, MYSQL* db_conn)
{
	printf("QUERIES_2\n");
	printf("Entrée dans la fonction queries_plant_fruit !\n");

	MYSQL *mysql = mysql_init(db_conn);
	if (!mysql)
	{
    	fprintf(stderr, "mysql_init() failed\n");
    	return EXIT_FAILURE;
	}
			
	char query_plant[4095] = "SELECT name_fruit, variety_fruit, latin_name_fruit, origine_plant, price_plant, quantity_stock, month_gathering, month_cultivation, floor_type, quantity_sun_need, quantity_water_need "
                   "FROM fruit "
                   "JOIN plant ON fruit.id_fruit = plant.id_fruit "
				   "LEFT JOIN stock ON plant.id_plant = stock.id_plant "
                   "JOIN gathering ON fruit.id_fruit = gathering.id_fruit "
				   "JOIN cultivation ON fruit.id_fruit = cultivation.id_fruit "
                   "JOIN floor_type ON fruit.id_fruit = floor_type.id_fruit "
                   "JOIN sun_need ON fruit.id_fruit = sun_need.id_fruit "
                   "JOIN water_need ON fruit.id_fruit = water_need.id_fruit ";

	printf("Print de la requête SQL préparée: %s\n", query_plant);

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

	if (mysql_query(db_conn, query_plant))
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
		char *name_fruit = row[0] ? row[0] : "NULL";
		char *variety_fruit = row[1] ? row[1] : "NULL";
		char *latin_name_fruit = row[2] ? row[2] : "NULL";
		char *origine_plant = row[3] ? row[3] : "NULL";
		float price_plant = row[4] ? atof(row[4]) : 0.0;
		int quantity_stock = row[5] ? atoi(row[5]) : 0;
		char *month_gathering = row[6] ? row[6] : "NULL";
		char *month_cultivation = row[7] ? row[7] : "NULL";
		char *floor_type = row[8] ? row[8] : "NULL";
		char *quantity_sun_need = row[9] ? row[9] : "NULL";
		char *quantity_water_need = row[10] ? row[10] : "NULL";
	
		// Étape 4 : Afficher la valeur après avoir récupéré le résultat
		printf("Fetched data: %s, %s, %s, %s, %f, %d, %s, %s, %s, %s, %s\n",
            name_fruit, variety_fruit, latin_name_fruit, origine_plant,
            price_plant, quantity_stock, month_gathering, month_cultivation, floor_type, 
			quantity_sun_need, quantity_water_need);

		if (!first_row) {
            send(client_socket, ",", 1, 0); // Séparation entre les objets JSON
        }
        first_row = 0;

		char row_data[512];
sprintf(row_data,
        "{\"name_fruit\":\"%s\", \"variety_fruit\":\"%s\", \"latin_name_fruit\":\"%s\", "
        "\"origine_plant\":\"%s\", \"price_plant\":%f, \"quantity_stock\":%d, \"month_gathering\":\"%s\", "
        "\"month_cultivation\":\"%s\", \"floor_type\":\"%s\", \"quantity_sun_need\":\"%s\", \"quantity_water_need\":\"%s\"}",
        name_fruit, variety_fruit, latin_name_fruit, origine_plant,
        price_plant, quantity_stock, month_gathering, month_cultivation, floor_type, quantity_sun_need, quantity_water_need);
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