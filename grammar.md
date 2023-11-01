# Grammar <::>
## ()
## ^
## - + Unary
## % / *
## + - binary 
## !


#      task: () * - + / % ^ ! BEGIN END number
#      unary:   + - ! digit
#      binary: * - / % ^

#         binary , '('  <  ``! + -``  > digit

#            < ``* - / % ^`` >
                                  


``the proper precedence and associativity ``

<expression> ::= <term> | <term> "+" <expression> | <term> "-" <expression>

<term> ::= <factor> | <factor> "*" <term> | <factor> "/" <term> | <factor> "%" <term>

<factor> ::= <unary_expression> | <unary_expression> "^" <factor>

<unary_expression> ::= <primary> | "-" <primary> | "+" <primary> | "!" <primary>

<primary> ::= "(" <expression> ")" | <number>

<number> ::= <sign>? <digit> #base case
            | <digit> <number> // recursive rule

<sign>   ::= '+' | '-'

<digit>  ::= 0 ... 9