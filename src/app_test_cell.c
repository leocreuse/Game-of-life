#include <stdio.h>
#include "cell.h"
#include "evolution.h"
#include "load.h"
#include "generate-image.h"
//#include "gui.h"
//#include <SDL2/SDL.h>
/**************************************
 * 
 * 			THIS PROGRAM IS JUST A 
 * 			SCRATCH PAD, THERE iS NO
 * 			PARTICULAR GOAL TO IT.
 * 			IT ONLY SERVES DEBBUGING
 * 			PURPOSES, FEEL FREE TO 
 * 			TRY THINGS OUT.
 * 			IN THE ACTUAL STATE OF THINGS 
 * 			DUE TO THE ENTRY DATA FILE IT
 * 			WILL TAKE A FEW MINUTES TO COMPLETE
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * 
 * *************************************/


int main(void){ //simple tests to make sure all functions work as intended
	population pop;
	//int sim_size = 5;
	nil(&pop);
	int x=5;
	int y=5;
	int nb=0;
	load_init("./data/ex-complexe.txt",&pop,&x,&y,&nb);
	create_cell(&pop,2,3,x,y);
	/*create_cell(&pop,2,4,x,y);
	create_cell(&pop,1,3,x,y);
	create_cell(&pop,-4,7,x,y);
	create_cell(&pop,3,3,x,y);
	create_cell(&pop,0,0,x,y);
	create_cell(&pop,2,0,x,y);
	create_cell(&pop,4,0,x,y);
	create_cell(&pop,1,1,sim_size,sim_size);
	create_cell(&pop,2,1,sim_size,sim_size);
	create_cell(&pop,2,2,sim_size,sim_size);
	
	//print_map(&pop,x,y);
	//printf("\n");
	//single_frame(&pop,x,y,23);
	printf("%d,\n",nb);
	printf("frame width: %d\n",x);
	printf("frame heigth: %d\n", y);
	all_alive(&pop);
	kill_dying(&pop);
	//printf("\n\n");
	//print_map(&pop,x,y);
	age(&pop);
	renew(&pop,x,y);
	all_alive(&pop);
	kill_dying(&pop);
	//printf("\n\n");
	//print_map(&pop,x,y);
	//print_pop(&pop);
	age(&pop);
	//printf("\n\n");
	//print_map(&pop,x,y);
	renew(&pop,x,y);
	//single_frame(&pop,x,y,24);
	//SDL_Event event;
	//unsigned int timer=SDL_GetTicks;
	printf("init start...");
	render_animation(&pop,x,y,nb,false);
	*/
	
	*/
	//all_frames(&pop,x,y,nb,false);
	//print_neighbors(&pop);
	//print_pop(&pop);
	/*for(int i=0;i<nb;i++){
		all_alive(&pop);
		kill_dying(&pop);
		age(&pop);
		renew(&pop,x,y);
		printf("%d\n",i);
	}*/
	//printf("\n");
	/*
	//printf("\n");
	//print_neighbors(&pop);
	printf("\n");
	print_map(&pop,sim_size,sim_size);
	
	printf("\n");
	print_map(&pop,sim_size,sim_size);
	print_pop(&pop);
	//printf("\n");
	//kill_cell(&pop);
	//kill_cell(&pop);
	//print_map(&pop,sim_size);
	//print_pop(&pop);
	//print_pop(&pop);*/
	print_pop(&pop);
	deallocate_pop(&pop);
	//printf("%d\n",(-3)%7);
	return 0;
}
