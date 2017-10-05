This executable is a simple calculator implementation, based on the calculator0
calculator08buggy.cpp file from Chapter 7 of "Programming Principles and 
Practice using c++" by Bjarne Stroustrup.

The mathematical operations that are supported by this calculator are:
    addition ; x+y
    subtraction : x-y 
    multiplication : x*y
    division : x/y
    factorial : x!
    modulo : x%y
    power : x^y
    sine function (argument in radians) : sin(x) 
    square root : sqrt(x)


For % and !, double values will be converted to integers. 

Pressing [Enter] yields evaluation of the expression on the current line. 
Multiple expression can be separated by ';' if needed. The result of the last 
successful evaluation is stored in a variable called "ans".

Users can also define variables themselves, using the command 
"let <var_name> = <var_value" for modifiable variables, and 
"let const <var_name> = <var_value>" for constant variables.

Stored variables can be displayed with typing "showvar" followed by [Enter].
A help message can be displayed with typing "help" followed by [Enter].
To exit the calculator, type "quit" followed by [Enter].

If an exception occurs or no new prompt is displayed, type a random 
expression followed by ';' and [Enter] to continue entering input.

