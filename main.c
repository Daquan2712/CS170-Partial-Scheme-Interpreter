//
// Created by Bradley Pham
//

#include "parser.h"
#include "evaluate.h"

void main() {

    while (1) {
        printf("scheme> ");
        cons_cell list;
        list = S_Expression();
        cons_cell result = eval(list);
        printList(result);
        printf("\n");
        if(!strcmp(result->content, "Have a nice day!"))
            break;
    }
}