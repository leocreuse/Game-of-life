#include "evolution.h"
//#include "cell.h"
void all_alive(population *p_pop){
	if(*p_pop !=NULL){
		if((*p_pop)->stat==NEWBORN){
			(*p_pop)->stat=ALIVE;
		}
		all_alive(&((*p_pop)->next));
	}
	return;
}

void kill_dying(population *p_pop){
	if(*p_pop !=NULL){
		if((*p_pop)->stat==DYING){
			kill_cell(p_pop);
			kill_dying(p_pop);
		}
		else{
			kill_dying(&((*p_pop)->next));
		}
	}
	
	return;
}

void age(population *p_pop){
	if(*p_pop != NULL){
		int alive_neighbors=0;  //to keep track wether or not we should age this cell or not.
		for(int i=0; i<8;i++){
			if(((*p_pop)->neigh[i])!=NULL){
				alive_neighbors++;
			}
		}
		if(alive_neighbors!=2 && alive_neighbors!=3){
			(*p_pop)->stat=DYING;
		}
		age(&((*p_pop)->next));
	}
}
void delta_to_coord(cell *current, int index, int *x, int *y){//I assume here that this function will not be called on a NULL cell...
	int _x=current->x;
	int _y=current->y;
	switch(index){//here some cases could have been combined to make the code more compact, but I don't have the courage to find the syntax right now.
		case 0:
			_y-=1;
			break;
		case 1:
			_y-=1;
			_x+=1;
			break;
		case 2:
			_x+=1;
			break;
		case 3:
			_y+=1;
			_x+=1;
			break;
		case 4:
			_y+=1;
			break;
		case 5:
			_y+=1;
			_x-=1;
			break;
		case 6:
			_x-=1;
			break;
		case 7:
			_y-=1;
			_x-=1;
			break;
		default:
			break;
	}
	*x=_x;
	*y=_y;
}
/*NOTE: My thought process for this function is as follow:
* Since we must check for each dead cell we encounter if it has the right
* number of alive neighbors, this implies running through the whole list of alive cells
* for each dead cell encountered. This is automaticaly donne by adding a new cell to the list of 
* alive cells, so it is easier for me to do this way and the complexity remains in O(size(p_pop)).
*/

void rec_renew(population *p_pop,population *original, config *p_cfg){
	if(*p_pop !=NULL){
		if((*p_pop)->stat==NEWBORN){
			rec_renew(&((*p_pop)->next),original,p_cfg);
		}
		else{
			for(int i=0;i<8;i++){//analyse each neighbor
				if(((*p_pop)->neigh[i])==NULL){//only look at those which are dead
					int x=0;
					int y=0;
					delta_to_coord(*p_pop,i,&x,&y);
					//create_cell(&temp_stack,x,y,x_size, y_size);
					create_cell(original,x,y,p_cfg);//create new cell to count the neighbors (only alive and dying, not the newborns), if nb_neigh!=3 at the end we delete the cell.
					int nb_neigh=0;
					for(int i=0;i<8;i++){//check numbre of alive neighbors of the "new" cell
						if((((*original)->neigh[i]) != NULL) && ((((*original)->neigh[i])->stat)!=NEWBORN)){
							nb_neigh++;
						}
					}
					if(nb_neigh!=3){//only keep the new cell if it has 3 neighbors
						kill_cell(original);
					}
				}
			}
			//Once we're done finding all the actual new cells, we examine the rest of the list:
			rec_renew(&((*p_pop)->next),original,p_cfg);//here the parameter original plays an important role:
																//without it, there would be less cells when looking for neighbors
																//which would make the algorithm false
		}
	}
}
//using a shell function just to hide the recursion-required arguments.
void renew(population *p_pop, config *p_cfg){
	rec_renew(p_pop, p_pop,p_cfg);
	//and we add to the original list the new cells:
	return;
}
