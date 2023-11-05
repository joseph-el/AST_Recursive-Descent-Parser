# SYNTAX RULES 

````
* "(": LPAR
    - left  : BGN  | - | + | * | / | % | DIGIT | ^ | )
    - right : DIGIT | (

* ")": RPAR
    - left  : ) | DIGIT | !
    - right : ) | ( |  ^ | - | + | * | / | % | ! | DIGIT | END

* "!":
    - left  : ) | DIGIT
    - right : END | ^ | - | + | * | / | % | )

* "DIGIT":
    - left  : BGIN | ^ | - | + | * | / | % | ( | )
    - right : END | ! | ( | ) | ^ | - | + | * | / | %

* "* / + - % ^":
    - left  : DIGIT | ) | !
    - right : ( | DIGIT

````