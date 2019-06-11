/*
 * File:   parser.h
 * Author: bradley
 *
 * Created on February 21, 2018, 9:55 PM
 */
/****************************************************************
 File: parser.h
 ----------------
 This is the interface for a parser for part of Scheme.
 It has an operation for starting the list and printing out the whole list
 ****************************************************************/
#ifndef PARSER
#define PARSER

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**************************************
 * struct cell members:
 * content: the string content representing a symbol
 * first: another nested struct representing a nested list
 * rest: the rest of the list
***************************************/
typedef struct cell {
    char *content;
    struct cell* first;
    struct cell* rest;
} *cons_cell;
//void S_Expression();
/****************************************************************
 Function: S_Expression();
 ------------------------------------
 Initialize a structure for a list containing symbols. However, the length of symbols is restrained
 within the max length of a token from lexical analyser

 Call this function to start building a structure. Simply call,

    cons_cell result;
    result = S_Expression();

 There is no argument required for this function. However, it will return a pointer to the first cons_cell of the
 structure. In case there is no list involve (simply a plain symbol), S_Expression() will return a structure with two
 cons_cell (one contains a special character "#" and the other contains the symbol itself)
 */
cons_cell S_Expression();

/****************************************************************
 Function: printList(cons_cell list, int lastRecursion
 ------------------------------------
 Function is used to print out a whole list

 Using: This function requires one parameter, the pointer to a list

    printList(list);

 The function does not return any value. It ends when finishing printing out a whole list.
 */
void printList(cons_cell list);
//include documentation here
cons_cell newCell();


#endif /* PARSER_H */
