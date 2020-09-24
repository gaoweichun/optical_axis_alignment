/**
* Copyright (c) 2016 rxi
*
* This library is free software; you can redistribute it and/or modify it
* under the terms of the MIT license. See `ini.c` for details.
*/

#ifndef INI_H
#define INI_H

#define INI_VERSION "0.1.1"

typedef struct ini_t ini_t;

typedef struct _HOUGH {
	int minRadius;
	int maxRadius;
	double param1;
	double param2;
	double minDist;
	int xdistance;
}HOUGH;

typedef struct _MTF {
	int xdistance;
	int ydistance;
	int width;
	int high;
}MTF;


void readConfig(HOUGH * h, MTF * m);

ini_t*      ini_load(const char *filename);
void        ini_free(ini_t *ini);
const char* ini_get(ini_t *ini, const char *section, const char *key);
int         ini_sget(ini_t *ini, const char *section, const char *key, const char *scanfmt, void *dst);

#endif