#include "generate-image.h"


void single_frame(population *p_pop, config *p_cfg, int frame_number){
	FILE *frame=NULL;
	char name[20];
	sprintf(name,"out/frame%03d.ppm",frame_number);
	frame=fopen(name,"w");
	if(frame!=NULL){
		fprintf(frame,"P3\n%04d %04d\n255\n",(p_cfg->x),(p_cfg->y));
		for(int i=0;i<(p_cfg->x)*(p_cfg->y);i++){
			fprintf(frame,"000 000 000 ");
		}
		cell *current=*p_pop;
		while(current !=NULL){
			fseek(frame, 17+12*(((p_cfg->y)-1-current->y)*(p_cfg->x)+current->x),SEEK_SET);
			if(current->stat==ALIVE){
				fprintf(frame,"%3d %3d %3d ",p_cfg->al_r,p_cfg->al_g,p_cfg->al_b);
			}
			else if(current->stat==NEWBORN){
				fprintf(frame,"%3d %3d %3d ",p_cfg->nb_r,p_cfg->nb_g,p_cfg->nb_b);
			}
			else{
				fprintf(frame,"%3d %3d %3d ",p_cfg->dy_r,p_cfg->dy_g,p_cfg->dy_b);
			}
			current=current->next;
		}
		fclose(frame);
	}
}

void all_frames(population *p_pop, config *p_cfg){
		if(p_cfg->trans){
			for(int i=0; i<p_cfg->it;i++){
				single_frame(p_pop,p_cfg,2*i);
				all_alive(p_pop);
				kill_dying(p_pop);
				single_frame(p_pop,p_cfg,2*i+1);
				age(p_pop);
				renew(p_pop,p_cfg);
			}
		}
		else{
			for(int i=0; i<p_cfg->it;i++){
				all_alive(p_pop);
				kill_dying(p_pop);
				single_frame(p_pop,p_cfg,i); //in order not to have dying or newborn cells showing.
				age(p_pop);
				renew(p_pop,p_cfg);
		}
	}
}
