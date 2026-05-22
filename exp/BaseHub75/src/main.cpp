/*
 * main.cpp
 *
 *  Created on: 21 May 2026
 *      Author: jondurrant
 */


#include "pico/stdlib.h"

#include "libraries/interstate75/interstate75.hpp"

using namespace pimoroni;


// Display size in pixels, note: the i75W RP2350 kit includes two 128x64
// pixel displays which form a chain that's 256x64 pixels in side.
Hub75 hub75(256, 64, nullptr, PANEL_GENERIC, false);


// Interrupt callback required function
void __isr dma_complete() {
  hub75.dma_complete();
}


int main() {
  stdio_init_all();

  uint width = 256;
  uint height = 64;

  // Start hub75 driver
  hub75.start(dma_complete);


  while(true) {

	  int r = 10;
	  int g = 100;
	  int b = 10;

    for(int y = 0; y < height; y++) {
    	g = (y%3)*30;
	  for(int x = 0; x < width; x++) {
		  r = x;

		  hub75.set_pixel( x,  y,  r,  g,  b);
      }
	  b +=10;
    }

    //hub75.display_update();

    sleep_ms(10);
  }

  return 0;
}
