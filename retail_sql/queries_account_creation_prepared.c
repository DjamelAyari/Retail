#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <iconv.h>

#include "../retail_server/header.h"
#include "database.h"
#include "queries.h"

int queries_account_creation_prepared_statement(int client_socket, char *request_body, MYSQL* db_conn)
{
	printf("Entry in the queries_account_creation_prepared_statement() function !\n");

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

	/*char *pv = strchr(request_body, '?');
	pv++;*/

	char *pairk = strtok(request_body, "=");
	char *pairv = strtok(NULL, "&");

	printf("Entry in the while loop to insert in the array structure the HTTPS request parameters !\n");

	int compt_while_loop = 0;
	while (pairk && pairv)
	{
		array_size++;
		array = realloc(array, array_size * sizeof(struct key_value));
		array[array_size - 1].key = pairk;
		array[array_size - 1].value = pairv;

		pairk = strtok(NULL, "=");
        pairv = strtok(NULL, "&");

		printf("while loop that insert params of the HTTPS request in the array structure n°%d !\n", compt_while_loop);
		compt_while_loop++;
	}
	printf("ARRAY SIZE:%d\n", array_size);
	printf("Exit of the while loop !\n");

	printf("Entry in the loop for checking the values inserted in the array structure\n");
	for (int i = 0; i < array_size; i++)
	{
        	printf("Structure array Key: %s\n, Structure array Value: %s\n", array[i].key, array[i].value);
    }
		
	char query_account_creation_param[4095] = "INSERT INTO customer (familly_name_customer, name_customer, birth_date_customer, email_customer, phone_customer, alley_number_customer, repetition_index_customer, alley_type_customer, alley, zip_code_customer, city_customer, country, password_customer) "
                   "VALUES ( ";
					//")";
	printf("Print of the SQL preprared request: %s\n", query_account_creation_param);
	
	printf("Modification SQL request with the while loop in corelation of the parameters given by the client\n");

	int i = 0;
	int j = 0;
	while (i < array_size)
	{
		if (strcmp(array[i].key, "familly_name_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "name_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "birth_date_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "email_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "phone_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "alley_number_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "repetition_index_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "repetition_index_customer") == 0 && strcmp(array[i].value, "NULL") == 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}		
		if (strcmp(array[i].key, "alley_type_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "alley") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "zip_code_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "city_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "country") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...'),");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		if (strcmp(array[i].key, "password_customer") == 0 && strcmp(array[i].value, "NULL") != 0)
		{
			strcat(query_account_creation_param, " AES_ENCRYPT(?, 'Laurine12...')");
			printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);
			j++;
		}
		//strcat(query_account_creation_param, ");");

		i++;
	}
	strcat(query_account_creation_param, ");");
	printf("Array[i] = %s And Query = %s\n", array[i].key, query_account_creation_param);

	printf("I is the numbers of keys / values in the array structure: %d.\n", i);
	printf("J is the numbers of parameters given by the user: %d.\n", j);

	printf("The SQL request is now modified in order to contain user parameters.\n");

	if (mysql_ping(db_conn))
	{
    	fprintf(stderr, "Lost connection to MySQL server: %s\n", mysql_error(db_conn));
    	// Reinitialization of the connexion
    	// Close the prepared statement if it exists
		if (stmt != NULL)
		{
			// Close the current prepared statement
			mysql_stmt_close(stmt);
			// Avoid dangling pointer
			stmt = NULL;
		}
		// Close the current connection
		mysql_close(db_conn);
		// Avoid dangling pointer
		db_conn = NULL;

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

	if (mysql_stmt_prepare(stmt, query_account_creation_param, strlen(query_account_creation_param)) != 0)
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
		// Si cet index correspond à la clé price_edible bind le paramètre
		if (strcmp(array[k].key, "price_edible") == 0)
		{
			price = atof(array[k].value);
			bind[bind_index].buffer_type = MYSQL_TYPE_DOUBLE;
			bind[bind_index].buffer = &price;
			bind[bind_index].is_null = 0;
			printf("BIND BUFFER price_edible: %f\n", *(double*)bind[bind_index].buffer);
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
		send(client_socket, mysql_stmt_error(stmt), strlen(mysql_stmt_error(stmt)), 0);
    	mysql_stmt_close(stmt);
    	mysql_close(db_conn);
    	exit(EXIT_FAILURE);
	}
	else
	{
		printf("Fonction mysql_stmt_execute() OK !\n");
	}

	/*unsigned int column_count = mysql_stmt_field_count(stmt);
	printf("Nombre de colonnes retournées: %u\n", column_count);


	MYSQL_BIND result_bind[7];
	memset(result_bind, 0, sizeof(result_bind));

	unsigned long name_length;
	unsigned long variety_length;
	unsigned long latin_name_length;
	unsigned long origine_length;
	unsigned long month_length;

	const size_t MAX_STRING_SIZE = 500;

	char name_fruit[MAX_STRING_SIZE];
	char variety_fruit[MAX_STRING_SIZE];
	char latin_name_fruit[MAX_STRING_SIZE];
	char origine_edible[MAX_STRING_SIZE];
	double price_edible;
	int quantity_stock;
	char month_gathering[MAX_STRING_SIZE];

	_Bool error;

	name_fruit[MAX_STRING_SIZE - 1] = '\0';
	variety_fruit[MAX_STRING_SIZE - 1] = '\0';
	latin_name_fruit[MAX_STRING_SIZE - 1] = '\0';
	origine_edible[MAX_STRING_SIZE - 1] = '\0';
	month_gathering[MAX_STRING_SIZE - 1] = '\0';

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
	result_bind[3].buffer = origine_edible;
	result_bind[3].buffer_length = MAX_STRING_SIZE;
	result_bind[3].length = &origine_length;
	result_bind[3].error = &error;

	result_bind[4].buffer_type = MYSQL_TYPE_DOUBLE;
	result_bind[4].buffer = &price_edible;
	result_bind[4].buffer_length = 500; //sizeof(price_edible);
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
	
	/*send(client_socket, "[", 1, 0);
    int first_row = 1;

	while (mysql_stmt_fetch(stmt) == 0)
	{
    	// Étape 4 : Afficher la valeur après avoir récupéré le résultat
		printf("Fetched data: %s, %s, %s, %s, %f, %d, %s\n",
            name_fruit, variety_fruit, latin_name_fruit, origine_edible,
            price_edible, quantity_stock, month_gathering);
		
		if (!first_row)
		{
            send(client_socket, ",", 1, 0); // Séparation entre les objets JSON
        }
        first_row = 0;

		char row_data[512];
        sprintf(row_data,
                "{\"name_fruit\":\"%s\", \"variety_fruit\":\"%s\", \"latin_name_fruit\":\"%s\", "
                "\"origine_edible\":\"%s\", \"price_edible\":%f, \"quantity_stock\":%d, \"month_gathering\":\"%s\"}",
                name_fruit, variety_fruit, latin_name_fruit, origine_edible,
                price_edible, quantity_stock, month_gathering);
        send(client_socket, row_data, strlen(row_data), 0);
    }
	
	// Send closing tag for the table
    send(client_socket, "]", 1, 0);
	printf("Send JSON OK !\n");*/
	if (mysql_stmt_close(stmt) != 0)
	{
    	fprintf(stderr, "Error closing MySQL statement: %s\n", mysql_stmt_error(stmt));
	}
	else
	{
    	printf("mysql_stmt_close OK !\n");
	}
	stmt = NULL;  // Avoid dangling pointer

	if (close(client_socket) == -1)
	{
		perror("Error closing socket");
	}
	else
	{
		printf("socket closed OK !\n");
	}

	return(0);
}