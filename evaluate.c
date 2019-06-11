//
// Created by bradley on 4/10/18.
//

#include "evaluate.h"
/**************************************
 * File: parser.c
 * This file implements the interface given in parser.h
***************************************/


/**************************************
 * Helper methods
 * These methods are implemented in other methods
 **************************************/
//To copy a list and return a cons_cell pointer to its duplicate
cons_cell copyList(cons_cell list) {
    cons_cell temp, tracker, result;
    temp = list;
    tracker = newCell();
    result = tracker;
    while (temp != NULL) {
        if (temp->first != NULL) {
            tracker->first = copyList(temp->first);
        } else {
            tracker->content = temp->content;
        }
        temp = temp->rest;
        if (temp != NULL) {
            tracker->rest = newCell();
            tracker = tracker->rest;
        }
    }
    return result;
}
//To store global definition
cons_cell globalEnvironment;
//To create a new symbol
cons_cell newSymbol(char* content) {
    cons_cell result = newCell();
    result->content = "#";
    result->rest = newCell();
    result->rest->content = content;
    return result;
}
//To help method equal with recursive call
int equalHelper(cons_cell list1, cons_cell list2) {
    cons_cell track1 = list1;
    cons_cell track2 = list2;
    int isEqual = 1;
    while(track1 != NULL && track2 != NULL) {
        if (strcmp(track1->content, track2->content)) {
            isEqual = 0;
            return isEqual;
        }
        if (track1->first != NULL && track2->first != NULL) {
            isEqual = equalHelper(track1->first, track2->first);
        }
        track1 = track1->rest;
        track2 = track2->rest;
    }
    if ((track1 == NULL && track2 != NULL) || (track1 != NULL)) //the later situation means tracks2 is already NULL
        isEqual = 0;
    return isEqual;
}
//to create the pair for define method
cons_cell helperDefine(char* name, cons_cell value) {
    cons_cell pair = newCell();
    pair->content = name;
    pair->rest = newCell();
    pair->rest->first = evalHelper(value, globalEnvironment);
    return pair;
}
cons_cell helperDefineList(char* name, cons_cell definition) {
    cons_cell pair = newCell();
    pair->content = name;
    pair->rest = newCell();
    pair->rest->first = definition;
    return pair;
}
/**************************************/

/**************************************
 * Function: symbol(cons_cell list)
 * Function returning a pointer to a cons cell. The cons cell will contain a symbol "#t" if
 * the parameter is a symbol, otherwise, an empty string
***************************************/
cons_cell symbol(cons_cell list) {
    cons_cell result;
    if (!(strcmp(list->content, "#"))) {
        result = newSymbol("#t");
    } else {
        result = newSymbol("#f");
    }
    return result;
}

/**************************************
 * Function: cdr(cons_cell list)
 * Function returning a pointer to a cons cell which will always contain a list
 * For instance: (cdr (quote (a b))) will return (b) instead of just a symbol b
***************************************/
cons_cell cdr(cons_cell list) {
    cons_cell result;
    if (!strcmp(list->content, "#")) { //if argument is a symbol
        result = newSymbol(list->content);
    } else if (list->rest != NULL) { //if there are elements after the first one
        result = list->rest;
    } else
        result = newCell();
    return result;
}

/**************************************
 * Function: car(cons_cell list)
 * Function returning a pointer to a cons cell which will contain either a list or a symbol
 * In case of symbol, the struct will contain two cons cell: one will contain symbol "#", the other will contain the symbol.
 * This will maintain our program's convention for a symbol and a list
 * For instance: (car (quote (a b))) will return a
 *               (car (quote ((a b) c) will return (a b)
***************************************/
cons_cell car(cons_cell list) {
    cons_cell result;
    if (!strcmp(list->content, "")) {
        if (list->first != NULL)
            return list->first;
        else
            return newCell();
    } else {
        result = newSymbol(list->content);
        return result;
    }
}

