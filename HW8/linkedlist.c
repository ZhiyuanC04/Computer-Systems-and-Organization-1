/**
 * CSO1 HW8 Circularly Linked List Implementation
 *
 * Your Computing ID: vgs3qt
 */

//TODO: Remember to add include statement here. 
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

cll_node *cll_head(cll_node *list){
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 

    // If input is NULL, return NULL.
    if (!list) return NULL; 

    cll_node *current = list; 

    // If is_head is not 1, continue.
    while (!current -> is_head) { 
        current = current -> next;
    }

    return current;
}


cll_node *cll_tail(cll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 

    // If input is NULL, return NULL.
    if (!list) return NULL; 

    // The "last" node is the node just before the head node
    return cll_head(list) -> prev; 
}


unsigned long cll_length(cll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 

    // Count from 0, which thhe whole list is empty, NULL.
    unsigned long length = 0;
    // If input is NULL, return 0, default length.
    if (!list) return length; 

    cll_node *head = cll_head(list);
    cll_node *current = head;

    // Add length by 1 if there is next node. 
    do {
        length++;
        current = current -> next;
    // Start from head and end when we meet head again.
    } while (current != head);

    return length;
}

cll_node *cll_find(cll_node *list, int value) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 

    // If input is NULL, return NULL.   
    if (!list) return NULL;

    cll_node *current = list;
    
    // check if the value equals to input value parameter.
    do {
        if (current -> value == value) {
            // If the value is same, return this pointer.
            return current;
        }
        // Checks next node.
        current = current -> next; 
    // Stop before meet the list again. List is the start.
    } while (current != list); 
    // Value not found in whole linkedlist.

    return NULL; 
}

cll_node *cll_remove(cll_node *list) {
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 

    // If input is NULL, return NULL.
    // If there is only one node, so next/prev is itself, free it and return.
    if (!list || (list -> next == list && list -> prev == list)) {
        free(list);
        return NULL;
    }

    cll_node *next_node = list -> next;
    cll_node *prev_node = list -> prev;

    // Change the node order to remove the node "list".
    prev_node -> next = next_node;
    next_node -> prev = prev_node;

    // If we remove head and there are more than 1 node in the list.
    if (list -> is_head && next_node != list) {
        // Next node is new head.
        next_node -> is_head = 1;
    }

    // Free the space.
    free(list);

    // Return the pointer to next_node, which now occupies the old position.
    return next_node;
}


cll_node *cll_insert(int value, cll_node *list, int before) {  
    //TODO: Implement this function, see header file for description
    //TODO: Update return statement. 

    // Malloc a space for the new node.
    cll_node *new_node = malloc(sizeof(cll_node));

    // Set the values in new_node.
    new_node -> value = value;
    new_node -> is_head = 0;

    // If this input node will be the first node in the list.
    if (list == NULL) {
        // It is the only node in list.
        new_node -> next = new_node;
        new_node -> prev = new_node;
        // It is the head node.
        new_node -> is_head = 1;
        return new_node;
    } 
    // If not the only node in list.
    else {
        // If before is 1. Put the new node before node "list".
        if (before){
            new_node -> next = list;
            new_node -> prev = list -> prev;
            list -> prev -> next = new_node;
            list -> prev = new_node;
        }
        // Inserting after the node "list".
        else {
            new_node -> next = list -> next;
            new_node -> prev = list;
            list -> next -> prev = new_node;
            list -> next = new_node;
        }
    }
    
    return new_node;
}

/**
 * Displays the contents of the list separated by commas and surrounded by
 * brackets, with the pointed-to node highlighted with asterisks.
 *
 * Reference solution provided with assignment description
 */
void cll_show(cll_node *list) {
    // Find the head of the linked list
    cll_node *head = cll_head(list);
    cll_node *ptr = head;
    // Print opening [
    putchar('[');
    // Loop through list printing values
    if (ptr) {
        do {
            if (!ptr->is_head) 
                printf(", "); // include a comma if not the first element
            if (ptr == list) 
                putchar('*'); // include * surrounding parameter element
            printf("%d", ptr->value);
            if (ptr == list) 
                putchar('*');
            ptr = ptr->next; // next pointer
        } while (ptr != head);
    }
    // Print closing ]
    puts("]");
}

int main(int argc, const char *argv[]) {
    // Example debugging code.  You should write other
    // tests, including testing corner cases.
    cll_node *x = NULL;
    putchar('A'); cll_show(x);
    x = cll_insert(25, x, 1);
    putchar('B'); cll_show(x);
    x = cll_insert(1, x, 0);
    putchar('C'); cll_show(x);
    x = cll_insert(98, x, 1);
    putchar('D'); cll_show(x);
    x = cll_insert(0, x, 1);
    putchar('E'); cll_show(x);
    x = cll_insert(-8, cll_tail(x), 0);
    putchar('F'); cll_show(x);
    cll_node *y = cll_head(x);
    putchar('G'); cll_show(y);
    printf("Length: %lu (or %lu)\n", cll_length(y), cll_length(x));
    x = cll_remove(x);
    putchar('H'); cll_show(x);
    putchar('I'); cll_show(y);
    x = cll_remove(cll_find(y, 98));
    putchar('J'); cll_show(x);
    putchar('K'); cll_show(y);

    return 0;
}