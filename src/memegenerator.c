/*
 ============================================================================
 Name        : memegenerator.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : meme generator
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#include "memegenerator.h"
#include "options.h"

char* trim(char *str){
    char* str1 = (char*)malloc(sizeof(str));

    unsigned int k = 0;
    unsigned int i = 0;

    for (; i < strlen(str); i++) {
    	if(str[i] != ' ' || str[i] != '\t' || str[i] != '\n'){
			str1[k] = str[i];
			k++;
    	}
    }

    str1[k++] = '\0';

    return str1;
}

void readHeader(FILE *fp, int *width, int *height)
{
	char ch;
	int width_, height_;
	int  maxval;

	fseek(fp, 0, SEEK_SET);

	do {
		ch = getc(fp);
	} while (ch != '\n');

	/* comments can be found in file starting with '#'.
	*  this code secure their skipping */
	ch = getc(fp);

	while (ch == '#'){
		do {
			ch = getc(fp);
		} while (ch != '\n');
		ch = getc(fp);
	}
	while (ch == ' '){
		ch = getc(fp);
	}
	if (!isdigit(ch)) end("don't know read from file");

	ungetc(ch, fp);		/* put that digit back */

	fscanf(fp, "%d %d\n%d\n", &width_, &height_, &maxval);

	*width = width_;
	*height = height_;
}

Meme *MemeRead(char* name){

	Meme* meme = malloc(sizeof(Meme));
	meme->name = name;

	int width = 0;
	int height = 0;

	FILE* fp = fopen(name, "rb");

	if (!fp) end("failed to open file for reading");

	char ch;

	if (fscanf(fp, "P%c\n", &ch) != 1) end("cannot read file");
	else if (ch == '3'){
		fclose(fp);
		fp = fopen(name, "r");
		printf("file is non binary\n");
	}
	else if (ch == '6') printf("file is binary\n");
	else end("file is not .ppm");

	readHeader(fp, &width, &height);

	meme->width = width;
	meme->height = height;

//	for (int i = 0; i < height; i++){
//		for (int j = 0; j < width; j++){
//			int r, g, b;
//			if(fscanf(fp, "%d%d%d", &r, &g, &b) != 3) end("cannot load pixel");
//			meme->pixels[i * height + width].red = r;
//			meme->pixels[i * height + width].green = g;
//			meme->pixels[i * height + width].blue = b;
////			printf("%d %d %d\n",r,g,b);
//		}
//	}
	size_t size = (size_t)(width *height * 3);

	char* dummy = trim(meme->data);
	meme->data =(char*)malloc(size+1);
	memcpy(meme->data, dummy, sizeof(dummy));
	free(dummy);

	size_t num = fread((void*)meme->data,1, size,fp);

	printf("%s\n", meme->data);

	if (num != size) end("data not read properly");


	fclose(fp);
	return meme;
}


int main(int argc, char* argv[]) {
	struct MemeGenOpt meme_opt = ParseOptions(argc, argv);

	char* topText;
	char* bottomText;
	char* file;
	char* colour;

	topText = meme_opt.TopText;
	bottomText = meme_opt.BottomText;
	file = meme_opt.file;
	colour = meme_opt.colour;

	Meme* meme = MemeRead(file);


//	printf("%d %d\n", meme->width, meme->height);
	printf("%s\n%s\n%s\n%s\n", file, colour, topText, bottomText);

	free(meme);
//	getchar();
	end("nice");
}

