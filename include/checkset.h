/*********************************************************************
Functions to check and set command line argument values and files.
This is part of GNU Astronomy Utilities (AstrUtils) package.

Copyright (C) 2013-2014 Mohammad Akhlaghi
Tohoku University Astronomical Institute, Sendai, Japan.
http://astr.tohoku.ac.jp/~akhlaghi/

AstrUtils is free software: you can redistribute it and/or modify it
under the terms of the GNU General Public License as published by the
Free Software Foundation, either version 3 of the License, or (at your
option) any later version.

AstrUtils is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License
along with AstrUtils. If not, see <http://www.gnu.org/licenses/>.
**********************************************************************/
#ifndef CHECKSET_H
#define CHECKSET_H


#include <fitsio.h>


/**************************************************************/
/********* Read arguments and check their values **************/
/**************************************************************/
void
intzeroorone(char *optarg, int *var, char *lo, char so, char* spack,
	     char *filename, size_t lineno);

void
intelzero(char *optarg, int *var, char *lo, char so, char *spack,
	  char *filename, size_t lineno);

void
intlzero(char *optarg, int *var, char *lo, char so, char *spack,
	 char *filename, size_t lineno);

void
int4or8(char *optarg, int *var, char *lo, char so, char *spack,
	 char *filename, size_t lineno);

void
anylong(char *optarg, long *var, char *lo, char so, char *spack,
	char *filename, size_t lineno);

void
sizetelzero(char *optarg, size_t *var, char *lo, char so, char *spack,
	 char *filename, size_t lineno);

void
sizetlzero(char *optarg, size_t *var, char *lo, char so, char *spack,
	 char *filename, size_t lineno);

void
floatl0(char *optarg, float *var, char *lo, char so, char *spack,
	 char *filename, size_t lineno);

void
floatl0s1(char *optarg, float *var, char *lo, char so, char *spack,
	 char *filename, size_t lineno);

void
anyfloat(char *optarg, float *var, char *lo, char so, char *spack,
	 char *filename, size_t lineno);

void
doublel0(char *optarg, double *var, char *lo, char so, char *spack,
	 char *filename, size_t lineno);

void
anydouble(char *optarg, double *var, char *lo, char so, char *spack,
	  char *filename, size_t lineno);










/**************************************************************/
/**********          My String functions:          ************/
/**************************************************************/
int
stringhasspace(char *in);

char *
malloccat(char *inname, char *toappend);










/**************************************************************/
/********** Set file names and check if they exist ************/
/**************************************************************/
void
checkfile(char *filename);

void
checkremovefile(char *filename, int dontdelete);

int
nameisafile(char *name, int dontdelete);

void
automaticoutput(char *inname, char *postfix, int removedirinfo,
		int dontdelete, char **outname);

void
checkdirwriteaddslash(char **dirname);

#endif
