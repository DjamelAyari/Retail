#include "header.h"
#include "../retail_sql/database.h"
#include "../retail_sql/queries.h"

//Prototype of the function that will handle clients request
void handle_client_request(int client_socket, MYSQL* db_conn);

int main()
{

//Initialization of WINSOCK
#if defined(_WIN32)
	WSADATA d;
	if(WSAStartup(MAKEWORD(2, 2), &d))
	{
		fprintf(stderr, "Failed to initialize.\n");
		return(1);
	}
#endif
	printf("WINSOCK initialization OK !\n");
	
	//Configuration of the address
	printf("Configuring address...\n");
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;

	struct addrinfo *bind_address;
	getaddrinfo("127.0.0.1", "8443", &hints, &bind_address);
	
	printf("Configuration of the address OK !\n");

	//Socket creation
	printf("Creating socket...\n");
	SOCKET socket_listen;
	socket_listen = socket(bind_address -> ai_family, bind_address -> ai_socktype, bind_address -> ai_protocol);
	if(!ISVALIDSOCKET(socket_listen))
	{
		fprintf(stderr, "socket() failed. (%d)\n", GETSOCKETERRNO());
		return(1);
	}
	printf("Socket creation OK !\n");

	//Binding the socket to the address
	printf("Binding socket to address...\n");
	if(bind(socket_listen, bind_address -> ai_addr, bind_address -> ai_addrlen))
	{
		fprintf(stderr, "bind() failed. (%d)\n", GETSOCKETERRNO());
		return(1);
	}
	printf("Binding the socket to the address OK !\n");
	freeaddrinfo(bind_address);
	printf("Free addrinfo structure OK !\n");

	//Listening for connexion
	printf("Listening...\n");
	if(listen(socket_listen, 10) < 0)
	{
		fprintf(stderr, "listen() failed. (%d)\n", GETSOCKETERRNO());
		return(1);
	}

	//Connexion to the MySQL database
	MYSQL* db_conn = db_connect();
        if (db_conn == NULL)
        {
                fprintf(stderr, "Failed to connect to database.\n");
                return 1;
        }
	printf("Connexion to the MySQL database OK !\n");
	
	//Creation of the sets for the multiplexing with select() function
	fd_set master;
	FD_ZERO(&master);
	FD_SET(socket_listen, &master);
	SOCKET max_socket = socket_listen;
	printf("Creation of the sets for the multiplexing with select() function OK !\n");

	//Waiting for the connexion of clients
	printf("Waiting for connections...\n");
	while(1)
	{
	
		fd_set reads;
		reads = master;

		if(select(max_socket+1, &reads, 0, 0, 0) < 0)
		{
			fprintf(stderr, "select() failed. (%d)\n", GETSOCKETERRNO());
			return(1);
		}

		SOCKET i;
		for(i = 1; i <= max_socket; ++i)
		{
			if(FD_ISSET(i, &reads))
			{
				if(i == socket_listen)
				{
					struct sockaddr_storage client_address;
					socklen_t client_len = sizeof(client_address);
					SOCKET socket_client = accept(socket_listen, (struct sockaddr*) &client_address, &client_len);
					if(!ISVALIDSOCKET(socket_client))
					{
						fprintf(stderr, "accept() failed. (%d)\n", GETSOCKETERRNO());
						return(1);
					}

					FD_SET(socket_client, &master);
					if(socket_client > max_socket)
					{
						max_socket = socket_client;
					}

					char address_buffer[100];
					getnameinfo((struct sockaddr*) &client_address, client_len, address_buffer, sizeof(address_buffer), 0, 0, NI_NUMERICHOST);
					printf("New connection from %s\n", address_buffer);
				} //end if i == socket_listen
				
				else
				{
					handle_client_request(i, db_conn);
					FD_CLR(i, &master);
			
				} //end else
			} //end if FD_ISSET
		} //end for i to max_socket

	} //end while
	
	printf("Closing listening socket...\n");
	CLOSESOCKET(socket_listen);

#if defined(_WIN32)
	WSACleanup();
#endif

	printf("Finished.\n");


	return(0);

} //end main()

