#ifndef LIST
#define LIST

//#define LIMITED_MEMORY      

#include "../List/global.h"

typedef struct list * plist;

void createlist (plist *ppl);
void insertlist (int p,listentry e,plist pl);
int listfull (plist pl);
void deletlist (int p,listentry *pe,plist pl);
int listempty (plist pl);
int listsize (plist pl);
void retrievelist (int p,listentry *pe,plist pl);
void replacelist (int p,listentry e,plist pl);
void destroylist (plist *ppl);
void traverselist (plist pl,void (*pf) (listentry e));

#endif