/**************************************
 * Function: quote(cons_cell list)
 * Function returning a pointer to a cons cell which will either contain a list or a symbol.
 * In case of symbol, the struct will contain two cons cell: one will contain symbol "#", the other will contain the symbol.
 * This will maintain our program's convention for a symbol and a list
 * For instance: (quote (a b)) will return (a b)
 *               (quote a) will return symbol a
***************************************/
cons_cell quote(cons_cell list) {
    cons_cell result;
    if (!strcmp(list->content, "")) {
        result = list->first;
    } else if (!strcmp(list->content, "()")) {
        result = list->first;
    } else {
        result = newSymbol(list->content);
    }
    return result;
}

/**************************************
 * Function: cons(cons_cell list1, cons_cell list2)
 * Function returning a pointer to a cons cell which will always contain a list representing concatenation of the two arguments
 * For instance: (cons (quote (a b)) (quote (e f))) will return ((a b) e f)
 *               (cons (quote a) (quote (b c))) will return (a b c)
***************************************/
cons_cell cons(cons_cell list, cons_cell environment) {
    cons_cell firstArg = evalHelper(list->first, environment);
    cons_cell secondArg;
    //in case the second argument is an actual list
    if (list->rest->first != NULL)
        secondArg = evalHelper(list->rest->first, environment);
    else //in case the second argument is just a symbol
        secondArg = NULL;
    //The result cons_cell will indicates the start of a list exclusively from the first argument list
    cons_cell result;
    cons_cell duplicate = copyList(firstArg);
    result = newCell();
    result->first = duplicate;
    cons_cell temp = result;
    while (temp->rest != NULL) {
        temp = temp->rest;
    }
    temp->rest = secondArg;
    return result;
}

/**************************************
 * Function: isNull(cons_cell list)
 * Function returning a pointer to a cons cell which will always contain either symbol #t or #f. "#t" will be returned when the argument list is empty, or a single
 * symbol,"#f" otherwise.
***************************************/
cons_cell isNull(cons_cell list) {
    if (list == NULL || !strcmp(list->content, "") || !strcmp(list->content, "#f") || !strcmp(list->content, "#t"))
        return newSymbol("#t");
    else
        return newSymbol("#f");
}

/**************************************
 * Function: equal(cons_cell list1, cons_cell list2)
 * Function returning a pointer to a cons cell containing symbol "#t" or "#f" representing the truth value if
 * two lists are equal.
 * Two lists are considered equal when they have exactly the same content (element, symbol, nested list, and size)
***************************************/
cons_cell equal(cons_cell list1, cons_cell list2) {
    cons_cell result;
    int isEqual = equalHelper(list1, list2);
    if (isEqual)
        result = newSymbol("#t");
    else
        result = newSymbol("#f");
    return result;
}

/**************************************
 * Function: append(cons_cell list)
 * Function returning a pointer to a cons cell which will always contain a list representing concatenation of the two lists
 * The parameter this function accepts is a cons_cell pointing to everything after the word "append".
 * For instance: (append (quote (a b)) (quote (c d))) -> append((quote(a b))(quote(c d)))
***************************************/
cons_cell append(cons_cell list, cons_cell environment) {
    cons_cell firstArg = evalHelper(list->first, environment);
    if (!strcmp(firstArg->content, "#")) {
        return newCell();
    }
    cons_cell secondArg;
    //in case the second argument is an actual list
    if (list->rest->first != NULL)
        secondArg = evalHelper(list->rest->first, environment);
    else //in case the second argument is just a symbol
        secondArg = NULL;
    cons_cell duplicate = copyList(firstArg);
    cons_cell temp;
    temp = duplicate;
    while (temp->rest != NULL) {
        temp = temp->rest;
    }
    temp->rest = secondArg;
    return duplicate;
}

/**************************************
 * Function: assoc(cons_cell symbol, cons_cell list)
 * Function returning a pointer to a cons cell which will contain the list with first element as the symbol.
 * In case there are multiple lists that have the symbol as the first element, the first list encountered will be returned
 * The parameter this function accepts two parameters: the symbol, and a nested list
 * For instance: (assoc (quote a) (quote ((a b) (b c) (c d)))) -> return (a b)
***************************************/
cons_cell assoc(cons_cell symb, cons_cell list) {
    cons_cell temp;
    temp = list;
    char* symbol = symb->rest->content;
    while (temp != NULL) {
        if (temp->first != NULL && !strcmp(temp->first->content, symbol))
            return temp->first;
        temp = temp->rest;
    }
    return newSymbol("#f");

}

