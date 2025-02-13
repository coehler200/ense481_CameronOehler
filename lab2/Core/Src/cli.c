/*
 * cli.c
 *
 *  Created on: Oct 8, 2024
 *  Updated on: Dec 2, 2024
 *  Updated on: Feb 13, 2025
 *      Author: coehl
 */

#include "cli.h"
#include <string.h>
#include "serial.h"
#include <stdio.h>

#define MAX_DATA 64
#define MAX_TOKENS 16
#define TX_BUFFER_SIZE 1024

char *CLEAR_ENTIRE_SCREEN = "\x1b[2J\x1b[1;1H";
char *PROMPT = "> ";
char *HELP = "Available Commands\r\n"
		"===================\r\n"
		"activate <flag> - remotely set a system flag\r\n"
		"maintenance [ON, OFF] - disable or enable user buttons\r\n"
		"clear - clears the screen\r\n"
		"help - display this message\r\n";
char *UNKNOWN_CMD = "Unknown command. "
		"Use 'help' for list of valid commands.\r\n";
char *CLEAR_CMD_WINDOW = "\x1b[9;1H\x1b[0J";

char data[MAX_DATA+1]; // Allow for \0 to be added
uint16_t dataLen = 0;
char rxBuffer[1];

int tokenizeString(char* string, char** tokens){
	char* savePtr = string;
    char* token;
    int index = 0;

    while((token = strtok_r(savePtr, " ", &savePtr))){
    	tokens[index++] = token;
    	if(index > MAX_TOKENS) return index;
    }
    return index;
}

void processCommand(char** tokens, int numTokens){
	char txBuffer[TX_BUFFER_SIZE] = "";
	strcat(txBuffer, "\r\n");
	strcat(txBuffer, "EXAMPLE RESPONSE\r\n");
	strcat(txBuffer, PROMPT);
	serialPrint(txBuffer, strlen(txBuffer));
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	receiveChar(rxBuffer);
	char c = rxBuffer[0];
	if(c == '\r' || c == '\n'){ // Enter via CR or LF
		data[dataLen++] = '\0';
		char* tokens[MAX_TOKENS] = {};
		int numTokens = tokenizeString(data, tokens);
		processCommand(tokens, numTokens);
		dataLen = 0;
	}
	else if(c == 127){ // Backspace
		if(dataLen != 0){
			dataLen--;
			serialPrint(&c, 1);
		}
	}
	else{
		if(dataLen < MAX_DATA){ // Prevent overflow
			serialPrint(&c, 1);
			data[dataLen++] = c;
		}
	}
}

void setupCliWithInterrupt(){
	char txBuffer[TX_BUFFER_SIZE] = "";
	strcat(txBuffer, CLEAR_ENTIRE_SCREEN);
	strcat(txBuffer, PROMPT);
	serialPrint(txBuffer, strlen(txBuffer));
	receiveChar(rxBuffer);
	while(1);
}

//void setupCli(){
//	serialPrintBlocking(CLEAR_ENTIRE_SCREEN, strlen(CLEAR_ENTIRE_SCREEN));
//	serialPrintBlocking(PROMPT, strlen(PROMPT));
//}
//
//void pollCli(){
//	for(;;){
//		char c = receiveCharBlocking();
//		if(c == '\r' || c == '\n'){ // Enter via CR or LF
//			data[dataLen++] = '\0';
//
//			char* tokens[MAX_TOKENS] = {};
//			int numTokens = tokenizeString(data, tokens);
//			processCommand(tokens, numTokens);
//			dataLen = 0;
//		}
//		else if(c == 127){ // Backspace
//			if(dataLen != 0){
//				dataLen--;
//				serialPrintBlocking(&c, 1);
//			}
//		}
//		else{
//			if(dataLen < MAX_DATA){ // Prevent overflow
//				serialPrintBlocking(&c, 1);
//				data[dataLen++] = c;
//			}
//		}
//	}
//}
