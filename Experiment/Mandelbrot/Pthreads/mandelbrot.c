#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

#define HEIGHT 4096
#define WIDTH 4096
#define MAX 1500
#define MAX_THREADS 4

typedef struct {
	int x;
	int y;
	int size;
} Args;

static unsigned int* map;

pthread_t tid[MAX_THREADS];

void mandelbrot(int x, int y, int size) {
	
	int i, j, width = x + size, height = y + size;
	double x_min = -1.6f;
	double x_max = 1.6f;
	double y_min = -1.6f;
	double y_max = 1.6f;

	for (i = y; i < height; i++) {
		for (j = x; j < width; j++) {
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

void * worker(void * args) {
	Args * arg = args;
	mandelbrot(arg->x, arg->y, arg->size);
	free(arg);
}

Args * create_args(int x, int y, int size) {
	Args * args = malloc(sizeof(Args));
	args->size = size;
	args->x = x;
	args->y = y;
	return args;
}

int main() {
	int l;
	for(l = 0; l < 10; l++) {
		map = malloc(WIDTH * HEIGHT * sizeof(int));
		struct timespec brotStart, brotEnd;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &brotStart);
		int i, counter = 0, x = 0, y = 0, size = HEIGHT / MAX_THREADS;
		for(i = 0; i < MAX_THREADS*4; i++) {
			pthread_create(&tid[counter++], NULL, worker, create_args(x,y, size));
			
			if(x == (WIDTH-size)) {
				x = 0;
				y += size;
			}
			else {
				x += size;
			}

			if(counter == MAX_THREADS) {
				counter = 0;
				int j;
				for(j = 0; j < MAX_THREADS; j++) {
					pthread_join(tid[j], NULL);
				}
			}
		}
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &brotEnd);
        printTimespec(brotStart, brotEnd, "mandelbrot set");
        logResult(brotStart, brotEnd);
		//drawMandel("frac.tga", WIDTH, HEIGHT, map);
		free(map);
	}
}