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

LinkedList *create_linkedlist();
LinkedListData *create_linkedlistdata(void *data,  size_t copysize);
void free_linkedlistdata(LinkedListData *listhead);
void free_linkedlist(LinkedList *list);
LinkedList *create_linkedlist_range(int start, int end);
void append_to_linkedlist(LinkedList *list, void *data, size_t copysize);
LinkedListData *get_index_linkedlist(LinkedList *list,  int index);
void *get_index_data_linkedlist(LinkedList *list, int index);
LinkedList *get_index_range_linkedlist(LinkedList *list, int start, int end);
#endif


