#include "parser.h"
#include "lexer.h"
/**************************************
 * File: parser.c
 * This file implements the interface given in parser.h
***************************************/

/**************************************
 * Function: newCell()
 * Function returning a pointer to a cons cell. This will allocate memory needed for a cons cell and will
 * initialise content to be an empty string, first pointer and rest pointer to be NULL
 * If the content is changed later, content string will be replace will a new string
***************************************/
cons_cell newCell() {
    cons_cell aCell;
    aCell = (cons_cell)malloc(sizeof(struct cell));
    aCell->content = "";
    aCell->first = NULL;
    aCell->rest = NULL;
    return aCell;
}
/**************************************
 * Private function: helperList(cons_cell cur, char* c)
 * Function creating a sequence of connected cons cell representing a full list from user input
 * There are two cases:
 *      (1): if user input is simply a symbol, cons cell structure will designate two cons cell: one is special
 *      character (#) to specify this case, and two is the actual symbol
 *      (2): If exist a list, the cons cell structure will not store parentheses but only all the symbols
 *      of a particular list. The cons cell per se will either have an empty string, NOT NULL pointer first
 *      to another list, or contain a NOT EMPTY string and a NULL first pointer
 * This function will return a cons_cell pointer pointing to the first cons cell
***************************************/
static cons_cell helperList(cons_cell cur, char* c) {
    cons_cell local, temp;
    if (!strcmp(c, "(")) { //starting of a new list
        local = newCell();
        c = getToken();
        local->first = helperList(local, c);
        temp = local; //assign the address
        c = getToken();
        while (strcmp(c, ")")) { //when the token is NOT ')'
            temp->rest = newCell();
            temp = temp->rest;
            temp->first = helperList(temp, c);
            c = getToken();
        }
        temp->rest = NULL;
        return local;
    } else {
        if(cur == NULL){
            local = newCell();
            local->content = "#";
            local->rest = newCell();
            local->rest->content = c;
            return local;
        }
        if (!strcmp(c, "()")) {
            local = newCell();
            return local;
        }
        //create a new string for cons_cell content
        char* string = (char*)malloc(strlen(c)*sizeof(char));
        string = strcpy(string, c);
        cur->content = string;
        return NULL;
    }

}

/**************************************
 * A public function starting to read input from user. See header for usage
***************************************/
cons_cell S_Expression() {
    char *firstToken;
    startTokens(20);
    firstToken = getToken();

    cons_cell result = NULL;
    result = helperList(result, firstToken);
    return result;
}

/**************************************
* Function: helperPrint(cons_cell list, int lastRecursion)
* Private function being used in printList
***************************************/
static void helperPrint(cons_cell list, int lastRecursion) {
    if(list == NULL)
        return;
    if(strcmp(list->content,"#")) {
        printf("(");
        cons_cell temp = list;
        while(temp != NULL) {
            if (strcmp(temp->content, "")) {
                printf("%s", temp->content);
                if (temp->rest != NULL)
                    printf(" ");
            }
            //the if statement is to decide whether to print a space after ")"
            if (temp->rest == NULL)
                helperPrint(temp->first, 1);
            else
                helperPrint(temp->first, 0);
            temp = temp->rest;
        }
        if (lastRecursion)
            printf(")");
        else
            printf(") ");
    } else {
        printf("%s ",list->rest->content);
    }
}

/**************************************
 * Function: printList(cons_cell list)
 * Public function receiving a cons_cell list as parameter and printing out everything inside a list
 * including parentheses to contain a list
 * No matter what the format of input is, the output printed out will always be in this format:
 * ((symbol[space]symbol)[space](symbols))
***************************************/
void printList(cons_cell list) {
    helperPrint(list, 0);
}

/*void helper(char *c, int numTab) {
    int j;
    printTab(numTab);
    printf("S_expression\n");
    if (!strcmp(c, "(")) {
        printTab(numTab);
        printf("%c\n", *c);
        c = getToken();
        helper(c, numTab + 1);
        while (strcmp(c, ")")) {
            helper(c, numTab + 1);
        }
        printTab(numTab);
        printf("%c\n", *c);
        if (numTab != 0)
            c = getToken();
    } else {
        //handle symbol or () 
        printTab(numTab);
        printf("\t%s\n", c);
        if (numTab != 0)
            c = getToken();
    }
}

void S_Expression() {  
    char *c;
    startTokens(20);
    c = getToken();
    
    helper(c, 0);
}
void printTab(int numTab) {
    int j;
    for(j = 0; j < numTab; j++)
            printf("\t");
}*/