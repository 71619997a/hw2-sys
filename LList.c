#include <stdio.h>
#include <stdlib.h>

struct node {
    int i;
    struct node *next;
};

struct node* insert_front(struct node* start, int newData) {
    struct node *newNode = (struct node*)malloc(sizeof(struct node));
    newNode->i = newData;
    newNode->next = start;
    return newNode;
}

struct node* free_list(struct node* start) {
    if(start == NULL) {
        return NULL;
    }
    free_list(start->next);  // make sure all memory past is gone
    start->next = NULL;  // make sure we aren't pointing to freed memory
    free(start);  // now we can free this memory
    return start;
}

void print_list(struct node* start) {
    if(start == NULL) {
        printf("NULL\n");
        return;
    }
    printf("%d->", start->i);
    fflush(stdout);
    print_list(start->next);
}

int main() {
    printf("Testing print and free on a 1-el list (5)\n");
    struct node *end = (struct node*)malloc(sizeof(struct node));  // one way of making new node
    end->i = 5;
    end->next = NULL;
    print_list(end);
    end = free_list(end);
    printf("List freed\n");
    // print_list(end);  printing a null pointer is a bad idea

    printf("\nTesting all functions on a 3-el list\n");
    struct node *end2 = insert_front(NULL, 3);  // other way of making new node
    struct node *start = insert_front(insert_front(end2, 2), 1);
    print_list(start);
    printf("From second element:\n");
    print_list(start->next);
    free_list(start->next);
    start->next = NULL;  // we don't want to point to freed memory, bad idea
    printf("Freeing from second element on, new list:\n");
    print_list(start);
    free_list(start);
    printf("Freeing all\n");
    return 0;
}
