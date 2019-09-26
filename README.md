# CS170-Partial-Scheme-Interpreter
A parser for a subset of Scheme.
# Internal Representation of Lists
         Cons_cell which is comprised of a pointer to a next cell and the string content
# Functions evaluated
scheme> (quote (a b c))

scheme> a

scheme> (car (a b c)) 

scheme> (cdr (a b c))

scheme> (cons (quote a) (quote (b c)))

scheme> (symbol? a)

scheme> (symbol? (quote (a b c)))
 
scheme> (append (quote (a b)) (quote (c d)))

scheme> (equal? (quote (a (b c) d)) (quote (a (b c) d)))

scheme> (assoc (quote joan) (quote ((john smith) (joan doe) (marcia law))))

scheme> (define l1 (quote (a b c)))

# Check Scheme for function definitions
