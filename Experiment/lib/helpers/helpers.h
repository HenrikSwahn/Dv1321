#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct timespec diff(struct timespec s, struct timespec e);
void printTimespec(struct timespec s, struct timespec e, char* message);
void logResult(struct timespec s, struct timespec e);
void removeResultFile();
void removeOrderFile();
void logOrder(int[], int);
#endif