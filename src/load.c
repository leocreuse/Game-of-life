#include "load.h"
#include <string.h>

bool load_init(const char *file, population *p_pop, config *p_cfg){ 
	FILE *fp=NULL;
	fp=fopen(file,"r");
	bool print_x_warning=false;
	//printf("read_init ok\n");
	if(fp!=NULL){
		if(fscanf(fp,"%d %d\n%d\n",&(p_cfg->x),&(p_cfg->y),&(p_cfg->it))!=3){//retrieve simulation size and step number. Check if there are no errors.
			return false;
		}
		else{
			int nb=0;
			char *line=malloc(sizeof(char)*(((p_cfg->x))+1));//line buffer, were going to work line by line here.
			//printf("malloc ok\n");
			while(fscanf(fp,"%s",line)!=EOF){//scan line
				nb+=1;
				if(strlen(line)<(p_cfg->x)){//chek if line length is correct.
					print_x_warning=true;
				}
				int i = 0;
				while(line[i]!='\0'){
					if(line[i]=='o'){//found a live cell, add it to the population.
						//printf("adding cell...\n");
						create_cell(p_pop,i,((p_cfg->y))-nb,p_cfg);
						//printf("cell added");
					}
					i++;
				}
			}
			free(line);
			if(nb!=(p_cfg->y)){//print warnings, these are not fatal errors, the simulation may not look like what the user expects.
				printf("Warning: The number of lines read and the the height of the simulation\ngiven by the input file do not match!\n");
			}
			if(print_x_warning){
				printf("Warning: One or more lines read are shorter than the width of the simulation given in the data file!\n");
			}
		}
		fclose(fp);
		return true;
	}
	else{
		return false;
	}
}

void default_config(config *p_cfg){
	p_cfg->x=50;
	p_cfg->y=50;
	p_cfg->pix=4;
	p_cfg->it=50;
	p_cfg->trans=0;
	p_cfg->pausable=1;
	p_cfg->dy_r=80;
	p_cfg->dy_g=80;
	p_cfg->dy_b=80;
	p_cfg->nb_r=120;
	p_cfg->nb_g=120;
	p_cfg->nb_b=120;
	p_cfg->al_r=255;
	p_cfg->al_g=255;
	p_cfg->al_b=255;
	p_cfg->delay=100;
}

bool load_config(config *p_cfg){
	FILE *fp=NULL;
	fp=fopen("data/config.txt","r");
	if(fp!=NULL){
		if(fscanf(fp,"width=%d\n",&(p_cfg->x))!=1){
			return false;
		}
		if(fscanf(fp,"height=%d\n",&(p_cfg->y))!=1){
			return false;
		}
		if(fscanf(fp,"cell size=%d\n",&(p_cfg->pix))!=1){
			return false;
		}
		if(fscanf(fp,"iterations=%d\n",&(p_cfg->it))!=1){
			return false;
		}
		if(fscanf(fp,"transitions=%d\n",&(p_cfg->trans))!=1){
			return false;
		}
		if(fscanf(fp,"pausable=%d\n",&(p_cfg->pausable))!=1){
			return false;
		}
		if(fscanf(fp,"dying red level=%d\n",&(p_cfg->dy_r))!=1){
			return false;
		}
		if(fscanf(fp,"dying green level=%d\n",&(p_cfg->dy_g))!=1){
			return false;
		}
		if(fscanf(fp,"dying blue level=%d\n",&(p_cfg->dy_b))!=1){
			return false;
		}
		if(fscanf(fp,"newborn red level=%d\n",&(p_cfg->nb_r))!=1){
			return false;
		}
		if(fscanf(fp,"newborn green level=%d\n",&(p_cfg->nb_g))!=1){
			return false;
		}
		if(fscanf(fp,"newborn blue level=%d\n",&(p_cfg->nb_b))!=1){
			return false;
		}
		if(fscanf(fp,"alive red level=%d\n",&(p_cfg->al_r))!=1){
			return false;
		}
		if(fscanf(fp,"alive green level=%d\n",&(p_cfg->al_g))!=1){
			return false;
		}
		if(fscanf(fp,"alive blue level=%d\n",&(p_cfg->al_b))!=1){
			return false;
		}
		if(fscanf(fp,"interframe delay=%d\n",&(p_cfg->delay))!=1){
			return false;
		}
		return true;
	}
	else{
		return false;
	}
}
