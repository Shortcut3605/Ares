# Ares
 This is the language that I am making as a side project -_-

 # Grammar

For all math, standard PEMDAS rules apply:
- expressions in parenthesis come first.
- exponents are evaluated next
- multiplication and division are done left to right.
- adding and subtracting is also done left to right.

*name* = *value* (Assigns variable *name* to *value*, creates variable *name* if it does not exist)

*name* = *name2* = *value* (Assigns variables *name* and *name2* to *value*, creates the variables if they dont exist. This can repeated for as many variables as necessary.)

*value* + (*name* = 10) (Creates or reassigns variable *name* with value 10 and adds it to *value*. This will not work without the parenthesis around *name* = 10)

*value* + (*name* = *name2* = 10) (Creates or reassigns variables *name* and *name2* with value 10 and add it to *value*)

# Supported Data Types
- integers
- floating points

