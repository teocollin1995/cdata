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
    int listitter;
    for(listitter = 1; listitter < listcount; listitter++){
      listhead = listhead->next;
    }
    listhead->next = create_linkedlistdata(data, copysize);
    list->count++;
  }
}



LinkedListData *get_index_linkedlist(LinkedList *list,  int index){
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
  int listitter;
  for(listitter = 0; listitter < index; listitter++){
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


LinkedList *get_index_range_linkedlist(LinkedList *list, int start, int end){
  int listcount = list->count;
  int returnlength = end - start;
  if(end -1 > listcount){
    return NULL;
  }
  if(start -1 > listcount){
    return NULL;
  }
  if(start < 0 ){
    return NULL;
  }
  if(end < 0){
    return NULL;
  }
  if(start >= end){
    return NULL;
  }
  int listitter = 0;
  LinkedListData *listhead = list->first;
  while (listitter < start ){
    listhead = listhead->next;
    listitter++;
  }
  //get size/ copy/crap/
  
  LinkedList *new = create_linkedlist();
  /* So, at this point, I could just call linkedlist_append a few times, but that would be dreadfully inefficient because each call to append will walk through the linked list, which is horrendous. Instead, we just walk through the two lists at the same time, generating the next element for the new list from the corresponding element of the old list. We don't just memcpy the whole thing because we want new refrences to the data each linked list void * data points to'. Also, using memcpy is a security whole that we should try to avoid as much as one can even when doing "generics" in C. I hope copying the data is better than just copying the struct. */
  new->count = returnlength + 1;
  new->first = create_linkedlistdata(listhead->data, listhead->datasize); //copy the first data; THis is why we don't count the first in return length
  LinkedListData *newlisthead;
  newlisthead =  new->first;
  listhead = listhead->next; //advance
  
  for(listitter = 0; listitter < returnlength; listitter++){
    newlisthead->next = create_linkedlistdata(listhead->data,listhead->datasize);
    newlisthead = newlisthead->next;
    listhead = listhead->next;
  }
  

  return new;
  
  

}

