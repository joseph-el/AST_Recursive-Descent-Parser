
# SYNTAX RULES

````
* "(": LPAR
    - left  : BGN  | - | + | * | / | % | DIGIT | ^ | )
    - right : DIGIT | (

* ")": RPAR
    - left  : ) | DIGIT | !
    - right : ( |  ^ | - | + | * | / | % | ! | DIGIT | END

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

# Grammar <::>

``the proper precedence and associativity ``

< > ::= <term> | <term> "+" <expression> | <term> "-" <expression>

<term> ::= <factor> | <factor> "*" <term> | <factor> "/" <term> | <factor> "%" <term>

<factor> ::= <unary_expression> | <unary_expression> "^" <factor>

<unary_expression> ::=  <primary> "!"

<primary> ::= "(" <expression> ")" | <number>

<number> ::= <sign>? <digit> #base case
            | <digit> <number> // recursive rule

<sign>   ::= '+' | '-'

<digit>  ::= 0 ... 9









##          () * ^ % / + - !    BGN END 
            
   `` begin - + * / % digit  ^ ) ``  <<left>> '(' <<right>> `` ( digit ``

   ``  ) digit ! ``                  <<left>> ')' <<right>> `` (  ^ - + * / % ! digit END ``

                 `` ) digit`` <<left>> ! <<right>> ``END ^ - + * / % (``

               `` BGIN  ^ - + * / % ( )``  <<left>> digit <<right>> `` !  END ( )  ^ - + * / % ``

               `` digit ) ! ``    <<left>> * / + - % ^ <<right>>   `` ( digit ``

    	if (size && SIZE_MAX / size < n)
		return (NULL);






// Assume the input is "2 + 3 * (4 - 1)"

// Lexer Output (Tokenization):

//                  (DIGIT, 2) (ADD, -1) (DIGIT, 3) (MUL, -1) (LPAR, -1) (DIGIT, 4) (SUB, -1) (DIGIT, 1) (RPAR, -1) (END, -1)

// Parser:
// 1. Call expression():
//    - Call term():
//      - Call factor():
//        - Call unaryExpression():
//          - Call primary():
//            - Match DIGIT: Create AST node (DIGIT, 2)
//      - Match ADD: Create AST node (ADD, -1)
//      - Call term():
//        - Call factor():
//          - Call unaryExpression():
//            - Call primary():
//              - Match DIGIT: Create AST node (DIGIT, 3)
//          - Match MUL: Create AST node (MUL, -1)
//          - Call term():
//            - Call factor():
//              - Call unaryExpression():
//                - Call primary():
//                  - Match LPAR: Create AST node (LPAR, -1)
//                  - Call expression():
//                    - Call term():
//                      - Call factor():
//                        - Call unaryExpression():
//                          - Call primary():
//                            - Match DIGIT: Create AST node (DIGIT, 4)
//                        - Match SUB: Create AST node (SUB, -1)
//                        - Call factor():
//                          - Call unaryExpression():
//                            - Call primary():
//                              - Match DIGIT: Create AST node (DIGIT, 1)
//                          - Create AST node (SUB, -1) with left and right children
//                      - Create AST node (SUB, -1) with left and right children
//                    - Match RPAR: Create AST node (RPAR, -1)
//                  - Create AST node (MUL, -1) with left and right children
//              - Create AST node (MUL, -1) with left and right children
//            - Create AST node (MUL, -1) with left and right children
//        - Create AST node (ADD, -1) with left and right children
//    - Create AST node (ADD, -1) with left and right children

// The resulting AST represents the hierarchical structure of the input expression.
