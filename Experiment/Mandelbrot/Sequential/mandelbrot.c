#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

#define LOL 2000
#define HEIGHT LOL
#define WIDTH LOL
#define MAX 1500

static unsigned int* map;

void mandelbrot() {
	
	int i, j;
	double x_min = -1.6f;
	double x_max = 1.6f;
	double y_min = -1.6f;
	double y_max = 1.6f;

	for (i = 0; i < HEIGHT; i++) {
		for (j = 0; j < WIDTH; j++) {
			double b = x_min + j * (x_max - x_min) / WIDTH;
			double a = y_min + i * (y_max - y_min) / HEIGHT;

			double sx = 0.0f;
			double sy = 0.0f;
			int iterations = 0;
			
			while (sx + sy <= 64.0f) {
				float xn = sx * sx - sy * sy + b;
				float yn = 2 * sx * sy + a;
				sx = xn;
				sy = yn;
				iterations++;
				if (iterations == MAX)	{
					break;
				}
			}

			if (iterations == MAX)	{
				map[j + i * WIDTH] = 0;
			}
			else {
				map[j + i * WIDTH] = 0xffffff;
			}
		}
	}
}

int main() {
	removeResultFile();
	int l;
   	for(l = 0; l < 10; l++) {
        	map = malloc(WIDTH * HEIGHT * sizeof(int));
        	struct timespec brotStart, brotEnd;
       	 	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &brotStart);
		mandelbrot();	
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &brotEnd);
        	printTimespec(brotStart, brotEnd, "mandelbrot set");
        	logResult(brotStart, brotEnd);
		free(map);
	}
}
