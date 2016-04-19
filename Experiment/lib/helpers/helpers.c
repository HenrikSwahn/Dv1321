#include "helpers.h"

struct timespec diff(struct timespec s, struct timespec e) {

	struct timespec t;

	if ((e.tv_nsec - s.tv_nsec) < 0) {
		t.tv_sec = e.tv_sec - s.tv_sec - 1;
		t.tv_nsec = 1000000000 + e.tv_nsec - s.tv_nsec;
	} 
	else {
		t.tv_sec = e.tv_sec - s.tv_sec;
		t.tv_nsec = e.tv_nsec - s.tv_nsec;
	}

	return t;
}

void printTimespec(struct timespec s, struct timespec e, char* message) {

	printf("Took: %ld:%ld seconds to %s\n", diff(s,e).tv_sec, diff(s,e).tv_nsec, message);
}

void logResult(struct timespec s, struct timespec e) {
	FILE *f;
	f = fopen("./result.txt", "a");
	fprintf(f,"%ld.%ld\n", diff(s,e).tv_sec, diff(s,e).tv_nsec);
	fclose(f);
}

void removeResultFile() {
	remove("./result.txt");
}

void removeOrderFile() {
	remove("./order.txt");
}

void logOrder(int arr[], int size) {
	FILE *f;
	f = fopen("./order.txt", "a");
	int i = 0;
	for(; i < size; i++) {
		fprintf(f,"%d\n", arr[i]);
	}
	fclose(f);
}