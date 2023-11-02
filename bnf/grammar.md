# Grammar <::>
## ()

## ^
## - + Unary
## % / *
## + - binary 
## !



            
`` begin - + * / % digit  ^ ) ``  <<left>> '(' <<right>> `` ( digit ``

``  ) digit ! ``                  <<left>> ')' <<right>> `` (  ^ - + * / % ! digit END ``

`` ) digit`` <<left>> ! <<right>> ``END ^ - + * / % (``

`` BGIN  ^ - + * / % ( )``  <<left>> digit <<right>> `` !  END ( )  ^ - + * / % ``

`` digit ) ! ``    <<left>> * / + - % ^ <<right>>   `` ( digit ``



##          () * ^ % / + - ! BGN END 
            
#   `` begin - + * / % digit  ^ ) ``  <<left>> '(' <<right>> `` ( digit ``

#   ``  ) digit ! ``                  <<left>> ')' <<right>> `` (  ^ - + * / % ! digit END ``

#                 `` ) digit`` <<left>> ! <<right>> ``END ^ - + * / % (``

#               `` BGIN  ^ - + * / % ( )``  <<left>> digit <<right>> `` !  END ( )  ^ - + * / % ``

#               `` digit ) ! ``    <<left>> * / + - % ^ <<right>>   `` ( digit ``

    

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