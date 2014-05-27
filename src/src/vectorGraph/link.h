#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


#ifndef __LINK_H__
#define __LINK_H__

struct lelement;

struct link;

void lnk__empty(struct link *e);

int lnk__is_end_mark(struct lelement *e);

void lnk__add_head(struct link *l, struct lelement *e);

struct lelement *lnk__remove_head(struct link *l);

void lnk__add_after(struct lelement *e, struct lelement *f);

struct lelement *lnk__remove_after(struct lelement *e);

void lnk__add_tail(struct link *l, struct lelement *e);

struct lelement *lnk__remove_tail(struct link *l);

#endif
