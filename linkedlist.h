#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

struct LinkedListData {
  void *data;
  size_t datasize;
  struct LinkedListData *next;
};

typedef struct LinkedListData LinkedListData;

struct LinkedList {
  int count;
  struct LinkedListData *first;
};

typedef struct LinkedList LinkedList;
typedef void *(*MAP_F)(void *);
typedef int (*FILTER_F)(void *);
typedef int (*FOLD_F)(void *, void *); //takes 2 arguments + and places the result in the first one - MUST return 1 if okay and if notl
LinkedList *create_linkedlist();
LinkedListData *create_linkedlistdata(void *data,  size_t copysize);
LinkedListData *create_linkedlistdata_inplace(void *data, size_t copysize);
int linkedlist_recount(LinkedList *list);
void free_linkedlistdata(LinkedListData *listhead);
void free_linkedlist(LinkedList *list);
LinkedList *create_linkedlist_range(int start, int end);
void append_to_linkedlist(LinkedList *list, void *data, size_t copysize);
LinkedListData *get_index_linkedlist(LinkedList *list,  int index);
void *get_index_data_linkedlist(LinkedList *list, int index);
LinkedList *get_index_range_linkedlist(LinkedList *list, int start, int end);
//make behave like index to - get data
LinkedList *linkedlist_map(LinkedList *list, MAP_F f );
LinkedList *linkedlist_map_inplace(LinkedList *list, MAP_F f );
LinkedList *linkedlist_filter(LinkedList *list, FILTER_F f);
LinkedList *linkedlist_filter_free(LinkedList *list, FILTER_F f);
void *linkedlist_foldr(LinkedList *list, FOLD_F f, void *base);
void *linkedlist_foldr_free(LinkedList *list, FOLD_F f, void *base);
LinkedList *linkedlist_merge_free(LinkedList *list1, LinkedList *list2);




//linkedlist level access

//insert
//pop/push
//return and remove
//array convert
//reverse
//free all linked list data
//in operator - raw data comparison? - size of data
//for each? 
//index
#endif


//inplace - do and free - fold, filter, map -inplace map - map - fold and free - filter and free
//union type for all numbers - num - 
