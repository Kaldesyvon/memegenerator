/*
 * options.c
 *
 *  Created on: 10 Feb 2021
 *      Author: Martin
 *
 *  Description: this file process arguments typed in command line using getopt()
 */

#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>

#include "options.h"

static void end(char* message){
	fprintf(stderr, "%s\n", message);
	exit(1);
}

struct MemeGenOpt ParseOptions(int argc, char* argv[]){

	extern int optind;
	extern char* optarg;

	struct MemeGenOpt meme_options = {0};

	char g = 0;


	if (argc <= 0) {
		end("argc <= 0");
	}

	while (1)
	{
		// parsing arguments with getopt()

		int option_index = 0;

		static struct option long_options[] = {
			{ "file",   1, 0, 'f' },
			{ "colour", 1, 0, 'c' },
			{ 0,        0, 0,  0 }
		};

		g = getopt_long(argc, argv, "f:c:",
				long_options, &option_index);

		if (g == -1)
			break;

		switch (g)
		{
			case 'f':
				meme_options.file = optarg;
				break;
			case 'c':
				meme_options.colour = optarg;
				break;
			case '?':
				break;
			default:
				end("invalid argument");
		}
	}

	// assign top and bottom text using optind as a indicator of next argument to be processed by getopt()

	meme_options.TopText = argv[optind];
	meme_options.BottomText = argv[optind + 1];

	return meme_options;

}
