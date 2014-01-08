#include<stddef.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define BUF_SIZE 256;

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
struct node* ReadWords(struct node *dict,FILE *fp) {
	
	//struct node *head = NULL;
//  char *line_in = malloc(sizeof(BUF_SIZE));

	while (fgets(dict->word, BUF_SIZE, fp) != 1) {
		insert(line_in);
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

int main (void) 
{
  struct node *wordlist = NULL;
  FILE *fp = fopen("/CSC360/fall360/palin","r");
  if (fp == NULL) {
    exit(EXIT_FAILURE);
  }
	//char line_in[BUF_SIZE];
	ReadWords(wordlist,fp);
	
	
	

	return(0);
}
//Find max number of words, 
//1st pass find all simple palins, store those that aren't simple
//for each non-simple palin, do strrev and strcmp, if word is found in list return both words
