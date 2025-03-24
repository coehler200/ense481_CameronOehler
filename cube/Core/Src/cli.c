/*
 * cli.c
 *
 *  Created on: Oct 8, 2024
 *  Updated on: Dec 2, 2024
 *  Updated on: Feb 13, 2025
 *  Updated on: Mar 23, 2025
 *      Author: coehl
 */

#include "cli.h"
#include <string.h>
#include "serial.h"
#include <stdio.h>
#include "version.h"
#include "buildDate.h"

#define MAX_DATA 64
#define MAX_TOKENS 16
#define TX_BUFFER_SIZE 1024

char *CLEAR_ENTIRE_SCREEN = "\x1b[2J\x1b[1;1H";
char *PROMPT = "> ";
char *HELP = "Available Commands\r\n"
		"===================\r\n"
		"printBinInfo - print version and build info for the binary\r\n"
		"clear - clears the screen\r\n"
		"help - display this message\r\n";
char *UNKNOWN_CMD = "Unknown command. "
		"Use 'help' for list of valid commands.\r\n";

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

	char* currentToken = tokens[0];

	if(strcmp(currentToken, "") == 0){
		if(numTokens > 1){
			strcat(txBuffer, UNKNOWN_CMD);
		}
	}
	else if(strcmp(currentToken, "printBinInfo") == 0){
		if(numTokens > 1){
			strcat(txBuffer, UNKNOWN_CMD);
		}
		else{
			char buf[128] = "";
			sprintf(buf, "Version: %s\r\nBuild Date: %s\r\n", GIT_COMMIT, BUILD_DATE);
			strcat(txBuffer, buf);
		}
	}
	else if(strcmp(currentToken, "clear") == 0){
		if(numTokens > 1){
			strcat(txBuffer, UNKNOWN_CMD);
		}
		else{
			strcat(txBuffer, CLEAR_ENTIRE_SCREEN);
		}
	}
	else if(strcmp(currentToken, "help") == 0){
		if(numTokens > 1){
			strcat(txBuffer, UNKNOWN_CMD);
		}
		else{
			strcat(txBuffer, HELP);
		}
	}
	else{
		strcat(txBuffer, UNKNOWN_CMD);
	}

	strcat(txBuffer, PROMPT);
	//serialPrint(txBuffer, strlen(txBuffer));
	serialPrintBlocking(txBuffer, strlen(txBuffer));
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//	receiveChar(rxBuffer);
//	char c = rxBuffer[0];
//	if(c == '\r' || c == '\n'){ // Enter via CR or LF
//		data[dataLen++] = '\0';
//		char* tokens[MAX_TOKENS] = {};
//		int numTokens = tokenizeString(data, tokens);
//		processCommand(tokens, numTokens);
//		dataLen = 0;
//	}
//	else if(c == 127){ // Backspace
//		if(dataLen != 0){
//			dataLen--;
//			serialPrint(&c, 1);
//		}
//	}
//	else{
//		if(dataLen < MAX_DATA){ // Prevent overflow
//			serialPrint(&c, 1);
//			data[dataLen++] = c;
//		}
//	}
//}

//void setupCliWithInterrupt(){
//	char txBuffer[TX_BUFFER_SIZE] = "";
//	strcat(txBuffer, CLEAR_ENTIRE_SCREEN);
//	strcat(txBuffer, PROMPT);
//	serialPrint(txBuffer, strlen(txBuffer));
//	receiveChar(rxBuffer);
//	while(1);
//}

void setupCli(){
	serialPrintBlocking(CLEAR_ENTIRE_SCREEN, strlen(CLEAR_ENTIRE_SCREEN));
	serialPrintBlocking(PROMPT, strlen(PROMPT));
}

void pollCli(){
	for(;;){
		char c = receiveCharBlocking();
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
				serialPrintBlocking(&c, 1);
			}
		}
		else{
			if(dataLen < MAX_DATA){ // Prevent overflow
				serialPrintBlocking(&c, 1);
				data[dataLen++] = c;
			}
		}
	}
}
