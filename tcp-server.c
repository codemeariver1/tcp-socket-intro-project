#include <stdio.h>
#include <stdlib.h>

// Definitions and APIs about sockets
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

// Store address information
#include <netinet/in.h>

int main()
{
	// "Server" socket workflow: socket() -> bind() -> listen() -> accept().

	char server_message[256] = "You have reached the server!";

	// Create a server socket.
	int server_socket; // Socket descriptor.
	// socket() param1: Socket domain.
	// socket() param2: Socket type (TCP: Connection socket / UDP: Datagram socket).
	// socket() param3: Protocol specification.
	server_socket = socket(AF_INET, SOCK_STREAM, 0); // In this case: (Internet, TCP, Default).

	// Define an address for the socket to connect to.
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET; // Specify an address family (Same as socket family).
	server_address.sin_port = htons(9002); // Specify port to connect to.
									  // htons() converts port number to appropriate 
									  //	network byte order format to be read.
	server_address.sin_addr.s_addr = INADDR_ANY; // Specify IP address. 
												 //		(INADDR_ANY: routes to an IP on local machine)

	// Bind the socket to our specified IP and port.
	// bind() param1: Socket to bind.
	// bind() param2: Server address struct.
	// bind() param3: Address size. 
	bind(server_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// Listen for server connections.
	// listen() param1: Socket.
	// listen() param2: Waiting connection backlog size.
	listen(server_socket, 5);

	// Accept the server connections for sending and recieving.
	int client_socket;
	// accept() param1: Server socket to accept connections.
	// accept() param2: Address of client connection struct.
	// accept() param3: Client address size. 
	client_socket = accept(server_socket, NULL, NULL);

	// Send data to client socket.
	// send() param1: Socket we're sending data on.
	// send() param2: Data to send to socket.
	// send() param3: Size of the data. 
	// send() param4: Optional flag.
	send(client_socket, server_message, sizeof(server_message), 0);

	close(server_socket);

	return 0;
}