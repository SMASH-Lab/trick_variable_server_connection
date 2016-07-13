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
 * @file trick_variable_server_connection.h
 * @author Alfredo Garro, University of Calabria (Italy), alfredo.garro@unical.it
 * @date 23 June 2016
 * @brief The library provides a set of C functions to connect and interact to a Trick Variable Server.
 *
 * @see https://github.com/nasa/Trick/wiki/Variable-Server for the documentation on the commands that can be sent to the Trick Variable Server.
 */

#ifndef _trick_variable_server_connection_h_
#define _trick_variable_server_connection_h_

/**
 *   @brief Create a socket to connect to the Trick Variable Server on the given host and port.
 *
 *   @return  Upon successful completion, the fuction returns a nonnegative integer, 
 *            the socket file descriptor. Otherwise a value of -1 is returned and errno 
 *            is set to indicate the error.  
 */

int create_default_socket();


/**
 *   @brief create a socket to connect to the Trick Variable Server on the given host and port.
 *   
 *   @param domain:   which can be AF_INET (Internet adress) or AF_UNIX (File system pathnames); 
 *   @param type:     which can be @c SOCK_STREAM, @c SOCK_DGRAM, @c SOCK_SEQPACKET;  
 *   @param protocol: which, if non-zero, must specify a protocol supported by the address family.
 *
 *   @return  Upon successful completion, the fuction returns a nonnegative integer, 
 *            the socket file descriptor. Otherwise a value of -1 is returned and errno 
 *            is set to indicate the error.  
 */

int create_generic_socket(int domain, int type, int protocol);


/**
 *   @brief Connect to the Trick Variable Server on the given host and port.
 * 
 *   @param socket: socket file descriptor; 
 *   @param host:   host IPv4 address; 
 *   @param port:   service port number.
 *
 *   @return  Upon successful completion, the function returns 0. Otherwise, -1 is returned 
 *            and errno is set to indicate the error.  
 */

int connect_to_variable_server(int socket, char* host, int port);


/**
 *   @brief sends the given command and any commands to the Trick Variable Server.     
 *   
 *   @param socket:  socket file descriptor; 
 *   @param command: the comand to send. 
 *
 *   @return  Upon successful completion, the function returns the number of bytes sent. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int send_command_to_variable_server(int socket, char* command);


/**
 *   @brief commands the Trick Variable Server to send variable data in ASCII.
 *   
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_ascii(int socket);


/**
 *   @brief commands the Trick Variable Server to send variable data in BINARY.
 *   
 *   @param socket: socket file descriptor; 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_binary(int socket);


/**
 *   @brief commands the Trick Variable Server to send variable data in binary and to omit names.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_binary_no_names(int socket);


/**
 *   @brief sets the Trick Variable Server to synchronized mode.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_sync(int socket); 


/**
 *   @brief commands the Trick Variable Server to stop sending data.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int pause(int socket); 


/**
 *   @brief commands the Trick Variable Server to resume sending data.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int unpause(int socket);


/**
 *   @brief adds the named variable to be observed through the Trick Variable Server.
 *
 *   @param socket:        socket file descriptor;
 *   @param variable_name: name of the variable to be observed.  
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int add_variable_to_server(int socket, char* variable_name);


/**
 *   @brief adds the named variable to the Trick Variable Server specifying the units of measure.
 *
 *   @param socket:        socket file descriptor;
 *   @param variable_name: nome of the variable to be observed;
 *   @param units:         units of measure of the variable to be observed.  
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int add_variable_to_sever_with_units(int socket, char* variable_name, char* units);


/**
 *   @brief removes the named variable observed through the Trick Variable Server.
 *
 *   @param socket:        socket file descriptor;
 *   @param variable_name: name of the variable to stop observing.  
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int remove_variable_from_server(int socket, char* variable_name);


/**
 *   @brief clears all the variables from the Trick Variable Server.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int clear(int socket);


/**
 *   @brief sets the period at which the Trick Variable Server sends updates.
 *
 *   @param socket:  socket file descriptor;
 *   @param period:  the period at which the Trick Variable Server sends updates. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_cycle(int socket, double period);


/**
 *   @brief sets how values are copied out of the simulation by the Trick Variable Server.
 *
 *   @param socket: socket file descriptor;
 *   @param mode:   0 (values are copied out of the sim asynchronously); 1 (values are copied at the end of execution frame); 
 *                  2 (copies are done at a multiple and offset of the Executive software frame). 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_copy_mode(int socket, int mode);


/**
 *   @brief requests a single update from the Trick Variable Server.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int poll(int socket);


/**
 *   @brief sends a run command to the simulation.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int run(int socket);


/**
 *   @brief sends a freeze command to the simulation.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int freeze(int socket);


/**
 *   @brief closes the connection to the Trick Variable Server.
 *
 *   @param sock: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int close(int socket);


/**
 *   @brief validates the addresses of the Trick Variable Server.
 *
 *   @param socket: socket file descriptor; 
 *   @param validate: 0 for validate False, >0 for validate True.
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_validate_addresses(int socket, int validate);


/**
 *   @brief sends an enable or disable real time command to the simulation.
 *
 *   @param socket: socket file descriptor; 
 *   @param enabled: 0 for validate False, >0 for validate True.
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_real_time(int socket, int enabled);


/**
 *   @brief sets the Trick Variable Server's debug level.
 *
 *   @param socket:  socket file descriptor;
 *   @param level: the debug level.
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_debug_level(int socket, int level); 


/**
 *   @brief sets this client's tag.
 *
 *   @param socket: socket file descriptor;
 *   @param  tag: the client's tag to set.  
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int set_client_tag(int socket, char* tag); 


/**
 *   @brief receives a message from the Trick Variable Server.
 *
 *   @param socket:       socket file descriptor;
 *   @param server_reply: a buffer where the message from the server will be stored; 
 *   @param lenght:       the length in bytes of the buffer pointed to by the server_reply argument;
 *   @param flags:        Specifies the type of message reception.         
 *
 *   @return  Upon successful completion, the fuction returns the length of the message in bytes. 
 *            If no messages are available to be received and the peer has performed an orderly shutdown, 
 *            the method returns 0. Otherwise, -1 is returned and errno is set to indicate the error.  
 */


int receive_message_from_variable_server(int socket, void *server_reply, unsigned int length, int flags);


/**
 *   @brief disables subsequent send and receive operations on a socket.
 *
 *   @param socket: socket file descriptor. 
 *
 *   @return  Upon successful completion, the function returns 0. 
 *            Otherwise, -1 is returned and errno is set to indicate the error.  
 */

int socket_shutdown(int socket);

#endif
