#A personal project: Implement a bunch of cdata structures


My university is kind of odd in that it doesn't have a data structures class. There is an algorthims class and there is a functional data structures class, but unlike many of my friends, I will not be forced to go through a class that makes me implment many structures in c. This is not to say that we don't (many structures come up in class), but there is no focus on it. So, I've taken it upon myself to just implement a lot of them over time in as thorough and ridiclous a way as possible...

## Linked Lists


By the time that I got to post this on git, I've already started on a 'generic' linked list structure and many functions for it. Generic in this case means that each data has a void pointer and a data size. I'll be implementing as many functions as I can think of from map,foldr,and filter using function pointers to versions of merge that keep or destroy the other lists. Each function will be tested so that a decade from now when I'm too lazy to write my own linkedlist again, I can just grab this one and be sure it works. A list of functions that I've not yet implemented is commented out in the bottom of the linked list header. Descriptions for each are kept in a seperate file which will be added on completion (i.e once I've verified that they do what they say they should).


## The FUTURE


I plan to implement hashmaps, doublies, trees, and all that fun stuff once I have some more free time. As this is just a personal project, I'll work on it when I have time and feel like it. 


## Other


Compiling with just 'make' is to compile test.c while make linkedlist_test compiles the tests for linkedlists. There is a make clean.
