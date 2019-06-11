//
// Created by bradley on 4/10/18.
//

#ifndef FINALPROJECT_EVALUATE_H
#define FINALPROJECT_EVALUATE_H

#include "parser.h"

/****************************************************************
 File: evaluate.h
 ----------------
 This is the interface for a evaluation, a part of Scheme.
 It has only one operation eval which can handle built-in functions: cons, car, cdr, symbol?, quote, and exit.
 This function will return a pointer to a cons_cell
 Parameter: a list built from user input
 Call this function to evaluate an expression from user:
        cons_cell result = eval(Expression)
 The result will behave as expected in Scheme when arguments passed in are appropriate:
    For cons:
        _If arguments are two list, or a symbol and a list, then eval will return a list concatenation of two lists, or a symbol and a list
        _Otherwise,
            +If second arg is a symbol, eval will return a list of two symbols and a # in between to indicate that
            the second argument should be a list, in lieu of a symbol
            +If second arg is "#t" or "#f", eval will return a list containing of the first argument
    For car:
        _If argument is a list, eval will return the first element of that list
        _Otherwise,
            +If argument is a symbol, "#" will be return to indicate that the argument should be a list (and user input is a symbol)
    For cdr:
        _If argument is a list, eval will return the list containing of all elements except the first one
        _If argument is a list with only one element, eval will return an empty list.
        _If argument is a symbol, eval will return a symbol "#" to indicate that the argument should be a list (instead of a symbol)
    For quote:
        _Eval will return exactly the argument; a list if argument is a list, or a symbol if argument is a symbol
    For symbol?
        _Eval will return "#t" if the argument is actually a symbol, an empty list otherwise
    For exit
        _This function requires no argument
        _Eval will return a list with one symbol "Have a nice day!"
    For append:
        _Eval only accept two lists to append. Otherwise, it will return an empty list or a list (symbol # symbol) to indicate
        that the second argument is a symbol instead of a list
    For null?:
        _Eval will return "#t" is that is an empty list, "#f" otherwise
    For equal? :
        _Eval will accept two arguments. They can be symbols or lists.
        _Eval will only return true if the two arguments are exactly the same, to the deepest level
    For assoc:
        _This has two arguments, the first of which is a symbol, the second a so-called "association list".
        _It returns the pair associated with the symbol, and #f if the symbol is not the first element of any pair.
    For cond:
        _The multiple-alternative conditional.
        _This will return the result of the expression whose condition is true
        _If none of the conditions is true, the evaluated result of the base case will be returned
    For define:
        _This return the name that associated with the value
 ****************************************************************/
cons_cell eval(cons_cell list);
cons_cell evalHelper(cons_cell list, cons_cell environment);
#endif //FINALPROJECT_EVALUATE_H
