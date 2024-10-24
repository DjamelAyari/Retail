#ifndef QUERIES_H
#define QUERIES_H

int queries_edible_fruit_prepared_statement(int client_socket, char *request_path, MYSQL* db_conn);

int queries_edible_fruit(int client_socket, char *request_path, MYSQL* db_conn);

int queries_edible_vegetable_prepared_statement(int client_socket, char *request_path, MYSQL* db_conn);

int queries_edible_vegetable(int client_socket, char *request_path, MYSQL* db_conn);

int queries_plant_fruit_prepared_statement(int client_socket, char *request_path, MYSQL* db_conn);

int queries_plant_fruit(int client_socket, char *request_path, MYSQL* db_conn);

int queries_plant_vegetable_prepared_statement(int client_socket, char *request_path, MYSQL* db_conn);

int queries_plant_vegetable(int client_socket, char *request_path, MYSQL* db_conn);

int queries_seed_fruit_prepared_statement(int client_socket, char *request_path, MYSQL* db_conn);

int queries_seed_fruit(int client_socket, char *request_path, MYSQL* db_conn);

int queries_seed_vegetable_prepared_statement(int client_socket, char *request_path, MYSQL* db_conn);

int queries_seed_vegetable(int client_socket, char *request_path, MYSQL* db_conn);

int queries_account_creation_prepared_statement(int client_socket, char *request_body, MYSQL* db_conn);



#endif