/**************************************
 * Function: cond(cons_cell list)
 * Conditional function which contains paris of (condition) and (operation) if that condition is true
 * The parameter it accepts is the cons_cell pointing to the rest of content after the word "cons"
***************************************/
cons_cell cond(cons_cell list, cons_cell environment) {
    cons_cell temp;
    temp = list;
    while (temp != NULL) {
        if (!strcmp(temp->first->content, "#t")) { //#t case
            return evalHelper(temp->first->rest->first, environment);
        }
        cons_cell condition = evalHelper(temp->first->first, environment);
        if (!strcmp(condition->rest->content, "#t")) {
            return evalHelper(temp->first->rest->first, environment);
        }
        temp = temp->rest;
    }
    return NULL;
}

/**************************************
 * Function: define(char* name, cons_cell value)
 * This function helps to assign a variable with value. Value can be any expression and will always be evaluated.
 * However, the name variable has to be a string. The assignment table is stored through a global variable @var environment
 * This function will return a cons_cell with content is the name variable
***************************************/
cons_cell define (char* name, cons_cell value) {
    if (globalEnvironment == NULL)
        globalEnvironment = newCell();
    //to create the cons parameter
    cons_cell listCreated = newCell();
    listCreated->first = helperDefine(name, value);
    listCreated->rest = newCell();
    listCreated->rest->first = globalEnvironment;
    globalEnvironment = cons(listCreated, globalEnvironment);
    return newSymbol(name);
}
cons_cell defineFunction(char* name, cons_cell definition) {
    if (globalEnvironment == NULL)
        globalEnvironment = newCell();
    //to create the cons parameter
    cons_cell listCreated = newCell();
    listCreated->first = helperDefineList(name, definition);
    listCreated->rest = newCell();
    listCreated->rest->first = globalEnvironment;
    globalEnvironment = cons(listCreated, globalEnvironment);
    return newSymbol(name);
}

