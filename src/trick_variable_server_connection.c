/****************************************************************************
 * Copyright (C) 2016 by Alfredo Garro                                      *
 *                                                                          *
 * This file is part of the Trick Variable Server Connection C library      *
 *                                                                          *
 *   TrickVariableServerConnection is free software: you can redistribute   *
 *   it and/or modify it under the terms of the GNU Lesser General Public   *
 *   License as published by the Free Software Foundation, either version   *
 *   3 of the License, or (at your option) any later version.               *
 *                                                                          *
 *                                                                          *
 *   The Trick Variable Server Connection libarry is distributed in the     *
 *   hope that it will be useful but WITHOUT ANY WARRANTY; without even the *
 *   implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR        *
 *   PURPOSE. See theGNU Lesser General Public License for more details.    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with TrickVariableServerConnection.                      *
 *   If not, see <http://www.gnu.org/licenses/>.                            *
 ****************************************************************************/

/**
 * @file trick_variable_server_connection.c
 * @author Alfredo Garro, University of Calabria (Italy), alfredo.garro@unical.it
 * @date 23 June 2016
 * @brief The library provides a set of C functions to connect and interact to a Trick Variable Server.
 *
 * @see https://github.com/nasa/Trick/wiki/Variable-Server for the documentation on the commands that can be sent to the Trick Variable Server.
 */


#include<stdio.h> //printf,...
#include<string.h>    //strlen,...
#include<sys/socket.h>    //socket,...
#include<arpa/inet.h> //inet_addr,...

#include "../include/trick_variable_server_connection.h"

/**
 * Function: create_default_socket
 * ----------------------------
 *   Create a socket to connect to the Trick Variable Server on the given host and port
 *   with the following default parameters:
 *   
 *   domain:   @c AF_INET (Internet address); 
 *   type:     @c SOCK_STREAM, which provides sequenced, reliable, bidirectional, connection-mode
 *             byte streams, and may provide a transmission mechanism for out-of-band data; 
 *   protocol: 0, which causes to use an unspecified default protocol appropriate 
 *             for the requested socket type.
 *   @return   Upon successful completion, the fuction returns a nonnegative integer, 
 *             the socket file descriptor. Otherwise a value of -1 is returned and errno 
 *             is set to indicate the error.  
 */

int create_default_socket() {
	return socket(AF_INET , SOCK_STREAM , 0);
}


/**
 * Function: create_generic_socket
 * ----------------------------
 *   create a socket to connect to the Trick Variable Server on the given host and port
 *   with a set of user specified parameters.
 *      
 *   @param domain:   which can be @c AF_INET (Internet adress) or @c AF_UNIX (File system pathnames); 
 *   @param type:     which can be @c SOCK_STREAM (that Provides sequenced, reliable, bidirectional,
 *                    connection-mode byte streams, and may provide a transmission mechanism for out-of-band data);
 *                    @c SOCK_DGRAM (that Provides datagrams, which are connectionless-mode, unreliable messages of
 *                    fixed maximum length); @c SOCK_SEQPACKET (that Provides sequenced, reliable, bidirectional,
 *                    connection-mode transmission path for records. A record can be sent using one or more output
 *                    operations and received using one or more input operations, but a single operation never
 *                    transfers part of more than one record. Record boundaries are visible to the receiver 
 *                    via the @c MSG_EOR flag); 
 *   @param protocol: which, if non-zero, must specify a protocol supported by the address family.
 *
 *   @return  Upon successful completion, the fuction returns a nonnegative integer, 
 *            the socket file descriptor. Otherwise a value of -1 is returned and errno 
 *            is set to indicate the error.  
 */

int create_generic_socket(int domain, int type, int protocol) {
	return socket(domain , type , protocol);
}


/**
 * Function: connect_to_variable_server
 * ----------------------------
 *   Connect to the Trick Variable Server on the given host and port.
 *   
 *   @param socket: socket file descriptor; 
 *   @param host:   host IPv4 address; 
 *   @param port:   service port number.
 *
 *   @return  Upon successful completion, the function returns 0. Otherwise, -1 is returned 
 *            and errno is set to indicate the error.  
 */

int connect_to_variable_server(int socket, char* host, int port) {
	struct sockaddr_in server;
	
	server.sin_addr.s_addr = inet_addr(host);
    	server.sin_family = AF_INET;
    	server.sin_port = htons( port );
	
	return connect(socket , (struct sockaddr *)&server , sizeof(server));	
}


