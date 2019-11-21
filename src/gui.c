#include "gui.h"
#include "cell.h"
#include "load.h"

int closable_delay(unsigned int delay, unsigned int start,SDL_Event *event, population *p_pop, bool paused, config *p_cfg,SDL_Surface *screen){  //not the most elegant way of doing this, 
	if(start==0){																																 // consumes a lot of cpu, but does the job...
		start=SDL_GetTicks();																													 //This function acts as a delay, and as the event handler for the user input.
	}
	bool pause=paused;
	//fprintf(stdout,"start time: %d\n",start);
	unsigned int current=SDL_GetTicks();
	while(current<start+delay||pause){
		//fprintf(stdout,"loop: %d\n",current);
		if(SDL_PollEvent(event)){
			switch(event->type){
				case SDL_QUIT:
					SDL_FreeSurface(screen);
					SDL_Quit();
					printf("\n\nquitting...\n");
					return -1;
				case SDL_KEYDOWN:
					if((event->key).keysym.sym==SDLK_SPACE){
						if(p_cfg->pausable){
							pause=(pause?0:1);
						}
						else{
							SDL_PushEvent(event);
						}
					}
					break;
				case SDL_MOUSEBUTTONDOWN:
					if(event->button.button==SDL_BUTTON_LEFT){
						toggle_cell(p_pop,(event->button.x)/(p_cfg->pix),(p_cfg->y)-1-((event->button.y)/(p_cfg->pix)),p_cfg);
						all_alive(p_pop);
						render_pop(screen,p_pop,p_cfg);
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

int init_frame(SDL_Surface **screen,config *p_cfg){
	if(SDL_Init(SDL_INIT_VIDEO)!=0){
		fprintf(stdout,"error while initializing gui...\n");
		return -1;
	}
	*screen = SDL_SetVideoMode((p_cfg->pix)*(p_cfg->x), (p_cfg->pix)*(p_cfg->y), 32, SDL_SWSURFACE|SDL_ANYFORMAT);
    if (*screen==NULL) {
        fprintf(stdout,"Error, couldn't set video mode\n");
        return -1;
    }
    SDL_WM_SetCaption("animation!", NULL);
    return 0;
}


void render_pop(SDL_Surface *screen, population *p_pop,config *p_cfg){
	//fprintf(stdout,"declaring rect\n");
	SDL_Rect rect;
	//fprintf(stdout,"no fill yet\n");
	SDL_FillRect(screen,NULL,SDL_MapRGB(screen->format,00,00,00));
	//fprintf(stdout,"screen filled\n");
	rect.h=p_cfg->pix;
	rect.w=p_cfg->pix;
	cell *current=*p_pop;
	while(current !=NULL){
		rect.x=(p_cfg->pix)*(current->x);
		rect.y=(p_cfg->pix)*((p_cfg->y)-(current->y)-1);
		if(current->stat==ALIVE){
			SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,p_cfg->al_r,p_cfg->al_g,p_cfg->al_b));
		}
		else if(current->stat==NEWBORN){
			SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,p_cfg->nb_r,p_cfg->nb_g,p_cfg->nb_b));
		}
		else{
			SDL_FillRect(screen,&rect,SDL_MapRGB(screen->format,p_cfg->dy_r,p_cfg->dy_g,p_cfg->dy_b));
		}
		current=current->next;
	}
	//fprintf(stdout,"update!\n");
	SDL_UpdateRect(screen, 0, 0, (p_cfg->pix)*(p_cfg->x), (p_cfg->pix)*(p_cfg->y));
}

void render_animation(population *p_pop,config *p_cfg){
	SDL_Surface *screen=NULL;
	SDL_Event event;
	if(init_frame(&screen,p_cfg)!=0){
		SDL_Quit();
		fprintf(stdout,"Error while initializing display...\n");
		return;
	}
	unsigned int timer=SDL_GetTicks();
	//fprintf(stdout,"all good to go!\n");
	int it=0;
	render_pop(screen,p_pop,p_cfg);
	if(closable_delay(p_cfg->delay,timer,&event,p_pop,true,p_cfg,screen)!=0){
		return;
	}
	if(p_cfg->trans){
		while((p_cfg->it)<0||(p_cfg->it)-it>=0){//if nb_it<0 the anmation goes on until stoped by the user...
			timer=SDL_GetTicks();
			all_alive(p_pop);
			kill_dying(p_pop);
			render_pop(screen,p_pop,p_cfg);
			p_cfg->pausable=1;
			if(closable_delay(p_cfg->delay,timer,&event,p_pop,false,p_cfg,screen)!=0){
				return;
			}
			timer=SDL_GetTicks();
			age(p_pop);
			renew(p_pop,p_cfg);
			render_pop(screen,p_pop,p_cfg);
			p_cfg->pausable=0;
			if(closable_delay(p_cfg->delay,timer,&event,p_pop,false,p_cfg,screen)!=0){//10fps, if window closed we must make sure that no frames are drawn.
				return;
			}
			it++;
		}
	}
	else{
		while((p_cfg->it)<0||(p_cfg->it)-it>=0){//if nb_it<0 the anmation goes on until stoped by the user...
			all_alive(p_pop);
			kill_dying(p_pop);
			//fprintf(stdout,"entering delay\n");
			render_pop(screen,p_pop,p_cfg);
			if(closable_delay(p_cfg->delay,timer,&event,p_pop,false,p_cfg,screen)!=0){
				return;
			}
			//fprintf(stdout,"delayfinished!\n");
			//fprintf(stdout,"draw!\n");
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