cons_cell defineLocal(char* name, cons_cell value, cons_cell envi) {
    cons_cell pair = helperDefineList(name, value);
    //to create the cons parameter
    cons_cell listCreated = newCell();
    listCreated->first = helperDefine(name, value);
    listCreated->rest = newCell();
    listCreated->rest->first = envi;
    envi = cons(listCreated, envi);
    return envi;
}
/**************************************
 * Function: eval(cons_cell list)
 * Function returning a pointer to a cons cell which will be the result of basic built in functions: car, cdr, cons, quote, symbol?
 * eval() is able to handle nested functions such as:
 *          (func (func (func (func (a b c)))))
 * on condition that nested functions do not return a truth value such as #t or #f
 * In addition, conditions for each function are also checked here. Please view evaluate.h for more detailed documentation
 * regarding conditions and corner cases of these built in functions
 * Conditions such as: appropriate arguments is checked here not to crash the program when users input wrong arguments for these functions.
***************************************/
cons_cell evalHelper(cons_cell list, cons_cell environment) {
    cons_cell result;
    //there are two cases of argument
    //arg for a procedure is just a symbol
    if (strcmp(list->content, "exit") && (list->rest != NULL && list->rest->first == NULL)) {
        if (!strcmp(list->content, "exit")) {
            result = newCell();
            result->content = "Have a nice day!";
            return result;
        }
        cons_cell isDefined;
        cons_cell symbolTemp = newSymbol(list->rest->content);
        isDefined = assoc(symbolTemp, environment);
        if (strcmp(isDefined->content, "#") != 0) {
            if (!strcmp(list->content, "#")) {//in case when input is a symbol
                if (isDefined->rest->first != NULL)
                    return isDefined->rest->first;
                return isDefined->rest;
            }
            //replace the symbol with the actual value to pass into eval()
            cons_cell calTemp = newCell();
            calTemp->content = list->content;
            calTemp->rest = isDefined->rest;
            if (list->rest->rest != NULL) {//when function has two arguments
                if (list->rest->rest->first != NULL) {
                    symbolTemp = evalHelper(list->rest->rest->first, environment);
                    calTemp->rest->rest = newCell();
                    calTemp->rest->rest->first = symbolTemp;
                    return (evalHelper(calTemp, environment));
                } else {
                    symbolTemp = newSymbol(list->rest->rest->content);
                    isDefined = assoc(symbolTemp, environment);
                    calTemp->rest->rest = isDefined->rest;
                    return (evalHelper(calTemp, environment));
                }

            }
            return(evalHelper(calTemp, environment));
        }
        if (!strcmp(list->content, "symbol?")) {
            return symbol(newSymbol(list->rest->content));
        } else if (!strcmp(list->content, "quote")) {
            return quote(list->rest);
        } else if (!strcmp(list->content, "define")) {
            return define(list->rest->content, list->rest->rest->first);
        } else if (!strcmp(list->content, "null?")) {
            return isNull(list->rest);
        } else
            return list;
    } else { //arg for procedure is a list or nested list
        //base case for recursion
        if (!strcmp(list->content, "quote")) {
            return quote(list->rest);
        } else if (!strcmp(list->content, "car")) {
            result = evalHelper(list->rest->first, environment);
            return car(result);
        } else if (!strcmp(list->content, "cdr")) {
            result = evalHelper(list->rest->first, environment);
            return cdr(result);
        } else if (!strcmp(list->content, "cons")) {
            return cons(list->rest, environment);
        } else if (!strcmp(list->content, "symbol?")) {
            result = evalHelper(list->rest->first, environment);
            return symbol(result);
        } else if (!strcmp(list->content, "exit")) {
            result = newCell();
            result->content = "Have a nice day!";
            return result;
        } else if (!strcmp(list->content, "append")) {
            return append(list->rest, environment);
        } else if (!strcmp(list->content, "null?")) {
            result = evalHelper(list->rest->first, environment);
            return isNull(result);
        } else if (!strcmp(list->content, "equal?")) {
            cons_cell firstArg, secondArg;
            if (list->rest->first == NULL)
                firstArg = evalHelper(list->rest, environment);
            else
                firstArg = evalHelper(list->rest->first, environment);
            if (list->rest->rest->first == NULL)
                secondArg = evalHelper(list->rest->rest, environment);
            else
                secondArg = evalHelper(list->rest->rest->first, environment);
            return equal(firstArg, secondArg);
        } else if (!strcmp(list->content, "cond")) {
            return cond(list->rest, environment);
        } else if (!strcmp(list->content, "assoc")) {
            cons_cell symbol = evalHelper(list->rest->first, environment); //return a symbol (# -> string)
            cons_cell comparedList = evalHelper(list->rest->rest->first, environment); //return a list to associate
            return assoc(symbol, comparedList);
        } else if (!strcmp(list->content, "define")) {//when user define a procedure
            return defineFunction(list->rest->first->content, list);
        } else if (strcmp(assoc(newSymbol(list->content), globalEnvironment)->content, "#") != 0) {
            //cons to the global environment
            cons_cell value = assoc(newSymbol(list->content), globalEnvironment)->rest->first;
            //create local environment
            cons_cell localEvn = newCell();
            //evaluate actual arguments and cons it with local environment
            cons_cell nameArgs = car(cdr(value));
            cons_cell temp = nameArgs->rest;
            cons_cell temp2 = list->rest;
            while (temp != NULL) {
                if (temp2->first == NULL)
                    return newCell();
                else {
                    localEvn = defineLocal(temp->content, temp2->first, localEvn);
                }
                temp2 = temp2->rest;
                temp = temp->rest;
            }
            //evaluate in the body of functions
            return evalHelper(value->rest->rest->first, localEvn);
        } else { //in case users input non-built-in procedure
            return list;
        }
    }
}
cons_cell eval(cons_cell list) {
    return evalHelper(list, globalEnvironment);
}

//(member (define (member E L) (cond ((null? L) #f) ((equal? E (car L)) L) (else (member E (cdr L))))))