## Overview

This repository contains an implementation of a ```Recursive Descent Parser (RDB)``` for arithmetic expression language using ```C++17```, along with the construction of ```Abstract Syntax Trees (AST)``` from parsed expressions. The grammar and syntax rules defined here serve as the foundation for parsing mathematical expressions.

<img width="1131" alt="rdb" src="https://github.com/joseph-el/Recursive-Descent-Parser-AST/assets/80905157/9bce961c-1f39-4f1b-a196-6f5600b23a85">

## BNF Grammar

The grammar of the expression language is defined as follows:

```plaintext
<expression> ::= <term> | <term> "+" <expression> | <term> "-" <expression>

<term> ::= <factor> | <factor> "*" <term> | <factor> "/" <term> | <factor> "%" <term>

<factor> ::= <unary_expression> | <unary_expression> "^" <factor>

<unary_expression> ::=  <primary> "!"

<primary> ::= "(" <expression> ")" | <number>

<number> ::= <sign>? <digit> #base case | <digit> <number> // recursive rule

<sign> ::= '+' | '-'

<digit> ::= 0 ... 9
```

## Syntax Rules

The syntax rules determine the order and associations of the operators and operands:

- **LPAR and RPAR:** Define the rules for parentheses.
- **! (Factorial):** Specifies the rules for the factorial operation.
- **DIGIT:** Describes the rules for numeric literals.
- **Operators:** (* / + - % ^) Outline the precedence and associativity of arithmetic operators.

```plaintext
* "(": LPAR
    - left  : BGN  | - | + | * | / | % | DIGIT | ^ | ) | (
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
```

## RDB Functions

The Recursive Descent Parser is implemented through the following functions:

```cpp
ast* parser();
private:
    ast* expression();
    ast* term();
    ast* factor();
    ast* unary_expression();
    ast* primary();
```

These functions handle the recursive descent parsing process, breaking down expressions into their constituent parts and building the corresponding Abstract Syntax Tree.

## AST Evaluation

The AST can be evaluated using the `eval` function:

```cpp
    void eval(ast* root);
```

## Getting Started

To build and run the project, follow these steps:

1. Compile the project using `make`.
2. Execute the generated `rdb_exec` executable.
3. Enter mathematical expressions to be parsed and evaluated.

## Command Line Features

The command-line interface includes the following features:

- Command interpretation for `"clear"` `"reset"` `"exit"`.
- Integration with the `readline` library for command history.
