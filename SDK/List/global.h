#ifndef GLOBAL
#define GLOBAL

#include "../LIB/STDtypes.h"

typedef union
{
	u8 OP;
	s32 Term;
}elementtype;

#define MAXELEMENT 10

typedef elementtype listentry;
#define MAXLIST MAXELEMENT 

#endif

