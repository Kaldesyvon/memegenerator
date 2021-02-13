/*
 * memegenerator.h
 *
 *  Created on: 10 Feb 2021
 *      Author: Martin
 *
 *  Description: header file for memegenerator.c
 */

#ifndef MEMEGENERATOR_H_
#define MEMEGENERATOR_H_

#include <sys/types.h>
#include <stdint.h>

//#include "options.h"

static void end(char* message){
	perror("error: ");
	fprintf(stderr, "%s\n", message);
	exit(1);
}

typedef struct Pixel{
	uint8_t blue;
	uint8_t green;
	uint8_t red;

} Pixel;

typedef struct Meme
{
	char* name;
	int width;
	int height;
	char* data;
} Meme;

void readHeader(FILE *fp, int *width, int *height);

Meme *MemeRead(char *name);
Meme *MemeCreate(int width, int height);

void   MemeWrite(Meme *image, char *filename);

int    MemeWidth(Meme *image);
int    MemeHeight(Meme *image);

void   MemeClear(Meme *image,  char red,  char green,  char blue);

void   MemeSetPixel(Meme *image, int x, int y, int chan, char val);
char MemeGetPixel(Meme *image, int x, int y, int chan);


#endif /* MEMEGENERATOR_H_ */