//Handling client request function
void handle_client_request(int client_socket, MYSQL* db_conn)
{
	char request[8192];
	ssize_t bytes_received;
	ssize_t total_bytes_received = 0;
	memset(request, 0, sizeof(request));
	
	 while ((bytes_received = recv(client_socket, request + total_bytes_received, sizeof(request) - total_bytes_received - 1, 0)) > 0)
	 {
        	total_bytes_received += bytes_received;

        	if (bytes_received < sizeof(request) - total_bytes_received - 1)
        	{
            		break;
        	}
     }

    	if (bytes_received < 0)
    	{
        	perror("recv");
        	return;
    	}

	printf("Sending of the headers to the browser in the handle_options() function OK ! \n");


	request[bytes_received] = '\0';
	printf("REQUEST: %s\n", request);
	printf("BYTES RECEIVED: %ld\n", bytes_received);

	void handle_cors(int client_socket)
	{
		// Send headers for preflight (OPTIONS) requests
		char header_response[] =
			"HTTP/1.1 200 OK\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n"
			"Access-Control-Allow-Headers: Content-Type\r\n"
			"Access-Control-Max-Age: 86400\r\n"
			"Content-Length: 0\r\n"
			"\r\n";

		send(client_socket, header_response, strlen(header_response), 0);
		printf("header_response for OPTIONS send OK !\n");
		printf("header_response for OPTIONS: %s\n", header_response);
	}

	/*char *body = strstr(request, "\r\n\r\n");
	if(body != NULL)
	{
		body += 4;
		//printf("BODY: %s\n", body);
	}
	printf("BODY: %s\n", body);*/
	// Extract the headers
    char *content_type = NULL;
    char *body = strstr(request, "\r\n\r\n");
    if (body != NULL)
    {
        *body = '\0';  // Split headers from body
        body += 4;    // Move pointer to the start of the body
        content_type = strstr(request, "Content-Type: ");  // Extract content type
        if (content_type != NULL)
        {
            content_type += 14;  // Move pointer past "Content-Type: "
            char *end_of_header = strstr(content_type, "\r\n");
            if (end_of_header != NULL)
            {
                *end_of_header = '\0';  // Null-terminate the content type string
            }
        }
    }

    // Check if body is present and validate its length
    size_t content_length = 0;
    if (content_type && strstr(request, "Content-Length: ") != NULL)
    {
        char *length_str = strstr(request, "Content-Length: ") + 16;  // Move past "Content-Length: "
        char *end_of_length = strstr(length_str, "\r\n");
        if (end_of_length != NULL)
        {
            *end_of_length = '\0';  // Null-terminate for string conversion
            content_length = strtoul(length_str, NULL, 10);  // Convert to unsigned long
        }
    }

    // Log the expected length and total bytes received
    printf("Expected Content-Length: %zu, Total Bytes Received: %zd\n", content_length, total_bytes_received);

    if (body == NULL || strlen(body) == 0 || content_length != total_bytes_received - (body - request))
    {
        fprintf(stderr, "Error: No body present in the request or body length mismatch.\n");
        return;
    }

    // Log content type
    printf("Content-Type: %s\n", content_type ? content_type : "NULL");

    // Process request based on content type
    if (content_type && strcmp(content_type, "application/json") == 0)
    {
        // Handle JSON request
        printf("Processing JSON body: %s\n", body);
        // Handle JSON processing
        // handle_json_request(client_socket, body);
    }
    else if (content_type && strcmp(content_type, "application/x-www-form-urlencoded") == 0)
    {
        // Handle URL-encoded request
        printf("Processing URL-encoded body: %s\n", body);
        // Handle URL-encoded processing
        // handle_url_encoded_request(client_socket, body);
    }
    else
    {
        fprintf(stderr, "Error: Unsupported Content-Type.\n");
        // Send an appropriate response for unsupported content type
        char response[] = "HTTP/1.1 415 Unsupported Media Type\r\n"
                          "Content-Length: 0\r\n"
                          "\r\n";
        send(client_socket, response, sizeof(response) - 1, 0);
        return;
    }
	
	//Parsing of the URL
	char *method = strtok(request, " ");
	char *path = strtok(NULL, " ");
	char *version = strtok(NULL, "\r\n");

	printf("Method: %s\n", method ? method : "NULL");
	printf("Path: %s\n", path ? path : "NULL");
	printf("Version: %s\n", version ? version : "NULL");

	if (strcmp(method, "OPTIONS") == 0)
	{
		// Handle CORS preflight request
		handle_cors(client_socket);
	} else
	{
		// Handle actual GET, POST, etc. requests
		// Here, you will also send CORS headers for the actual response
		char header_response[] =
			"HTTP/1.1 200 OK\r\n"
			"Access-Control-Allow-Origin: *\r\n"
			"Content-Type: application/x-www-form-urlencoded\r\n"
			"\r\n"
			"{\"message\": \"Success\"}\r\n";

		send(client_socket, header_response, strlen(header_response), 0);
		printf("header_response if method is not OPTION send OK !\n");
		printf("header_response if method is not OPTION: %s\n", header_response);
	}



	if (path == NULL || version == NULL)
	{
    		fprintf(stderr, "Invalid request format.\n");
    		return;
	}
	
	printf("Test before the loop that replace + signs by space\n");

	if (path == NULL)
	{
    		fprintf(stderr, "Path is NULL. Cannot proceed.\n");
    		return;
	}

	if (path == NULL)
	{
    		fprintf(stderr, "Path is NULL. Cannot proceed.\n");
    		return;
	}


	printf("Path length: %zu\n", strlen(path));
	
	//Loop that replace the + with space
	int i = 0;
	while (path[i] != '\0')
	{
		if (path[i] == '+')
		{
			path[i] = ' ';
		}

		i++;
	}

	printf("Path after replacement: %s\n", path);

	printf("Remplacement of + signs by space OK !!!\n");
	
	//Condition to choose the appropriate function for the URL
	if (strstr(path, "/edible_fruit") == path)
	{
		if (strchr(path, '?') != NULL)
		{
			queries_edible_fruit_prepared_statement(client_socket, path, db_conn);
		}

		else
		{
			queries_edible_fruit(client_socket, path, db_conn);
		}
	}

	else if (strstr(path, "/edible_vegetable") == path)
	{
		if (strchr(path, '?') != NULL)
		{
			queries_edible_vegetable_prepared_statement(client_socket, path, db_conn);
		}

		else
		{
			queries_edible_vegetable(client_socket, path, db_conn);
		}
	}

	else if (strstr(path, "/plant_fruit") == path)
	{
		if (strchr(path, '?') != NULL)
		{
			queries_plant_fruit_prepared_statement(client_socket, path, db_conn);
		}

		else
		{
			queries_plant_fruit(client_socket, path, db_conn);
		}
	}

	else if (strstr(path, "/plant_vegetable") == path)
	{
		if (strchr(path, '?') != NULL)
		{
			queries_plant_vegetable_prepared_statement(client_socket, path, db_conn);
		}

		else
		{
			queries_plant_vegetable(client_socket, path, db_conn);
		}
	}

	else if (strstr(path, "/seed_fruit") == path)
	{
		if (strchr(path, '?') != NULL)
		{
			queries_seed_fruit_prepared_statement(client_socket, path, db_conn);
		}

		else
		{
			queries_seed_fruit(client_socket, path, db_conn);
		}
	}

	else if (strstr(path, "/seed_vegetable") == path)
	{
		if (strchr(path, '?') != NULL)
		{
			queries_seed_vegetable_prepared_statement(client_socket, path, db_conn);
		}

		else
		{
			queries_seed_vegetable(client_socket, path, db_conn);
		}
	}

	else if (strstr(path, "/account_creation") == path)
	{
		queries_account_creation_prepared_statement(client_socket, body, db_conn);
	}
}
