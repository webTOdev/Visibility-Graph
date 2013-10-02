/*
 * Utility.h
 *
 *  Created on: Sep 20, 2013
 *      Author: nut
 */

#ifndef UTILITY_H_
#define UTILITY_H_

#include "CImg.h"// Include CImg library header.

const unsigned char WHITE[] = { 255, 255, 255 };
const unsigned char GREY[] = { 100, 100, 100 };
const unsigned char BLACK[] = { 0, 0, 0 };
const unsigned char RED[] = { 255, 0, 0 };
const unsigned char GREEN[] = { 0, 255, 0 };
const unsigned char BLUE[] = { 0, 0, 255};
const int screen_size = 800;
//const int screen_size = 400;
float scale=1.0;   // Scale the Lines , let the maximum coordinate is 9000 then scale = 9000/screen_size


#endif /* UTILITY_H_ */
