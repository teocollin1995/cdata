#include <stdbool.h>
#include <assert.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <stddef.h>
#include "linkedlist.h"


LinkedList *create_linkedlist(){
  LinkedList *result = malloc(sizeof(LinkedList));
  assert(result != NULL);
  result->count = 0;
  result->first = NULL;
  return result; //Valgrind is telling me this is unitalialized
}


LinkedListData *create_linkedlistdata(void *data,  size_t copysize){
  assert(copysize > 0);
  LinkedListData *result = malloc(sizeof(LinkedListData));
  assert(result != NULL);
  result->datasize = copysize;
  result->data = malloc(copysize);
  memcpy(result->data, data, copysize);
  result->next = NULL;
  return result;
}


void append_to_linkedlist(LinkedList *list, void *data, size_t copysize){
  assert(copysize > 0);
  assert(list != NULL);
  int listcount = list->count;
  if(listcount == 0){
    list->first = create_linkedlistdata(data, copysize);
    list->count++;
  }
  else{
    LinkedListData * listhead = list->first;
    for(int listitter = 1; listitter < listcount; listitter++){
      listhead = listhead->next;
    }
    listhead->next = create_linkedlistdata(data, copysize);
    list->count++;
  }
}



LinkedListData *get_index_linkedlist(LinkedList *list,  int index)
{
  int listcount = list->count;
  if(listcount == 0 ){
    
    return NULL;
  }
  if(listcount < index){
    
    return NULL;
  }
  if(index < 0)
    {
    
      return NULL;
    }
  
  
  LinkedListData *listhead = list->first;
  // we are starting at 0 so we can have 0 based indexing
  for(int listitter = 0; listitter < index; listitter++){
    listhead = listhead->next;
    //abstract this, clearly...
  }
  return listhead;
}

void *get_index_data_linkedlist(LinkedList *list, int index){

  LinkedListData *result = get_index_linkedlist(list, index);
  if(result == NULL){

    return NULL;
  }

  return result->data;

  
}




