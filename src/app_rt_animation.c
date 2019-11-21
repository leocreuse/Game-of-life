#include "load.h"
#include "cell.h"
#include "gui.h"
#include "evolution.h"

int main(int argc, char *argv[]){
	population pop;
	nil(&pop);
	config cfg;
	load_config(&cfg);
	load_init(argv[1],&pop,&cfg);
	cfg.it=-1;
	//print_pop(&pop);
	render_animation(&pop,&cfg);
	deallocate_pop(&pop);
	return 0;
}
