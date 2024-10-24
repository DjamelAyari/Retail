#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <iconv.h>

#include "../retail_server/header.h"
#include "database.h"
#include "queries.h"

int queries_seed_fruit_prepared_statement(int client_socket, char *request_path, MYSQL* db_conn)
{
	printf("Entrée dans la fonction queries_seed_fruit_prepared_statement !\n");

	MYSQL_STMT *stmt = mysql_stmt_init(db_conn);
	if (stmt == NULL)
	{
    	fprintf(stderr, "mysql_stmt_init() failed\n");
    	mysql_close(db_conn);
    	exit(EXIT_FAILURE);
	}
	else
	{
		printf("Fonction mysql_stmt_init() OK !\n");
	}

	struct key_value
	{
        	char *key;
        	char *value;
	};

	struct key_value *array = NULL;
	int array_size = 0;

	char *pv = strchr(request_path, '?');
	pv++;

	char *pairk = strtok(pv, "=");
	char *pairv = strtok(NULL, "&");

	printf("Entrée dans la boucle while pour insertion dans la structure array des paramètres de la requête HTTP !\n");

	int compt_while_loop = 0;
	while (pairk && pairv)
	{
		array_size++;
		array = realloc(array, array_size * sizeof(struct key_value));
		array[array_size - 1].key = pairk;
		array[array_size - 1].value = pairv;

		pairk = strtok(NULL, "=");
        pairv = strtok(NULL, "&");

		printf("Boucle while insertion param requête HTTP dans structure array n°%d !\n", compt_while_loop);
		compt_while_loop++;
	}
	printf("ARRAY SIZE:%d\n", array_size);
	printf("Sortie de la boucle while !\n");

	printf("Entrée dans la boucle for pour verifier les valeurs insérées dans la structure array\n");
	for (int i = 0; i < array_size; i++)
	{
        	printf("Structure array Key: %s\n, Structure array Value: %s\n", array[i].key, array[i].value);
    }
		
	char query_seed_param[4095] = "SELECT name_fruit, variety_fruit, latin_name_fruit, origine_seed, price_seed, quantity_stock, month_gathering, month_cultivation, floor_type, quantity_sun_need, quantity_water_need "
                   "FROM fruit "
                   "JOIN seed ON fruit.id_fruit = seed.id_fruit "
				   "LEFT JOIN stock ON seed.id_seed = stock.id_seed "
                   "JOIN gathering ON fruit.id_fruit = gathering.id_fruit "
				   "JOIN cultivation ON fruit.id_fruit = cultivation.id_fruit "
                   "JOIN floor_type ON fruit.id_fruit = floor_type.id_fruit "
                   "JOIN sun_need ON fruit.id_fruit = sun_need.id_fruit "
                   "JOIN water_need ON fruit.id_fruit = water_need.id_fruit "
                   "WHERE 1=1";
	printf("Print de la requête SQL préparée: %s\n", query_seed_param);
	
	printf("Modification de la requête SQL via boucle while en fonction des paramètres fournis par le client\n");

	int i = 0;
	int j = 0;
	while (i < array_size)
	{
		if (strcmp(array[i].key, "name_fruit") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND name_fruit = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "variety_fruit") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND variety_fruit = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "latin_name_fruit") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND latin_name_fruit = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "origine_seed") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND origine_seed = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "price_seed") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND price_seed = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "quantity_stock") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND quantity_stock = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "month_gathering") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND month_gathering = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "month_cultivation") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND month_cultivation = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "floor_type") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND floor_type = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "quantity_sun_need") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND quantity_sun_need = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}
		if (strcmp(array[i].key, "quantity_water_need") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_seed_param, " AND quantity_water_need = ?");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_seed_param);
			j++;
		}

		i++;
	}

	printf("I est le nombre de paires clé / valeur dans la structure array: %d.\n", i);
	printf("J est le nombre de paramètres donnés par l'utilisateur: %d.\n", j);

	printf("La requête SQL est maintenant modifiée pour contenir les paramètres clients.\n");

	if (mysql_ping(db_conn))
	{
    	fprintf(stderr, "Lost connection to MySQL server: %s\n", mysql_error(db_conn));
    	// Réinitialiser la connexion
    	// Close the prepared statement if it exists
		if (stmt != NULL)
		{
			mysql_stmt_close(stmt);  // Close the current prepared statement
			stmt = NULL;  // Avoid dangling pointer
		}
		// Close the current connection
		mysql_close(db_conn);
		db_conn = NULL;  // Avoid dangling pointer

		// Reinitialize and reconnect
		db_conn = mysql_init(NULL);
		if (!mysql_real_connect(db_conn, "127.0.0.1", "root", "Laurine12...", "retail", 3306, NULL, 0))
		{
			fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(db_conn));
			return -1;
		}

		// Reinitialize the prepared statement after reconnecting
		stmt = mysql_stmt_init(db_conn);
		if (!stmt)
		{
			fprintf(stderr, "mysql_stmt_init() failed: %s\n", mysql_stmt_error(stmt));
			return -1;
		}
	}

	printf("Ca repart.\n");

	if (mysql_stmt_prepare(stmt, query_seed_param, strlen(query_seed_param)) != 0)
	{
    	fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
    	mysql_stmt_close(stmt);
    	mysql_close(db_conn);
    	exit(EXIT_FAILURE);
	}
	else
	{
		printf("Fonction mysql_stmt_prepare() OK !\n");
	}

	printf("Création et paramétrage de la structure bind, pour binder les paramétres clients, à la requête SQL.\n");

	MYSQL_BIND bind[j];
	memset(bind, 0, sizeof(bind));

	int bind_index = 0;
	int k = 0;
	double price = 0.0;
	int quantity = 0;

	_Bool is_null = 1;
	
	// Si l'index k de la structure array n'est pas NULL
