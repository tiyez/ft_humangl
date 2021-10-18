
#ifndef Def_H
#define Def_H

#include <stdio.h>

#define Error(...) \
do {fprintf (stderr, "Error:%s:%d: ", __func__, __LINE__);\
	fprintf (stderr, __VA_ARGS__);\
	fprintf (stderr, "\n");\
} while (0)

#define Debug(...) \
do {fprintf (stderr, "Debug:%s:%d: ", __func__, __LINE__);\
	fprintf (stderr, __VA_ARGS__);\
	fprintf (stderr, "\n");\
} while (0)

#define GL(v) (v); if ((error = glGetError())) do { Error ("GL Error! %d", error); exit (1); } while (0)

#define Member_Offset(type, memb) (&(((type *)0)->memb))
#define Array_Count(arr) (sizeof (arr) / sizeof ((arr)[0]))


#endif /* Def_H */