/**
 * Function: send_command_to_variable_server
 * ----------------------------
 *   sends the given command and any commands to the Trick Variable Server
 *   A newline is automatically appended to the given command.
 *   
 *   @param socket:  socket file descriptor; 
 *   @param command: the comand to send. 
 *
 *   @return  Upon successful completion, the function returns the number of bytes sent. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int send_command_to_variable_server(int socket, char* command) {
        char cmd[512];

	if (sizeof(cmd)<strlen(command)+2) {
		return -1;	
	}
	else {
		strncpy(cmd, command, sizeof(cmd));
		strncat(cmd, "\n", (sizeof(cmd) - strlen(cmd)-1)); 
		return send(socket , cmd , strlen(cmd) , 0);
	}
}


/**
 * Function: set_ascii
 * ----------------------------
 *   commands the Trick Variable Server to send variable data in ASCII.
 *   
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_ascii(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_ascii()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: set_binary
 * ----------------------------
 *   commands the Trick Variable Server to send variable data in BINARY.
 *   
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_binary(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_binary()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: set_binary_no_names
 * ----------------------------
 *   commands the Trick Variable Server to send variable data in binary and to
 *   omit names.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_binary_no_names(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_binary_nonames()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: set_sync
 * ----------------------------
 *   sets the Trick Variable Server to synchronized mode.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_sync(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_sync(1)")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: pause
 * ----------------------------
 *   commands the Trick Variable Server to stop sending data.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int pause(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_pause()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: unpause
 * ----------------------------
 *   commands the Trick Variable Server to resume sending data.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int unpause(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_unpause()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: add_variable_to_server
 * ----------------------------
 *   adds the named variable to be observed through the Trick Variable Server.
 *
 *   @param socket:        socket file descriptor;
 *   @param variable_name: name of the variable to be observed.  
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int add_variable_to_server(int socket, char* variable_name) {


	char  cmd[512];
        const char* prefix="trick.var_add(\"";
        const char* suffix="\")"; 

	if (sizeof(cmd)<(strlen(prefix)+strlen(variable_name)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, variable_name, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}
}


/**
 * Function: add_variable_to_server_with_units
 * ----------------------------
 *   adds the named variable to be observed through the Trick Variable Server
 *   specifying the units of measure.
 *
 *   @param socket:        socket file descriptor;
 *   @param variable_name: name of the variable to be observed;
 *   @param units:         units of measure of the variable to be observed.  
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int add_variable_to_sever_with_units(int socket, char* variable_name, char* units) {


	char  cmd[512];
        const char* prefix="trick.var_add(\"";
	const char* infix="\", \"";
        const char* suffix="\")"; 

	if (sizeof(cmd)<(strlen(prefix)+strlen(variable_name)+strlen(infix)+strlen(units)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, variable_name, (sizeof(cmd) - strlen(cmd)-1));
		strncat(cmd, infix, (sizeof(cmd) - strlen(cmd)-1));
		strncat(cmd, units, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}
}


/**
 * Function: remove_variable_from_server
 * ----------------------------
 *   removes the named variable observed through the Trick Variable Server.
 *
 *   @param socket:          socket file descriptor;
 *   @param variable_name:   name of the variable to stop observing.  
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int remove_variable_from_server(int socket, char* variable_name) {


	char  cmd[512];
        const char* prefix="trick.var_remove(\"";
        const char* suffix="\")"; 

	if (sizeof(cmd)<(strlen(prefix)+strlen(variable_name)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, variable_name, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}
}


/**
 * Function: clear
 * ----------------------------
 *   clears all the variables from the Trick Variable Server.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int clear(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_clear()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: set_cycle
 * ----------------------------
 *   sets the period at which the Trick Variable Server sends updates.
 *
 *   @param socket:  socket file descriptor;
 *   @param period:  the period at which the Trick Variable Server sends updates. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_cycle(int socket, double period) {
	
	char  cmd[512];
	const char* prefix="trick.var_cycle(";
	char  per[128];
	const char* suffix=")"; 

	snprintf(per, 128, "%lf", period);	
	
	if (sizeof(cmd)<(strlen(prefix)+strlen(per)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, per, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}

}


/**
 * Function: set_copy_mode
 * ----------------------------
 *   sets how values are copied out of the simulation by the Trick Variable Server.
 *
 *   @param socket: socket file descriptor;
 *   @param mode:   0 (values are copied out of the sim asynchronously); 1 (values are copied at the end of execution frame); 
 *                  2 (copies are done at a multiple and offset of the Executive software frame). 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_copy_mode(int socket, int mode) {
	
	char  cmd[512];
	const char* prefix="trick.var_set_copy_mode(";
	char  mod[4];
	const char* suffix=")"; 

	snprintf(mod, 4, "%i", mode);	
	
	if (sizeof(cmd)<(strlen(prefix)+strlen(mod)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, mod, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}

}


/**
 * Function: poll
 * ----------------------------
 *   requests a single update from the Trick Variable Server.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int poll(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_send()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: run
 * ----------------------------
 *   sends a run command to the simulation.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int run(int socket) {
	if (send_command_to_variable_server(socket,"trick.exec_run()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: freeze
 * ----------------------------
 *   sends a freeze command to the simulation.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int freeze(int socket) {
	if (send_command_to_variable_server(socket,"trick.exec_freeze()")<0) {
		return -1;
	}
	else {
		return 0;
	}
}


/**
 * Function: close
 * ----------------------------
 *   closes the connection to the Trick Variable Server.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int close(int socket) {
	if (send_command_to_variable_server(socket,"trick.var_exit()")<0) {
		return -1;
	}
	else {
		close(socket);		
		return 0;
	}
}


/**
 * Function: set_validate_addresses
 * ----------------------------
 *   validates the addresses of the Trick Variable Server.
 *
 *   @param socket:   socket file descriptor. 
 *   @param validate: 0 for validate False, >0 for validate True;
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_validate_addresses(int socket, int validate) {
	
	char  cmd[256];
	const char* prefix="trick.var_validate_address(";
	char  val[16];
	const char* suffix=")"; 

	if (validate>0) strncpy(val, "True", 16); else strncpy(val, "False", 16);
	
	if (sizeof(cmd)<(strlen(prefix)+strlen(val)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, val, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}

}


/**
 * Function: set_real_time
 * ----------------------------
 *   sends an enable or disable real time command to the simulation
 *
 *   @param socket:  socket file descriptor; 
 *   @param enabled: 0 for validate False, >0 for validate True.
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_real_time(int socket, int enabled) {
	
	char  cmd[256];
	const char* prefix="trick.real_time_";
	char  enab[16];
	const char* suffix="()"; 

	if (enabled>0) strncpy(enab, "enable", 16); else strncpy(enab, "disable", 16);	
	
	if (sizeof(cmd)<(strlen(prefix)+strlen(enab)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, enab, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}

}


/**
 * Function: set_debug_level
 * ----------------------------
 *   sets the Trick Variable Server's debug level
 *
 *   @param socket:  socket file descriptor;
 *   @param level:   the debug level.
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_debug_level(int socket, int level) {
	
	char  cmd[256];
	const char* prefix="trick.var_debug(";
	char  lev[64];
	const char* suffix=")"; 

	snprintf(lev, 64, "%i", level);	
	
	if (sizeof(cmd)<(strlen(prefix)+strlen(lev)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, lev, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}

}
    

/**
 * Function: set_client_tag
 * ----------------------------
 *   sets this client's tag
 *
 *   @param socket: socket file descriptor;
 *   @param tag:    the client's tag to set.  
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_client_tag(int socket, char* tag) {

	char  cmd[512];
        const char* prefix="trick.var_set_client_tag(\"";
        const char* suffix="\")"; 

	if (sizeof(cmd)<(strlen(prefix)+strlen(tag)+strlen(suffix)+1)) {
		return -1;	
	}
	else {
		strncpy(cmd, prefix, sizeof(cmd));
		strncat(cmd, tag, (sizeof(cmd) - strlen(cmd)-1));
                strncat(cmd, suffix, (sizeof(cmd) - strlen(cmd)-1));
		if (send_command_to_variable_server(socket,cmd)<0) {
			return -1;
		}
		else {
			return 0;
		}
	}
}


/**
 * Function: receive_message_from_variable_server
 * ----------------------------
 *   receives a message from the Trick Variable Server
 *
 *   @param socket:       socket file descriptor;
 *   @param server_reply: a buffer where the message from the server will be stored; 
 *   @param lenght:       the length in bytes of the buffer pointed to by the server_reply argument
 *   @param flags:        Specifies the type of message reception. Values of this argument are formed by 
 *                        logically OR'ing  zero or more of the following values:
 *                        @c MSG_PEEK (peeks at an incoming message. The data is treated as unread and the next call 
 *                        will still return this data);
 *                        @c MSG_OOB (requests out-of-band data. The significance and semantics of out-of-band data 
 *                        are protocol-specific); 
 *			  @c MSG_WAITALL (requests that the function block until the full amount of data requested can 
 *                        be returned. The function may return a smaller amount of data if a signal is caught, if the 
 *                        connection is terminated, if MSG_PEEK was specified, or if an error is pending for the socket).          
 *
 *   @return  Upon successful completion, the fuction returns the length of the message in bytes. 
 *            If no messages are available to be received and the peer has performed an orderly shutdown, 
 *            the method returns 0. Otherwise, -1 is returned and errno is set to indicate the error.  
 */


int receive_message_from_variable_server(int socket, void *server_reply, unsigned int lenght, int flags) {
	return recv(socket , server_reply , lenght , flags); 
}


/**
 * Function: socket_shutdown
 * ----------------------------
 *   disables subsequent send and receive operations on a socket.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int socket_shutdown(int socket) {
	return shutdown(socket, SHUT_RDWR);
}