while (k < array_size)
{
	if(strcmp(array[k].value, "NULL") != 0)
	{
		// Si cet index correspond à la clé price_seed bind le paramètre
		if (strcmp(array[k].key, "price_seed") == 0)
		{
			price = atof(array[k].value);
			bind[bind_index].buffer_type = MYSQL_TYPE_DOUBLE;
			bind[bind_index].buffer = &price;
			bind[bind_index].is_null = 0;
			printf("BIND BUFFER price_seed: %f\n", *(double*)bind[bind_index].buffer);
			bind_index++;
		}
		// Si cet index correspond à la clé quantity_stock bind le paramètre
		else if ((strcmp(array[k].key, "quantity_stock") == 0))
		{
			quantity = atoi(array[k].value);
			bind[bind_index].buffer_type = MYSQL_TYPE_LONG;
			bind[bind_index].buffer = &quantity;
			bind[bind_index].is_null = 0;
			printf("BIND BUFFER quantity_stock: %d\n", *(int*)bind[bind_index].buffer);
			bind_index++;
		}
		// Si cet index correspond à une clé de type string bind le paramètre
		else
		{
			bind[bind_index].buffer_type = MYSQL_TYPE_STRING;
			bind[bind_index].buffer = (char*)array[k].value;
			bind[bind_index].buffer_length = strlen(array[k].value);
			bind[bind_index].is_null = 0;
			printf("BIND BUFFER %s: %s\n", array[k].key, (char*)bind[bind_index].buffer);
			bind_index++;
		}
		k++;
	}
	else
	{
		k++; // Passe a l'index suivant de la structure array
	}
}

	printf("Sortie de la boucle while pour binder les paramétres.\n");

	printf("Fonction bind param pour binder les paramètres de la requête HTTP à ceux de la requête SQL.\n");

	if (mysql_stmt_bind_param(stmt, bind))
	{
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        return EXIT_FAILURE;
    }
	else
	{
		printf("Fonction mysql_stmt_bind_param() OK !\n");
	}

	if (mysql_stmt_execute(stmt) != 0)
	{
    	fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
    	mysql_stmt_close(stmt);
    	mysql_close(db_conn);
    	exit(EXIT_FAILURE);
	}
	else
	{
		printf("Fonction mysql_stmt_execute() OK !\n");
	}

	unsigned int column_count = mysql_stmt_field_count(stmt);
	printf("Nombre de colonnes retournées: %u\n", column_count);


	MYSQL_BIND result_bind[11];
	memset(result_bind, 0, sizeof(result_bind));

	unsigned long name_length;
	unsigned long variety_length;
	unsigned long latin_name_length;
	unsigned long origine_length;
	unsigned long month_length;
	unsigned long month_c_length;
	unsigned long floor_length;
	unsigned long sun_length;
	unsigned long water_length;

	const size_t MAX_STRING_SIZE = 500;

	char name_fruit[MAX_STRING_SIZE];
	char variety_fruit[MAX_STRING_SIZE];
	char latin_name_fruit[MAX_STRING_SIZE];
	char origine_seed[MAX_STRING_SIZE];
	double price_seed;
	int quantity_stock;
	char month_gathering[MAX_STRING_SIZE];
	char month_cultivation[MAX_STRING_SIZE];
	char floor_type[MAX_STRING_SIZE];
	char quantity_sun_need[MAX_STRING_SIZE];
	char quantity_water_need[MAX_STRING_SIZE];

	_Bool error;

	name_fruit[MAX_STRING_SIZE - 1] = '\0';
	variety_fruit[MAX_STRING_SIZE - 1] = '\0';
	latin_name_fruit[MAX_STRING_SIZE - 1] = '\0';
	origine_seed[MAX_STRING_SIZE - 1] = '\0';
	month_gathering[MAX_STRING_SIZE - 1] = '\0';
	month_cultivation[MAX_STRING_SIZE - 1] = '\0';
	floor_type[MAX_STRING_SIZE - 1] = '\0';
	quantity_sun_need[MAX_STRING_SIZE - 1] = '\0';
	quantity_water_need[MAX_STRING_SIZE - 1] = '\0';

	result_bind[0].buffer_type = MYSQL_TYPE_STRING;
	result_bind[0].buffer = name_fruit;
	result_bind[0].buffer_length = MAX_STRING_SIZE;
	result_bind[0].length = &name_length;
	result_bind[0].error = &error;
	printf("Name length: %ld\n", name_length);
		
	result_bind[1].buffer_type = MYSQL_TYPE_STRING;
	result_bind[1].buffer = variety_fruit;
	result_bind[1].buffer_length = MAX_STRING_SIZE;
	result_bind[1].length = &variety_length;
	result_bind[1].error = &error;

	result_bind[2].buffer_type = MYSQL_TYPE_STRING;
	result_bind[2].buffer = latin_name_fruit;
	result_bind[2].buffer_length = MAX_STRING_SIZE;
	result_bind[2].length = &latin_name_length;
	result_bind[2].error = &error;

	result_bind[3].buffer_type = MYSQL_TYPE_STRING;
	result_bind[3].buffer = origine_seed;
	result_bind[3].buffer_length = MAX_STRING_SIZE;
	result_bind[3].length = &origine_length;
	result_bind[3].error = &error;

	result_bind[4].buffer_type = MYSQL_TYPE_DOUBLE;
	result_bind[4].buffer = &price_seed;
	result_bind[4].buffer_length = 500; //sizeof(price_seed);
	result_bind[4].error = &error;

	result_bind[5].buffer_type = MYSQL_TYPE_LONG;
	result_bind[5].buffer = &quantity_stock;
	result_bind[5].buffer_length = 500; //sizeof(quantity_stock);
	result_bind[5].error = &error;

	result_bind[6].buffer_type = MYSQL_TYPE_STRING;
	result_bind[6].buffer = month_gathering;
	result_bind[6].buffer_length = MAX_STRING_SIZE;
	result_bind[6].length = &month_length;
	result_bind[6].error = &error;

	result_bind[7].buffer_type = MYSQL_TYPE_STRING;
	result_bind[7].buffer = month_cultivation;
	result_bind[7].buffer_length = MAX_STRING_SIZE;
	result_bind[7].length = &month_c_length;
	result_bind[7].error = &error;

	result_bind[8].buffer_type = MYSQL_TYPE_STRING;
	result_bind[8].buffer = floor_type;
	result_bind[8].buffer_length = MAX_STRING_SIZE;
	result_bind[8].length = &floor_length;
	result_bind[8].error = &error;

	result_bind[9].buffer_type = MYSQL_TYPE_STRING;
	result_bind[9].buffer = quantity_sun_need;
	result_bind[9].buffer_length = MAX_STRING_SIZE;
	result_bind[9].length = &sun_length;
	result_bind[9].error = &error;

	result_bind[10].buffer_type = MYSQL_TYPE_STRING;
	result_bind[10].buffer = quantity_water_need;
	result_bind[10].buffer_length = MAX_STRING_SIZE;
	result_bind[10].length = &water_length;
	result_bind[10].error = &error;

	if (mysql_stmt_bind_result(stmt, result_bind) != 0)
	{
    	fprintf(stderr, "mysql_stmt_bind_result() failed: %s\n", mysql_stmt_error(stmt));
    	exit(EXIT_FAILURE);
	}
	else
	{
		printf("Fonction mysql_stmt_bind_result() OK !\n");
	}


	mysql_stmt_store_result(stmt);
	if (stmt == NULL)
	{
    	fprintf(stderr, "mysql_stmt_store_result() failed: %s\n", mysql_stmt_error(stmt));
    	mysql_stmt_close(stmt);
    	mysql_close(db_conn);
    	exit(EXIT_FAILURE);
	}
	else
	{
		printf("Fonction mysql_store_result() OK !\n");
	}

	unsigned long row_count = mysql_stmt_num_rows(stmt);
	printf("Nombre de lignes retournées: %lu\n", row_count);

	printf("Name length 2: %ld\n", name_length);
		
	// Prepare HTTP response
	char response_header[] = "HTTP/1.1 200 OK\r\nContent-Type: application/json\r\nAccess-Control-Allow-Origin: *\r\n\r\n";

    // Send response header
    send(client_socket, response_header, strlen(response_header), 0);
	
	send(client_socket, "[", 1, 0);
    int first_row = 1;

	while (mysql_stmt_fetch(stmt) == 0)
	{
    	// Étape 4 : Afficher la valeur après avoir récupéré le résultat
		printf("Fetched data: %s, %s, %s, %s, %f, %d, %s, %s, %s, %s, %s\n",
            name_fruit, variety_fruit, latin_name_fruit, origine_seed,
            price_seed, quantity_stock, month_gathering, month_cultivation,
			floor_type, quantity_sun_need, quantity_water_need);
		
		if (!first_row)
		{
            send(client_socket, ",", 1, 0); // Séparation entre les objets JSON
        }
        first_row = 0;

		char row_data[512];
sprintf(row_data,
        "{\"name_fruit\":\"%s\", \"variety_fruit\":\"%s\", \"latin_name_fruit\":\"%s\", "
        "\"origine_seed\":\"%s\", \"price_seed\":%f, \"quantity_stock\":%d, \"month_gathering\":\"%s\", "
        "\"month_cultivation\":\"%s\", \"floor_type\":\"%s\", \"quantity_sun_need\":\"%s\", \"quantity_water_need\":\"%s\"}",
        name_fruit, variety_fruit, latin_name_fruit, origine_seed,
        price_seed, quantity_stock, month_gathering, month_cultivation, floor_type, quantity_sun_need, quantity_water_need);
send(client_socket, row_data, strlen(row_data), 0);
    }
	
	// Send closing tag for the table
    send(client_socket, "]", 1, 0);
	printf("Send JSON OK !\n");
	mysql_stmt_close(stmt);
	stmt = NULL;  // Avoid dangling pointer
	printf("mysql_stmt_close OK !\n");
	close(client_socket);
	printf("socket closed OK !\n");



	return(0);
}