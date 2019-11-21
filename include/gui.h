/**
 * 
 * @file gui.h
 * @author Léo Creuse
 * 
 * @brief This file defines the api to show the animation at execution time. It uses the SDL 1.2 library, so it should be installed on the user's system.
 * 
 * This enables the user to watch the evolution of the cells directly, without having to 
 * wait for the generation of the cells and the compilation of the gif. It also looks nicer
 * since the cells are more than one pixel wide...\n\n
 * The supported commands at the time are:\n
 * 	-pressing space to pause the animation (assuming pausing is not blocked in the configuration)\n
 * 	-left-clicking anywhere on the screen to toggle the cell under it.\n
 *  -closing the window.\n\n
 * The api is made of:\n
 * 	-A function to initialize the graphical interface.\n
 *  -A function to update the screen according to the state of the population\n
 *  -A function to show the whole animation.\n\n

 */

#ifndef GUI_H
#define GUI_H


#include <SDL/SDL.h>


#include "cell.h"
#include "evolution.h"
#include <stdbool.h>
#include <stdio.h>

/**
 * @brief initializes the SDL library.
 * 
 * @param renderer A pointer to a pointer to a SDL_Renderer, which will be used to render the frames.
 * @param window A pointer to a pointer to a SDL_Window, in which the animation will be played.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 * 
 * 
 */

int init_frame(SDL_Surface **screen, config *p_cfg);

/**
 * @brief Draws a single frame on the window.
 * 
 * @param renderer  A pointer to a SDL_Renderer which will be rendered the frame.
 * @param p_pop A pointer to the population to be displayed.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 * 
 */

void render_pop(SDL_Surface *screen, population *p_pop,config *p_cfg);


/**
 * @brief Renders the full animation.
 * 
 * @param p_pop A pointer to the population containing the inintial state.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 */
void render_animation(population *p_pop,config *p_cfg);
#endif
