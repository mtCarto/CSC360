#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUF_SIZE 256;

typedef struct stdin_dict {
  char** words;
  int size;
}stdin_dict;

//linked list to hold input words
struct node {
	char *word;
	struct node *next; 
}*head; 

typedef struct node item;

//add word from input to list

void append(char *data) {
	struct node *temp, *right;
	temp = (struct node *)malloc(sizeof(struct node));	
	temp->word = data;
	right = (struct node *)head;
	
	while (right->next != NULL) {
		right = right->next;
		right->next = temp;
		right=temp;
		right->next=NULL;
	}
}
	
void add( char *data) {
	struct node *temp;
	temp = (struct node *)malloc(sizeof(struct node));
	temp->word = data;
	if (head == NULL){ 
		head = temp;
		head->next = NULL;
	}
	else {
		temp->next = head;
		head = temp;
	}
}

void insert(char *data) {
	struct node *temp;
	temp = head;
	if (temp == NULL) {
		add(data);
	} else {
		append(data);
	}
}
//Find word in the list, return 1 (true) if a word is in the list
struct node* search(char *data, struct node **prev) {
	struct node *head = head;
	struct node *temp = NULL;
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
stdin_dict* ReadWords(FILE *fp) {
	stdin_dict *dict = calloc(1,sizeof(stdin_dict));
  if (dict == NULL) {
    printf("Error allocating for dict. \n");
    exit(-1);
  }

  dict->size = 1;
  dict->words = malloc(dict->size * sizeof(char*));
  if (dict->words == NULL) {
    printf("Error allocating for words. \n");
    exit(-1);
  }


  int stdin_pos = 0;

  for(;;) {
    //check if there is room for a word
    //allocate for space for word
    dict->words[stdin_pos] = calloc(256,sizeof(char*));
    //check if alloc worked

    void* in_status = fgets(dict->words[stdin_pos],256 ,fp);
    if (in_status == NULL) {
      break;
    } else {
      if (dict->words[stdin_pos][strlen(dict->words[stdin_pos])-1] == '\n') {
        dict->words[stdin_pos][strlen(dict->words[stdin_pos])-1] = 0;//strip newline off end of word
      }
    }
    printf("%s", dict->words[stdin_pos]);
  }	
	return dict;
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
int isPalin(char *ptest)
{
	//temp variable b to hold reversed string
	char *b = malloc(sizeof(ptest));
	//copy and reverse the word
	strcpy(b,ptest);
	strrev(b);

	//Test for simple palindrome
	if ( strcmp(ptest,b)== 0){ 
		free(b);
		return 1;
	}
	else
		return 0;
}

int main (int argc,char *argv[]) 
{
  printf("Welcome!\n");
  FILE *fp = fopen("/CSC360/fall360/words","r");
  if (fp == NULL) {
    exit(EXIT_FAILURE);
  }
	ReadWords(fp);
	
	
  exit(0);
	return 0;
}
//Find max number of words, 
//1st pass find all simple palins, store those that aren't simple
//for each non-simple palin, do strrev and strcmp, if word is found in list return both words
