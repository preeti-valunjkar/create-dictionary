// This is a simple test client for the Triple S module

#include <assert.h>
#include <string.h>
#include "triple-s.h"

int main(void) {
  struct triple_s *sss = sss_create();
 
  sss_add(sss, "monkey");
  assert(sss_search(sss, "monkey") == 0);
  sss_add(sss, "monkey");
  sss_add(sss, "alligator");
  sss_add_follows(sss, "zebra");
  
  assert(sss_count(sss) == 3);
  
  sss_add(sss, "unicorn");
  sss_remove(sss, "unicorn");
  
  assert(sss_search(sss, "unicorn") == -1);
  assert(sss_search(sss, "monkey") == 1);
  assert(!strcmp(sss_get(sss, 1), "monkey"));
  
  assert(sss_search(sss, "zebra") == 2);
  assert(sss_search(sss, "alligator") == 0);
  sss_destroy(sss);
  
  struct triple_s *sss1 = sss_create();
  
  assert(sss_search(sss1, "litchi") == -1);
  sss_add_follows(sss1, "mango");
  sss_add(sss1, "banana");
  assert(sss_search(sss1, "banana") == 0);
  assert(sss_count(sss1) == 2);
  assert(!strcmp(sss_get(sss1, 1), "mango"));
  
  assert(sss_search(sss1, "apple") == -1);
  sss_remove(sss1, "banana");
  assert(!strcmp(sss_get(sss1, 0), "mango"));
  sss_remove(sss1, "mango");
  assert(sss_count(sss1) == 0);
  sss_destroy(sss1);
  
  struct triple_s *sss2 = sss_create();
  
  sss_add(sss2, "fall");
  sss_add_follows(sss2, "spring");
  sss_add_follows(sss2, "winter");
  sss_add(sss2, "summer");
  
  assert(sss_count(sss2) == 4);
  assert(sss_search(sss2, "winter") == 3);
  assert(!strcmp(sss_get(sss2, 1), "spring"));
  
  sss_add(sss2, "summer");
  assert(sss_count(sss2) == 4);
  
  sss_remove(sss2, "winter");
  assert(sss_search(sss2, "winter") == -1);
  assert(!strcmp(sss_get(sss2, 2), "summer"));
  sss_remove(sss2, "spring");
  assert(sss_count(sss2) == 2);
  assert(sss_search(sss2, "summer") == 1);
  
  sss_remove(sss2, "fall");
  assert(!strcmp(sss_get(sss2, 0), "summer"));
  sss_destroy(sss2);
  
  struct triple_s *sss3 = sss_create();
  
  assert(sss_count(sss3) == 0);
  sss_add(sss3, "hello");
  assert(sss_count(sss3) == 1);
  sss_remove(sss3, "hello");
  assert(sss_search(sss3, "hello") == -1);
  assert(sss_count(sss3) == 0);
  
  sss_add_follows(sss3, "bye");
  assert(!strcmp(sss_get(sss3, 0), "bye"));
  assert(sss_count(sss3) == 1);
  sss_remove(sss3, "bye");
  assert(sss_count(sss3) == 0);
  sss_destroy(sss3);
}       
