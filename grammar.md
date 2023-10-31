<digit>  ::= 0...9
<sign>   ::= '+' | '-'
<wspace> ::= '\r\t\f 32'

<number> ::= <sign>? <digit> #base case
            | <digit> <number> // recursive rule



