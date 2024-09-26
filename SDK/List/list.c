#include "../List/list.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef LIMITED_MEMORY

typedef struct listnode 
{
	listentry entry;
	struct listnode *next;
}listnode;

struct list
{
	listnode *head;
	int size;
};

void createlist (plist *ppl)
{
	*ppl=(struct list *)malloc(sizeof(struct list));
	(*ppl)->head=NULL;
	(*ppl)->size=0;
}
void insertlist (int p,listentry e,plist pl)
{
	listnode *pn,*qn;
	int i;
	pn=(listnode*)malloc(sizeof(listnode));
	pn->entry=e;
	pn->next=NULL;
	if (p==0)
	{
		pn->next=pl->head;
	    pl->head=pn;
	}
	else
	{
		for (qn=pl->head,i=0;i<p-1;i++)
		{
			qn=qn->next;
		}
		pn->next=qn->next;
		qn->next=pn;
	}
	pl->size++;
}
int listfull (plist pl)
{
	return 0;
}
void deletlist (int p,listentry *pe,plist pl)
{
	int i;
	listnode *pn,*qn;
	if(p==0)
	{
		*pe=pl->head->entry;
	    pn=pl->head->next;
		free(pl->head);
	    pl->head=pn;
	}
	else
	{
		for (qn=pl->head,i=0;i<p-1;i++)
		{
			qn=qn->next;
		}
		*pe=qn->next->entry;
		pn=qn->next->next;
		free(qn->next);
		qn->next=pn;
	}
	pl->size--;
}
int listempty (plist pl)
{
	if (pl->size==0) return 1;
	else return 0;
}
int listsize (plist pl)
{
	return pl->size;
}
void retrievelist (int p,listentry *pe,plist pl)
{
	int i;
	listnode *qn;
	for (qn=pl->head,i=0;i<p;i++)
	{
		qn=qn->next;
	}
	*pe=qn->entry;
}
void replacelist (int p,listentry e,plist pl)
{
	int i;
	listnode *qn;
	for (qn=pl->head,i=0;i<p;i++)
	{
		qn=qn->next;
	}
	qn->entry=e;
}
void destroylist (plist *ppl)
{
	listnode *pn;
	while ((*ppl)->head)
	{
		pn=(*ppl)->head->next;
		free((*ppl)->head);
		(*ppl)->head=pn;
	}
	(*ppl)->size=0;
}
void traverselist (plist pl,void (*pf) (listentry e))
{
	listnode *pn=pl->head;
	while (pn)
	{
		pf(pn->entry);
		pn=pn->next;
	}
}

#else
	
struct list
{
	int size;
	listentry entry[MAXLIST];
};

void createlist (plist *ppl)
{
	*ppl=(struct list *)malloc(sizeof(struct list));
	(*ppl)->size=0;
}
void insertlist (int p,listentry e,plist pl)
{
	int i;
	for (i=pl->size-1;i>=p;i--)
	{
		pl->entry[i+1]=pl->entry[i];
	}
	pl->entry[p]=e;
	pl->size++;
}
int listfull (plist pl)
{
	if (pl->size==MAXLIST) return 1;
	else return 0;
}
void deletlist (int p,listentry *pe,plist pl)
{
	int i;
	*pe=pl->entry[p];
	for (i=p+1;i<=pl->size-1;i++)
	{
		pl->entry[i-1]=pl->entry[i];
	}
	pl->size--;
}
int listempty (plist pl)
{
	if (pl->size==0) return 1;
	else return 0;
}
int listsize (plist pl)
{
	return pl->size;
}
void retrievelist (int p,listentry *pe,plist pl)
{
	*pe=pl->entry[p];
}
void replacelist (int p,listentry e,plist pl)
{
	pl->entry[p]=e;
}
void destroylist (plist *ppl)
{
	(*ppl)->size=0;
}
void traverselist (plist pl,void (*pf) (listentry e))
{
	for (int i=0;i<pl->size;i++)
		pf(pl->entry[i]);
}

#endif