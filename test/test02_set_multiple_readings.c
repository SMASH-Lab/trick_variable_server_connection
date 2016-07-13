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
 * @file test02_set_multiple_readings.c
 * @author Alfredo Garro, University of Calabria (Italy), alfredo.garro@unical.it
 * @date 29 June 2016
 * @brief This is a simple test that shows how to connect and interact to a Trick Variable Server 
 * for querying and reading simulation data until they are provided by the Server. 
 * The source simulation is the SIM_cannon_jet reported in the Trick Tutorial 
 * "Trick Simulation Environment User Training Materials Trick 2013.0 Release",
 * see Section 9.0 and subsequent.
 * The program takes as first input parameter the port number on which the Trick Variable Server is active. 
 * The server is supposed to run locally. If not, the IP address must be provided after the port number as the second input parameter.
 *
 * @see https://github.com/nasa/Trick/wiki/Variable-Server for the documentation on the commands that can be sent to the Trick Variable Server.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/trick_variable_server_connection.h"


int main (int narg, char** args)
{
	int socket_desc;
 	char* host = "127.0.0.1";
	int port = 0; 	

	if (!args[1]) {
		puts("Port Number not specified as input parameter. Try again!");
		return 1;
	}
	else port = atoi(args[1]);

	if (args[2]) {
		host = args[2];
	}

	printf("Host = %s\n", host );
	printf("SeverPort = %i\n", port);

    	char *message , server_reply[2000];
     
    	//Create a default socket
    	socket_desc = create_default_socket();
    	if (socket_desc == -1) {
        	printf("socket not created");
    	}
 
    	//Connect to the Trick Variable Server
        if (connect_to_variable_server(socket_desc, host, port) < 0) {
        	puts("failed to connect to the Trick Variable Server");
       		return 1;
    	}
     
    	puts("Connected\n");
     
    	//Set the update period
	double period = 0.5;
	if (set_cycle(socket_desc, period) < 0) {
        	puts("failed to set the update period");
       		return 1;
    	}
	
	printf("Update Period Set to %f\n", period );

	//Set the copy mode
	double mode = 1; //values are copied at the end of execution frame
	if (set_copy_mode(socket_desc, mode) < 0) {
        	puts("failed to set the copy mode");
       		return 1;
    	}
	printf("Copy Mode Set to %f\n", mode );


	//Add variables to observe
	char* var_name = "time";
	if (add_variable_to_server(socket_desc,var_name) < 0) {
		puts("add variable to server failed");
       		return 1;
    	}
	puts(var_name);
	puts(" variable added\n");	
	
	var_name = "dyn.baseball.pos[0]";
	if (add_variable_to_server(socket_desc,var_name) < 0) {
		puts("add variable to server failed");
       		return 1;
    	}
	puts(var_name);
	puts(" variable added\n");	
	
	var_name = "dyn.baseball.pos[1]";
	if (add_variable_to_server(socket_desc,var_name) < 0) {
		puts("add variable to server failed");
       		return 1;
    	}
	puts(var_name);
	puts(" variable added\n");
	
	var_name = "dyn.baseball.pos[2]";
	if (add_variable_to_server(socket_desc,var_name) < 0) {
		puts("add variable to server failed");
       		return 1;
    	}
	puts(var_name);
	puts(" variable added\n");

	
	var_name = "dyn.baseball.g";
	if (add_variable_to_server(socket_desc,var_name) < 0) {
		puts("add variable to server failed");
       		return 1;
    	}
	puts(var_name);
	puts(" variable added\n");

	//Receive data from the server
	int data_recv_ack = 1;

	while (data_recv_ack > 0) {
		data_recv_ack = receive_message_from_variable_server(socket_desc, server_reply, 2000, 0); 
		if (data_recv_ack <= 0) {
        		puts("no data to receive\n");
		}
		else {
			puts("data received:\n");
    			puts(server_reply);
			puts("------------------\n");			
    		}
	}
    	return 0;

}
