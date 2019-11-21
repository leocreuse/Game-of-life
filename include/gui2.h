/**
 *
 * @author Léo Creuse
 * 
 * @file gui2.h
 * 
 * @brief This file defines the api to show the animation at execution time. It uses the SDL 2.0 library, so it should be installed on the users system.
 * 
 * Note: this basicaly does the same thing than gui.h does, it simply uses the SDL2.0 library instead, which is more recent, and more versatile, but not installed on the CI's computer.\n
 * This enables the user to watch the evolution of the cells directly, without having to 
 * wait for the generation of the cells and the compilation of the gif. It also looks nicer
 * since the cells are more than one pixel wide...
 * 
 * The api is made of:\n
 * 	-A function to initialize the graphical interface.\n
 *  -A function to update the screen according to the state of the population\n
 *  -A function to show the whole animation.\n\n
 * 
 * 
 * 
 * 
 * 
 */

#ifndef GUI_H
#define GUI_H

#include <SDL2/SDL.h>


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
int init_frame(SDL_Renderer **renderer, SDL_Window **window,config *p_cfg);

/**
 * @brief Draws a single frame on the window.
 * 
 * @param renderer  A pointer to a SDL_Renderer which will be rendered the frame.
 * @param p_pop A pointer to the population to be displayed.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation. 
 * 
 */
void render_pop(SDL_Renderer *renderer, population *p_pop,config *p_cfg);

/**
 * @brief Renders the full animation.
 * 
 * @param p_pop A pointer to the population containing the nintial state.
 * @param x_size Defines the width of the simulation.
 * @param y_size  Defines the height of the simulation.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 */
void render_animation(population *p_pop,config *p_cfg);
#endif
