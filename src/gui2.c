#include "gui2.h"

int closable_delay(unsigned int delay, unsigned int start,SDL_Event *event,population *p_pop,int paused,config *p_cfg,SDL_Renderer *renderer){  //not the most elegant way of doing this, 
	if(start==0){															  // consumes a lot of cpu, but does the job...
		start=SDL_GetTicks();												  //This function acts as a delay, and as the event handler for the user input.
	}
	int pause = paused;
	unsigned int current=SDL_GetTicks();
	while(current<start+delay ||pause){
		if(SDL_PollEvent(event)){
			switch(event->type){
				case SDL_WINDOWEVENT:
					if((event->window).event==SDL_WINDOWEVENT_CLOSE){
						SDL_Quit();
						printf("\n\nquitting...\n");
						return -1;
					}
					break;
				case SDL_KEYDOWN:
					if((event->key).keysym.sym==SDLK_SPACE){
						//printf("keyspace!!\n");
						if(p_cfg->pausable){
							//printf("pausable!\n");
							pause=(pause?0:1);
						}
						else{
							SDL_PushEvent(event);
						}
					}
					break;
					case SDL_MOUSEBUTTONDOWN:
					if(event->button.button==SDL_BUTTON_LEFT){
						//printf("(%d,%d)\n",(event->button.x),(event->button.y));
						toggle_cell(p_pop,(event->button.x)/(p_cfg->pix),(p_cfg->y)-1-((event->button.y)/(p_cfg->pix)),p_cfg);
						all_alive(p_pop);
						render_pop(renderer,p_pop,p_cfg);
					}
					break;
				default:
					break;
			}
		}
		SDL_Delay(1);
		current=SDL_GetTicks();
	}
	return 0;
}
int init_frame(SDL_Renderer **renderer, SDL_Window **window,config *p_cfg){
	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		printf("error while initializing gui...\n");
		return -1;
	}
	SDL_CreateWindowAndRenderer((p_cfg->pix)*(p_cfg->x),(p_cfg->pix)*(p_cfg->y),0,window,renderer);
	return 0;
}

void render_pop(SDL_Renderer *renderer,population *p_pop, config *p_cfg){
	SDL_Rect rect;
	SDL_SetRenderDrawColor(renderer,0,0,0,255);
	SDL_RenderClear(renderer);
	rect.h=p_cfg->pix;
	rect.w=p_cfg->pix;
	cell *current=*p_pop;
	while(current !=NULL){
		if(current->stat==ALIVE){
			SDL_SetRenderDrawColor(renderer,p_cfg->al_r,p_cfg->al_g,p_cfg->al_b,255);
		}
		else if(current->stat==NEWBORN){
			SDL_SetRenderDrawColor(renderer,p_cfg->nb_r,p_cfg->nb_g,p_cfg->nb_b,255);
		}
		else{
			SDL_SetRenderDrawColor(renderer,p_cfg->dy_r,p_cfg->dy_g,p_cfg->dy_b,255);
		}
		rect.x=(p_cfg->pix)*current->x;
		rect.y=(p_cfg->pix)*((p_cfg->y)-(current->y)-1);
		SDL_RenderFillRect(renderer,&rect);
		current=current->next;
	}
	SDL_RenderPresent(renderer);
}


void render_animation(population *p_pop,config *p_cfg){
	SDL_Renderer *renderer;
	SDL_Window *window;
	SDL_Event event;
	unsigned int timer=SDL_GetTicks();
	printf("got here so far...");
	if(init_frame(&renderer, &window,p_cfg)!=0){
		SDL_Quit();
		printf("Error while initializing display...\n");
		return;
	}
	int it=0;
	render_pop(renderer,p_pop,p_cfg);
	if(closable_delay(p_cfg->delay,timer,&event,p_pop,1,p_cfg,renderer)!=0){
				return;
			}
	if(p_cfg->trans){
		while(p_cfg->it<0||(p_cfg->it)-it>=0){//if nb_it<0 the anmation goes on until stoped by the user...
			timer=SDL_GetTicks();
			all_alive(p_pop);
			kill_dying(p_pop);
			if(closable_delay(p_cfg->delay,timer,&event,p_pop,0,p_cfg,renderer)!=0){
				return;
			}
			render_pop(renderer,p_pop,p_cfg);
			p_cfg->pausable=1;
			timer=SDL_GetTicks();
			age(p_pop);
			renew(p_pop,p_cfg);
			if(closable_delay(p_cfg->delay,timer,&event,p_pop,0,p_cfg,renderer)!=0){//10fps, if window closed we must make sure that no frames are drawn.
				return;
			}
			render_pop(renderer,p_pop,p_cfg);
			p_cfg->pausable=0;
			it++;
		}
	}
	else{
		while(p_cfg->it<0||(p_cfg->it)-it>=0){//if nb_it<0 the anmation goes on until stoped by the user...
			all_alive(p_pop);
			kill_dying(p_pop);
			if(closable_delay(p_cfg->delay,timer,&event,p_pop,0,p_cfg,renderer)!=0){
				return;
			}
			render_pop(renderer,p_pop,p_cfg);
			timer=SDL_GetTicks();
			age(p_pop);
			renew(p_pop,p_cfg);
			it++;
		}
		
	}
	//closable_delay(500);
	SDL_Quit();
	return;
}
