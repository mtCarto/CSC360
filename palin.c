#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUF_SIZE 256;
#define TRUE 1
#define FALSE 0
//linked list to hold input words
struct dict {
	char *word;
	struct dict *next; 
}*head; 

struct dict *head = NULL;
struct dict *curr = NULL;
//typedef struct dict item;
int isPalin(char *ptest);
//add word from input to list, check if list is empty
struct dict* add_toList(char *data) {
  //if list is empty create new list
	if (head == NULL){ 
		printf("Creating new list.\n");
    struct dict *ptr = (struct dict*)malloc(sizeof(struct dict));
    if (ptr == NULL) {
      printf("error creating ptr\n");
      return NULL;
    }
    ptr->word = data;
    ptr->next = NULL;

    head = curr = ptr;
	  return ptr;
  } 
  //else add to end of list
	else {
    //printf("Adding to end of list.\n");
    struct dict *ptr = (struct dict*)malloc(sizeof(struct dict));
    if (ptr == NULL) {
      printf("error creating ptr\n");
      return NULL;
    }
    ptr->word = data;
    ptr->next = NULL;

    curr->next = ptr;
    curr = ptr;

    return ptr;
	}
}


//Find word in the list, return 1 (true) if a word is in the list
struct dict* search(char *data, struct dict **prev) {
	struct dict *head = head;
	struct dict *temp = NULL;
	int found = 0;
	while (head != NULL) {
		if (head->word == data) {
			found = 1;
			break;
		
		}
		else {
			temp = head;
			head = head->next;
		}
	} 
	
	if (found == 1) {
		if (prev)
			*prev = temp;
		return head;
	}
	else {
		return NULL;
	}
}
	
	
//Read word list into an array words[] to use for dictionar
struct dict* ReadWords(FILE *fp) {
    
  //initialize dict list
  struct dict *ptr = NULL;
  for(;;) {
    //malloc less? check for size of input
    //do check for room, if not double size
    //char *wordIn = (char *)malloc(sizeof(256));
    char *wordIn = calloc(256,sizeof(char*));
    if (wordIn == NULL) {
      printf("Error allocating wordIn \n");
    }
    void* in_Word = fgets(wordIn,256,fp);
    if (in_Word == NULL) {
      printf("Error reading word \n");
      break;
    } else {
      //ignore words with less than 3 characeters
      if (strlen(wordIn) <= 4) {
        continue;
      }
    //strip newline from input word
      char *cptr;
      if ((cptr = strchr(wordIn,'\n')) != NULL) {
        *cptr = '\0';
      }
      if (isPalin(wordIn) == 0) {
        printf("%s \n",wordIn);
        //add_toList(wordIn);
      }
    }
  //trouble here, doesn't like this free after awhile
  free(wordIn);
  }
	return ptr;
}

//Reverse string
char *strrev(char *str) {
	char *p1,*p2;

	if (! str || ! *str)
		return str;
	for (p1 = str, p2 = str + strlen(str)-1; p2 > p1; ++p1, --p2)
	{	
		*p1 ^= *p2;
		*p2 ^= *p1;
		*p1 ^= *p2;
	}	
	return str;
}

//palindrome test, ptest is the word to be tested
int isPalin(char *ptest) {
  //char *tempstr;
  //get malloc working properly, possible error here or in alloc in ReadWords
  char *tempstr = (char *)malloc(strlen(ptest) * sizeof(128));
  strcpy(tempstr,ptest);
  strrev(tempstr);
 // printf("%s \n", ptest);
 // printf("%s \n", tempstr);
  if (strcmp(tempstr,ptest) == 0) {
    strrev(ptest);
    free(tempstr);
    return 0;
  }
  else {
    free(tempstr);
	  return 1;
  }
}

void printList(void) {
 // your looking at an empty struct, everything is in stdin_dict *dict........
 // struct node *ptr = head;
  
  printf("\n ------List Start------ \n");
  
  printf("\n -----List End------- \n");
  return;
}


int main (int argc,char *argv[]) 
{ 
  printf("Welcome!\n");
  FILE *fp = fopen("/home/mcthomps/CSC360/s360/words","r");
  if (fp == NULL) {
    printf("file failed to open\n");
    exit(EXIT_FAILURE);
  }
  
   ReadWords(fp);
 // printList(dict);
//check if word is a simple palindrome
//  yes: add to output list
//if not check if it's reverse is in the list
//  yes: insert into output list
//else continue
  fclose(fp);
  exit(0);
	return 0;
}
//for each non-simple palin, do strrev and strcmp, if word is found in list return both words
