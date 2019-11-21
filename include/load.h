/**
* @file load.h
* 
* @brief This file defines a function to load a population from a data file.
* 
* 
*/

#ifndef LOAD_H
#define LOAD_H

#include "cell.h"
#include <stdio.h>
#include <stdbool.h>
/**
 * @brief Load population data from a txt file, with the rules given in Mr Garion's subject.
 * 
 * This function will also print some warnings to the console if there are non-fatal errors while retirieving data.
 * 
 * @param file  The path to the data file.
 * @param p_pop A pointer to the population in which the data should be stored. Note: the population should be NULL.
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 * 
 * @return This function will return \c true if the file was loaded without major errors, and \c false otherwise.
 * 
 */
bool load_init(const char *file, population *p_pop, config *p_cfg);


/**
 * @brief This functions initialize the configuration structure to a default config.
 * 
 * The default config is as follows:
 * x=50;
 * y=50;
 * pix=4;
 * it=50;
 * trans=0;
 * pausable=1;
 * dy_r=80;
 * dy_g=80;
 * dy_b=80;
 * nb_r=120;
 * nb_g=120;
 * nb_b=120;
 * al_r=255;
 * al_g=255;
 * al_b=255;
 * delay=100;
 * 
 *  @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation. 
 */
void default_config(config *p_cfg);

/**
 * @brief loads a configuration from the file "data/config.txt" and stores it in p_cfg.
 * 
 * the configuration file must be in the directory ./data relative to the executable, and must be named config.txt, otherwise it will not work.
 * 
 * @param p_cfg p_cfg is a pointer to a configuration containing all the settings of the animation.
 */
bool load_config(config *p_cfg);

#endif
