/*
 * Comments below indicate what the program _should_ do.
 *
 * This program reads some information including age (integet), 
 * name(sequences of lower case letters) and gender(character)
 * one per line and add one by one in a doubly linked list if they don't exist.
 * If we have them already our data structure, it deletes that entry instead.
 * Then it reverses the list and prints those people one by one in right order
 * and reverse order.
 *
 * Do not add any error checking.  Existing error checking only for
 * convenience (i.e., to ensure tested with proper input files).
 *
 * This code's style and quality are not necessarily good.
 *
 * Follow the instructions given during the Lab Exam, and fix this
 * code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* maximum number of characters in an error message */
#define MAX_NAME 128

/* represents one string, which is stored as a linked list. */
typedef struct person 
{
	struct person *prev;
	struct person *next;
	int age;
	char *name;
	char gender;

} person;

/* global vars. */
FILE* input_file = NULL;
/* head of linked list containing people*/
person* head = NULL;
/* tail of linked list containing people */
person* tail = NULL;

/* See definitions for comments. */
void read_data(FILE *);
void reverse();
person * new_person(char *, int, char);
void delete_person(person *);
void free_person(person *);
void push_back(person *);
void print_rightorder(person *);
person * find_person(person *);
int isequal(person, person);
void push_front(person *);
void print_reverseorder(person *);
void print_error(char *);
void clean_up();

/*
 * Reads input data and print the output using print functions
 */
int main(int argc, char **argv)
{
	if (argc != 2)
		print_error("must have 1 arg.  usage ./bug input_file");

	input_file = fopen(argv[1], "r");
	if (input_file == NULL)
		print_error("problem opening input file");

	read_data(input_file);
	reverse(head,tail);
	printf("====  right order  ==== \n");
	print_rightorder(head);
	printf("==== reverse order ==== \n");
	print_reverseorder(tail);
	clean_up();

	exit(EXIT_SUCCESS);
}

/*
 * Reads the information from input
 */
void read_data(FILE *input_file) {
	char name[MAX_NAME],gender;
	int age;
	while(fscanf(input_file,"%s %d %c",name,&age,&gender)!=EOF) {
		person* np = new_person(name,age,gender);
		person* find = find_person(np);
		if(find==NULL)
			push_back(np);
		else {
			free_person(np);
			delete_person(find);
		}
	}
}

/*
 * Prints error message 'msg' and exits.
 */
void print_error(char *msg)
{
	fprintf(stderr, "error: %s\n", msg);
	clean_up();
	exit(EXIT_FAILURE);
}

/*
 * Reverses out doubly linked list
 */
void reverse() {
	person *tmp;
	for(person *it=head;it!=NULL;it=tmp) {
		tmp = it->next;
		it->next = it->prev;
		it->prev = tmp;
	}
	tmp = head;
	head = tail;
	tail = tmp;
}


/*
 * Creates a new person using the parameters
 */
person * new_person(char *name, int age, char gender)
{	
	person*np = calloc(1,sizeof(person));
	strcpy(np,name);
	np->age = age;
	np->gender = gender;
	np->name = calloc(strlen(name)-1,sizeof(char));
	return np;
}

/*
 * Delete this particular person from the list
 */
void delete_person(person *p)
{
	if(p->prev != NULL)
		p->prev->next = p->next;
	else
		head = p->next;
	if(p->next != NULL)
		p->next->prev = p->prev;
	else
		tail = p->prev;
	free_person(p);
}

/*
 * Adds a person in front of our doubly linked list and updates 
 * the pointers as well as head and tail properly
 */
void push_front(person *np)
{
	np->prev = NULL;
	np->next = head;
	if(head==NULL) {
		head = tail = np;
	} else {
		head->prev = np;
		head = np;
	}
	return;
}

/*
 * Adds a person in the back of our doubly linked list and updates 
 * the pointers as well as head and tail properly
 */
void push_back(person *np)
{
	np->next = NULL;
	np->prev = tail;
	if(tail==NULL) {
		head = tail = np;
	} else {
		tail->next = np;
		tail = np;
	}
	return;
}

/*
 * Prints people that we have in our data structure in reverse order
 */
void print_reverseorder(person *tail)
{
	for(person* it=tail; it!=NULL; it=it->prev)
			printf("%s %d %c\n",it->name,it->age,it->gender);
	return;
}

/*
 * Returs 1 if the information of these to people are the same; otherwise 0.
 */
int isequal(person p1, person p2)
{
	return p1.gender==p2.gender && p1.age==p2.age && strcmp(p1.name,p2.name)==0;
}

/*
 * Find this particular person in the list and returns NULL if it does't exist.
 */
person* find_person(person *p)
{
	for(person* it=head; it!=NULL; it=it->next) {
		if(isequal(*it,*p))
			return it;
	}
	return NULL;
}

/*
 * Prints people that we have in our data structure in right order
 */
void print_rightorder(person *head)
{
	for(person* it=head; it!=NULL; it=it->next)
			printf("%s %d %c\n",it->name,it->age,it->gender);
	return;
}


/*
 * Clean all of the allocated dynamic memory
 */
void clean_up() {
	for(person *it = head; it!=NULL;) {
		person *tmp = it->next;
		free_person(it);
		it = tmp;
	}
}

/*
 * Free the memory that this entry has in the memory
 */
void free_person(person *p)
{
	p->next = NULL;
	p->prev = NULL;
	free(p->name);
	free(p);
}

