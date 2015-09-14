#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "linkedlist.h"



int main(){
  LinkedList *crap0 = create_linkedlist();
  for(int i = 0; i < 100; i++){
    append_to_linkedlist(crap0, (void *) &i, sizeof(int));
  }
  for(int a = 0; a < 101; a++){
    printf("a is %d\n", a);
    int *b =  get_index_data_linkedlist(crap0, a);
    printf("Pointer is at %d\n", *b);
    //printf("Value: %d\n", *b);
  }
  printf("%d\n", *((int *)crap0->first->data));
  printf("%d\n", *((int *)crap0->first->next->data));
  printf("%d\n", crap0->count);
  
}
