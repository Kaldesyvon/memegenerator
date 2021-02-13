/*
 * options.h
 *
 *  Created on: 10 Feb 2021
 *      Author: Martin
 *
 *  Description: header file for options.c
 */

#ifndef OPTIONS_H_
#define OPTIONS_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


static void end(char* message);

struct MemeGenOpt{
	char* file;
	char* colour; // might change type to enum later if problems occurs
	char* TopText;
	char* BottomText;
};


struct MemeGenOpt ParseOptions(int argc, char* argv[]);

#endif /* OPTIONS_H_ */
