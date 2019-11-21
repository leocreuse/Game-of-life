#include "cell.h"

int neigh_index(population *p_pop, cell *current, config *p_cfg){
	//This function returns -1 if the two cells represented by *p_pop and current aren't neighbors,
	//and the nuber corresponding to the possition of *p_pop in the array of neighbors of current, based on the order
	//given in the subject.	
	int dx=((*p_pop)->x)-(current->x);
	int dy=((*p_pop)->y)-(current->y);
	if((abs(dx)>1 && abs(dx)<((p_cfg->x)-1)) || (abs(dy)>1 && abs(dy)<((p_cfg->y)-1))){ //the cells are too far to be neighbours
		return -1;
	}
	else{
		dx=(abs(dx)==((p_cfg->x)-1)?-dx/((p_cfg->x)-1):dx);//to take care of the case where the two cells are on opposite borders (the map is actually a torus)
		dy=(abs(dy)==((p_cfg->y)-1)?-dy/((p_cfg->y)-1):dy);
		int temp=10*dx+dy;
		switch(temp){  //the 'breaks' are not needed beacause of the returns; the default case should not be triggered in theory...
			case 0:
				return -1;
			case 1:
				return 4;
			case -1:
				return 0;
			case 9:
				return 1;
			case 10:
				return 2;
			case 11:
				return 3;
			case -9:
				return 5;
			case -10:
				return 6;
			case -11:
				return 7;
			default:
				return -1;
		}
	}
}

void update_neig(population *p_pop, cell *current, config *p_cfg){
	if(*p_pop != NULL){						//check that we haven't reached the end of the population
		int pos=neigh_index(p_pop, current,p_cfg);
		if(pos>=0){
			(*p_pop)->neigh[(pos+4)%8]=current;
			current->neigh[pos]=*p_pop;
		}
		update_neig(&((*p_pop)->next),current,p_cfg);
	}
	return;
}

void nil( population* p_pop) {
	*p_pop=NULL; 				//simple initialization
}

void create_cell(population* p_pop, int pos_x, int pos_y, config *p_cfg){//I do not check for doubles since my code should not
															             //produce doubles from already alive cells.
															             //WARNING: The code WILL bug out if the user 
															             //intentionnaly introduces doubles in the list.
	cell* cel= malloc(sizeof(cell)); //reserve memory
	//printf("malloc ok\n");
	cel->x=(pos_x<0 ? pos_x % (p_cfg->x) + (p_cfg->x):pos_x % (p_cfg->x));//give correct position
	cel->y=(pos_y<0 ? pos_y % (p_cfg->y) + (p_cfg->y):pos_y % (p_cfg->y));
	cel->stat=NEWBORN; //cell just appeared, it must be a newborn
	//printf("param ok\n");
	for(int i=0;i<8;i++){
		//printf("loop start");
		cel->neigh[i]=NULL; //initialize as if there were no alive neighbors
	}
	//printf("neigh ok");
	cel->next=*p_pop;  //stack the cel
	*p_pop=cel;
	//printf("stacking ok");
	update_neig(p_pop,*p_pop,p_cfg);//update the neighbors
	//printf("all ok...\n");
}

int size(population *p_pop) {
	if(*p_pop==NULL){
		return 0;
	}
	else{
		return size(&((*p_pop)->next))+1;
	}
}




void kill_cell(population *p_pop) {
	if(*p_pop==NULL){
		//there's nothing to kill
	}
	else{ //let's kill the current cell
		cell  *dead=*(p_pop);
		*p_pop=((*p_pop)->next);
		for(int i=0;i<8;i++){
			if(dead->neigh[i]!=NULL){
				(dead->neigh[i])->neigh[(i+4)%8]=NULL;  //must make sure that all the neighbors are aware that this cell is dead
			}
		}
		free(dead);
	}
}

void deallocate_pop(population* p_pop) {
	if(*p_pop==NULL){//nothing to remove, we're done.
		
	}
	else{
		kill_cell(p_pop);  //remove first element
		deallocate_pop(p_pop);//remove the rest
	}
}

void print_pop(population *p_pop) {
	if(*p_pop==NULL){
		printf("\n");
	}
	else{
		printf("(%d, %d): ",(*p_pop)->x,(*p_pop)->y);
		switch((*p_pop)->stat){
			case NEWBORN:
				printf("Newborn\n");
				break;
			case ALIVE:
				printf("Alive\n");
				break;
			case DYING:
				printf("Dying\n");
				break;
			default:
				printf("\n");
				break;
		}
		print_pop(&((*p_pop)->next));
	}
}

void print_map(population *p_pop, config  *p_cfg){
	char *line=malloc(sizeof(char)*((p_cfg->x)+1));
	line[(p_cfg->x)]='\0';
	cell *current=*p_pop;
	for(int i = 0;i<(p_cfg->y);i++){
			for(int i=0;i<(p_cfg->x);i++){
				line[i]='_';
			}
			current=*p_pop;
			while(current!=NULL){
				if(current->y==(p_cfg->y)-i-1){
					switch(current->stat){
						case NEWBORN:
							line[current->x]='/';
							break;
						case ALIVE:
							line[current->x]='|';
							break;
						case DYING:
							line[current->x]='\\';
							break;
						default:
							break;
					}
				}
				current=current->next;
			}
			printf("%s\n",line);
	}
	free(line);
}

char stat_to_print(cell *current){
	if(current!=NULL){
		switch(current->stat){
			case NEWBORN:
				return '/';
			case ALIVE:
				return '|';
			case DYING:
				return '\\';
			default:
				return '_';
		}
	}
	return '0';
}
void print_neighbors(population *p_pop){
	cell *first = *p_pop;
	printf("_____\n");
	printf("%c|%c|%c\n",stat_to_print(first->neigh[5]),stat_to_print(first->neigh[4]),stat_to_print(first->neigh[3]));
	printf("_____\n");
	printf("%c|X|%c\n",stat_to_print(first->neigh[6]),stat_to_print(first->neigh[2]));
	printf("_____\n");
	printf("%c|%c|%c\n",stat_to_print(first->neigh[7]),stat_to_print(first->neigh[0]),stat_to_print(first->neigh[1]));
	printf("_____\n");
}

void toggle_cell_rec(population *p_pop,population *init, int x, int y,config *p_cfg){
	if(*p_pop==NULL){
		create_cell(init,x,y,p_cfg);
	}
	else if((*p_pop)->x==x && (*p_pop)->y==y){
		kill_cell(p_pop);
	}
	else{
		toggle_cell_rec(&((*p_pop)->next),init,x,y,p_cfg);
	}
	
}

void toggle_cell(population *p_pop, int x, int y, config *p_cfg){
	toggle_cell_rec(p_pop,p_pop,x,y,p_cfg);
}
