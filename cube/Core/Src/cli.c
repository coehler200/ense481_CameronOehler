/**
  ******************************************************************************
  * @file     cli.c
  * @brief    Provide cli communications
  * @author   Cameron Oehler
  ******************************************************************************
  *
  * This file provides methods for setting up, polling, and executing commands
  * from a cli environment.
  *
  * Created on: Oct 8, 2024
  * Updated on: Dec 2, 2024
  * Updated on: Feb 13, 2025
  * Updated on: Mar 23, 2025
  *
  ******************************************************************************
  */

#include "cli.h"
#include <string.h>
#include "serial.h"
#include <stdio.h>
#include "version.h"
#include "buildDate.h"

/** Maximum number of characters to buffer */
#define MAX_DATA 64
/** Maximum number of tokens to parse */
#define MAX_TOKENS 16
/** Maximum size of the buffer to send a response */
#define TX_BUFFER_SIZE 1024

char *CLEAR_ENTIRE_SCREEN = "\x1b[2J\x1b[1;1H";
char *PROMPT = "> ";
char *HELP = "Available Commands\r\n"
		"===================\r\n"
		"printBinInfo - print version and build info for the binary\r\n"
		"orientation - print out imu orientation information\r\n"
		"stream - stream IMU orientation information continuously forever\r\n"
		"clear - clears the screen\r\n"
		"help - display this message\r\n";
char *UNKNOWN_CMD = "Unknown command. "
		"Use 'help' for list of valid commands.\r\n";

char data[MAX_DATA+1]; // Allow for \0 to be added
uint16_t dataLen = 0;
char rxBuffer[1];

/**
 * Given a string, break it into various tokens. ' ' is the delimiter.
 *
 * @param string the full command string
 * @param tokens an empty array to be filled with parsed tokens
 *
 * @return the number of tokens parsed
 */
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

/**
 * Processes tokens into some output.
 * This is where the actual functionality of the cli is determined.
 *
 * @param tokens the tokens that make up a command
 * @param numTokens the number of tokens
 */
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
	else if(strcmp(currentToken, "orientation") == 0){
		if(numTokens > 1){
			strcat(txBuffer, UNKNOWN_CMD);
		}
		else{
			float x;
			osMessageQueueGet(imuOrientationQueueHandle, &x, 0, osWaitForever);
			float y;
			osMessageQueueGet(imuOrientationQueueHandle, &y, 0, osWaitForever);
			float z;
			osMessageQueueGet(imuOrientationQueueHandle, &z, 0, osWaitForever);
			char buf[128] = "";
			sprintf(buf, "roll: %f, pitch: %f, heading: %f\r\n", x, y, z);
			strcat(txBuffer, buf);
		}
	}
	else if(strcmp(currentToken, "stream") == 0){
		if(numTokens > 1){
			strcat(txBuffer, UNKNOWN_CMD);
		}
		else{
			while(1){
				float x;
				osMessageQueueGet(imuOrientationQueueHandle, &x, 0, osWaitForever);
				float y;
				osMessageQueueGet(imuOrientationQueueHandle, &y, 0, osWaitForever);
				float z;
				osMessageQueueGet(imuOrientationQueueHandle, &z, 0, osWaitForever);
				char buf[128] = "";
				sprintf(buf, "{'roll': %f, 'pitch': %f, 'heading': %f}", x, y, z);
				serialPrintBlocking(buf, strlen(buf));
			}
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

/**
 * Clear the screen and print the prompt
 */
void setupCli(){
	serialPrintBlocking(CLEAR_ENTIRE_SCREEN, strlen(CLEAR_ENTIRE_SCREEN));
	serialPrintBlocking(PROMPT, strlen(PROMPT));
}

/**
 * Continuously poll the serial device for character input. Buffer input and
 * remove buffered input on 'backspace'. On CR/LF pass the buffered command to
 * the token parser and command processor.
 */
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
