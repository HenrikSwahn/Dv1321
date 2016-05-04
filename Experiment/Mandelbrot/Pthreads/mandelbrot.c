#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>

#define L 1300.0
#define HEIGHT L
#define WIDTH L
#define MAX 1500
#define MAX_THREADS 8
#define T HEIGHT/MAX_THREADS

typedef struct {
	int x;
	int y;
	double h;
	double w;
} Args;

static unsigned int* map;

pthread_t tid[MAX_THREADS];

void mandelbrot(int x, int y, double w, double h) {
	
	int i, j;
	double width = x + w, height = y + h;
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
				map[(int)(j + i * WIDTH)] = 0;
			}
			else {
				map[(int)(j + i * WIDTH)] = 0xffffff;
			}
		}
	}
}

void * worker(void * args) {
	Args * arg = args;
	mandelbrot(arg->x, arg->y, arg->w, arg->h);
	free(arg);
}

Args * create_args(int x, int y, double w, double h) {
	Args * args = malloc(sizeof(Args));
	args->w = w;
	args->h = h;
	args->x = x;
	args->y = y;
	return args;
}

int main() {
	int l;
	//for(l = 0; l < 10; l++) {
		map = malloc(WIDTH * HEIGHT * sizeof(int));
		struct timespec brotStart, brotEnd;
        clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &brotStart);
		int i, counter = 0;
		double x = 0, y = 0;
		for(i = 0.0; i < MAX_THREADS*2; i++) {
			pthread_create(&tid[counter++], NULL, worker, create_args(x,y, T, HEIGHT/2));
			if(counter == MAX_THREADS) {
				counter = 0;
				x = 0;
				y += HEIGHT/2;
				int j;
				for(j = 0; j < MAX_THREADS; j++) {
					pthread_join(tid[j], NULL);
				}
			}
			else {
				x += T;
			}
		}
		clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &brotEnd);
        printTimespec(brotStart, brotEnd, "mandelbrot set");
        logResult(brotStart, brotEnd);
		drawMandel("frac.tga", (int)WIDTH, (int)HEIGHT, map);
		free(map);
	//}
}