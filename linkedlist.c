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

LinkedListData *create_linkedlistdata_inplace(void *data, size_t copysize){
  assert(copysize > 0);
  LinkedListData *result = malloc(sizeof(LinkedListData));
  assert(result != NULL);
  result->datasize = copysize;
  result->data = data;
  result->next = NULL;
  return result;
}

int linkedlist_recount(LinkedList *list){
  if(list->first == NULL){
    return 0;

  }
  int count = 1;
  LinkedListData *listhead = list->first; //what if it is a 0?
  while( listhead->next != NULL){
    count++;
    listhead = listhead->next;
  }
  return count;


}

void free_linkedlistdata(LinkedListData *listhead){
  free((void *) listhead->data);
  free((void *) listhead);
}


void free_linkedlist(LinkedList *list){
  //check for count == 0
  LinkedListData *listhead = list->first;
  LinkedListData *next;
  int listitter;
  for(listitter = 0; listitter < list->count; listitter++){
    next = listhead->next;
    free_linkedlistdata(listhead);
    listhead = next;

  }
  free((void *) list);
}
//union for int
LinkedList *create_linkedlist_range(int start, int end){
  if(!(start < end)){
    return NULL;

  }

  LinkedList *result = create_linkedlist();
  int i;
  int intsize = sizeof(int);
  result->first = create_linkedlistdata((void *) &start, intsize);
  LinkedListData *listhead = result->first;
  for(i = start + 1; i <= end; i++){
    listhead->next = create_linkedlistdata((void *) &i, intsize);
    listhead = listhead->next;
  }
  result->count = end - start + 1;
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

LinkedList *linkedlist_map(LinkedList *list, MAP_F f ){
  //f must malloc memory
  int listcount = list->count;
  int listitter;
  LinkedList *new = create_linkedlist();
  //create linked list to put new data in
  //opeation for first element list:
  LinkedListData *listhead = list->first;
  new->first = create_linkedlistdata_inplace( (*f)(listhead->data), listhead->datasize);
  LinkedListData *newlisthead = new->first;
  for(listitter = 1; listitter < listcount; listitter++){
    newlisthead->next = create_linkedlistdata_inplace( (*f)(listhead->next->data), listhead->next->datasize);
    listhead = listhead->next;
    newlisthead = newlisthead->next;
  }
  new->count = list->count;
  return new;

}

LinkedList *linkedlist_map_inplace(LinkedList *list, MAP_F f){
  int listcount = list->count;
  int listitter;
  LinkedListData *listhead = list->first;
  //f should not malloc memory
  for(listitter = 0; listitter < listcount; listitter++){
    listhead->data = (*f)(listhead->data);
    listhead = listhead->next;
  }
  return list;
}


LinkedList *linkedlist_filter(LinkedList *list, FILTER_F f){
  int listcount = list->count;
  int listitterw = 0;
  int listitter;
  LinkedListData *listhead = list->first;
  LinkedListData *newlisthead;
  LinkedList *new = create_linkedlist();
  while (! (*f)(listhead->data)){
    listitterw++;
    listhead = listhead->next; //segfault is none of them meet the condtions?
  }
  listitterw++;
  new->first = create_linkedlistdata(listhead->data, listhead->datasize);
  newlisthead = new->first;
  listhead = listhead->next;
  new->count++;
  for(listitter = listitterw; listitter < listcount; listitter++){
    //printf("itter: %d\n", listitter);
    if((*f)(listhead->data)){
      newlisthead->next = create_linkedlistdata(listhead->data, listhead->datasize);
      newlisthead = newlisthead->next;
      new->count++;
    }
    listhead = listhead->next; 
  }
  
  return new;

}
LinkedList *linkedlist_filter_free(LinkedList *list, FILTER_F f){
  int listcount = list->count;
  int numbermatched = 0;
  int listwalk = 0;
  LinkedListData *listhead = list->first;
  LinkedListData *listend;
  LinkedListData *listtemp;
  //find the new head of the list
  while (! (*f)(listhead->data)){
    listwalk++;
    listtemp = listhead->next; //segfault is none of them meet the condtions?
    free_linkedlistdata(listhead);
    listhead = listtemp;
  }
  numbermatched++;
  listwalk++;
  list->first = listhead;
  listend = list->first;
  listhead = listhead->next;
  
  while (listwalk < listcount){
    if ((*f)(listhead->data)){
     
      numbermatched++;
      listend->next = listhead;
      listend = listend->next;
      listhead = listhead->next;
    }
    else{
     
      listtemp = listhead->next;
      free_linkedlistdata(listhead);
      listhead = listtemp;

    }
    listwalk++;
    
  }
  list->count = numbermatched;
  return list;
  

}


void *linkedlist_foldr(LinkedList *list, FOLD_F f, void *base){
  int listcount = list->count;
  LinkedListData *listhead = list->first;
  int listitter;
  int okay;
  for(listitter = 0; listitter < listcount; listitter++){
    okay = (*f)(base, listhead->data);
    if(! okay){
      return NULL;
    }
    listhead = listhead->next;
  }

  return base;

}

void *linkedlist_foldr_free(LinkedList *list, FOLD_F f, void *base){
  int listcount = list->count;
  LinkedListData *listhead = list->first;
  LinkedListData *temp;
  int listitter;
  int okay;
  for(listitter = 0; listitter < listcount; listitter++){
    okay = (*f)(base, listhead->data);
    if(! okay){ //if everything fails, we should still clean up because otherwise we get a leak!
      for(int freelistitter = listitter; freelistitter < listcount; freelistitter++){
	temp = listhead->next;
	free_linkedlistdata(listhead);
	listhead = temp;
      }
      return NULL;
    }
    temp = listhead->next;
    free_linkedlistdata(listhead);
    listhead = temp;
  }
  free((void *) list);

  return base;

}
//maybe make one that doesn't consume the other list?
LinkedList *linkedlist_merge_free(LinkedList *list1, LinkedList *list2){
  int listitter;
  int listcount1 = list1->count;
  LinkedListData *list1head = list1->first;
  LinkedListData *list2head = list2->first;
  list1->count += list2->count;
  //at which point we no longer need the head for list2
  //free((void *) list2);
  for(listitter = 0; listitter < listcount1 - 1; listitter++){
    list1head = list1head->next;
  }

  list1head->next = list2head; //would it be faster to just compare their lengths
  return list1;

  
}
