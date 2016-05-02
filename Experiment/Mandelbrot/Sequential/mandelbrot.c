#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define HEIGHT 1024
#define WIDTH 1024
#define SIZE 1024
#define MAX 30

typedef struct {
	unsigned x;
	unsigned y;
	unsigned n;
} Point;

static Point * points;
static unsigned counter;

Point createPoint(unsigned y, unsigned x, unsigned n) {
	Point point;
	point.x = x;
	point.y = y;
	point.n = n;
	return point;	
}

void draw() {
	
}

void mandelbrot() {

	double minRe = -2.0;
	double maxRe = 1.0;
	double minLm = -1.2;
	double maxLm = minLm + (maxRe - minRe) * HEIGHT / WIDTH;
	double reFactor = (maxRe - minRe) / (WIDTH-1);
	double lmFactor = (maxLm - minLm) / (HEIGHT-1);
	
	unsigned y;
	for(y = 0; y < HEIGHT; y++) {
		double h = minLm - y * lmFactor;
		unsigned x;
		for(x = 0; x < WIDTH; x++) {
			double w = minRe + x * reFactor;
			double zw = w, zh = h, inside = 1;
			unsigned n;
			for(n = 0; n < MAX; n++) {
				double zw2 = zw * zw, zh2 = zh * zh;
				if(((zw2 + zh2) > 4)) {
					inside = 0;
					break;
				}
				zh = 2 * zw * zh + h;
				zw = zw2 - zh2 + w;
			}
			if(inside == 1) {
				points[counter++] = createPoint(y,x,n);		
			}
		}
	}	
}

int main() {
	points = malloc(SIZE * sizeof(Point));
	counter = 0;
	mandelbrot();
	draw();
	free(points);
}
