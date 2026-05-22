#include "pico/stdlib.h"

#include "libraries/pico_graphics/pico_graphics.hpp"
#include "libraries/interstate75/interstate75.hpp"

using namespace pimoroni;


// Display size in pixels, note: the i75W RP2350 kit includes two 128x64
// pixel displays which form a chain that's 256x64 pixels in side.
Hub75 hub75(256, 64, nullptr, PANEL_GENERIC, false);

// Our PicoGraphics surface. If we want a square output then use 128x128
// as the width and height, which Hub75 will automatically remap to 256x64.
PicoGraphics_PenRGB888 graphics(256, 64, nullptr);


const int width = 256;
const int height = 64;


// Interrupt callback required function
void __isr dma_complete() {
  hub75.dma_complete();
}


int main() {
  stdio_init_all();

  std::string msg="Hello World";
  float scale = 2.0;

  // Start hub75 driver
  hub75.start(dma_complete);

  graphics.set_font("sans");
  int32_t txtWidth = graphics.measure_text(
		  msg,
		 scale
		  ) * -1;
  for (;;){
	  for (int i=width; i > txtWidth; i--){
		  graphics.set_pen(0, 0, 0);
			graphics.clear();

			graphics.set_pen(10, 10, 180);
			graphics.text(
					msg,
					Point(i, 30),
					0xFFFF,
					scale
					);

			hub75.update(&graphics);
			sleep_ms(10);
	  }
  }

  return 0;
}
