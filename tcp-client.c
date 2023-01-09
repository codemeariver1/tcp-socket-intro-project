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
	// "Client" socket workflow: socket() -> connect() -> recv().

	// Create a client socket.
	int network_socket; // Socket descriptor.
	// socket() param1: Socket domain.
	// socket() param2: Socket type (TCP: Connection socket / UDP: Datagram socket).
	// socket() param3: Protocol specification.
	network_socket = socket(AF_INET, SOCK_STREAM, 0); // In this case: (Internet, TCP, Default).

	// Define an address for the socket to connect to.
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET; // Specify an address family (Same as socket family).
	server_address.sin_port = htons(9002); // Specify port to connect to.
									  // htons() converts port number to appropriate 
									  //	network byte order format to be read.
	server_address.sin_addr.s_addr = INADDR_ANY; // Specify IP address.
												 //		(INADDR_ANY: routes to an IP on local machine)
	// Connect to the socket server.
	// connect() param1: Socket to connect to.
	// connect() param2: Server address struct.
	// connect() param3: Address size. 
	int connection_status = connect(
		network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

	// Check connection status
	if (connection_status == -1)
		printf("There was an error making a connection to the remote socket\n\n");

	// Recieve data from the server.
	// recv() param1: Socket to recieve data from.
	// recv() param2: Server data storage location.
	// recv() param3: Size of the data/buffer.
	// recv() param4: Optional flag.

	char server_response[256];
	recv(network_socket, &server_response, sizeof(server_response), 0);

	// Output the server's response
	printf("The server sent the data: %s\n", server_response);

	// Close the socket
	close(network_socket);

	return 0;
}
