///////////////////////////////////////////////////////////////////////////// 
// INTEGRITY STATEMENT (v3)
//
// By signing your name and ID below you are stating that you have agreed
// to the online academic integrity statement:
// https://student.cs.uwaterloo.ca/~cs136/current/assignments/integrity.shtml
/////////////////////////////////////////////////////////////////////////////
// I received help from and/or collaborated with: 

// None
//  
// Name: Preeti Valunjkar
// login ID: pvalunjk
///////////////////////////////////////////////////////////////////////////// 

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

struct words {
  char *word;
  struct words *next;
};

struct triple_s {
  int len;
  struct words *front;
  struct words *back;
};

struct triple_s *sss_create(void) {
  struct triple_s *sss = malloc(sizeof(struct triple_s));
  sss->len = 0;
  sss->front = NULL;
  sss->back = NULL;
  return sss;
}

void sss_destroy(struct triple_s *sss) {
  assert(sss);
  struct words *currnode = sss->front;
  struct words *nextnode = NULL;
  while (currnode) {
    nextnode = currnode->next;
    free(currnode->word);
    free(currnode);
    currnode = nextnode;
  }
  free(sss);
}

void sss_add_follows(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  if (sss->front == NULL) {
    struct words *w = malloc(sizeof(struct words));
    w->word = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(w->word, s);
    w->next = NULL;
    sss->front = w;
    sss->back = w;
    ++sss->len;
  } else {
    assert(strcmp(sss->back->word, s) < 0);
    struct words *w = malloc(sizeof(struct words));
    w->word = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(w->word, s);
    w->next = NULL;
    sss->back->next = w;
    sss->back = w;
    ++sss->len;
  }
}

int sss_count(const struct triple_s *sss) {
  assert(sss);
  return sss->len;
}

const char *sss_get(const struct triple_s *sss, int idx) {
  assert(sss);
  assert(idx >= 0);
  assert(idx < sss_count(sss));
  struct words *w = sss->front;
  for (int i = 0; i < idx; ++i) {
    w = w->next;
  }
  return w->word;
}

int sss_search(const struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  int pos = 0;
  const struct words *w = sss->front;
  while (w) {
    if (strcmp(w->word, s) == 0) {
      return pos;
    }
    ++pos;
    w = w->next;
  }
  return -1;
}

void sss_remove(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  int pos = sss_search(sss, s);
  if (pos == 0) {
    struct words *w = sss->front;
    sss->front = sss->front->next; 
    free(w->word);
    free(w);
    --sss->len;
  } else if (pos != -1) {
    struct words *w = sss->front;
    for (int i = 0; i < pos - 1; ++i) {
      w = w->next;
    }
    struct words *del = w->next;
    w->next = w->next->next;
    free(del->word);
    free(del);
    --sss->len;
  }
}

// add_front(sss, s) adds the word s to the beginning of the 
// sss 
// requires: s does not exist in sss or sss is empty
// effects: may modify sss
// time: O(1)
static void add_front(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  if (sss->front) {
    assert(strcmp(s, sss_get(sss, 0)) < 0);
  }
  struct words *new = malloc(sizeof(struct words));
  new->word = malloc((strlen(s) + 1) * sizeof(char));
  strcpy(new->word, s);
  new->next = sss->front;
  sss->front = new;
  ++sss->len;
  if (sss->len == 1) {
    sss->back = new;
  }
}

void sss_add(struct triple_s *sss, const char *s) {
  assert(sss);
  assert(s);
  if ((sss->front == NULL) || (strcmp(sss->front->word, s) > 0)) {
    add_front(sss, s);
  } else if (sss_search(sss, s) == -1) {
    struct words *before = sss->front;
    while (before->next && strcmp(before->next->word, s) < 0) {
      before = before->next;
    }
    struct words *new = malloc(sizeof(struct words));
    new->word = malloc((strlen(s) + 1) * sizeof(char));
    strcpy(new->word, s);
    new->next = before->next;
    before->next = new;
    sss->back = sss->back->next;
    ++sss->len;
  } 
}

