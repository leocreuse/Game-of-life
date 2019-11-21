#include <stdio.h>
#include "cell.h"
#include "load.h"
#include "evolution.h"
#include "generate-image.h"

//The user should specify the path to the data file in the comand line as first argument.

int main(int argc, char *argv[]){
	population pop;
	nil(&pop);
	config cfg;
	default_config(&cfg);
	load_init(argv[1],&pop,&cfg);
	all_frames(&pop,&cfg);
	deallocate_pop(&pop);
	return 0;
}
