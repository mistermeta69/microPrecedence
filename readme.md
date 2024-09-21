Table-based shift/Reduce parser for expressions
Based on Aho and Ullman description in Dragon book

This code implements a precedence parser for basic arithmetic expressions. It's a shift-reduce parser that can handle addition, subtraction, multiplication, division, and parentheses. Let's break down the main components and functionality of this code:

## Main Components

1. Token Recognition (`gettoken` function)
2. Expression Evaluation (`eval` function)
3. Operator and Operand Stacks
4. Precedence Tables
5. Parsing Algorithm (`calc` function)

## Functionality Breakdown

### 1. Token Recognition

The `gettoken` function reads input characters and converts them into tokens:
- Numbers (0-9) are converted to their integer values
- Operators (+, -, *, /) are assigned specific token codes
- Parentheses and end-of-input are also recognized

### 2. Expression Evaluation

The `eval` function performs basic arithmetic operations based on the operator and two operands.

### 3. Operator and Operand Stacks

Two separate stacks are maintained:
- `opstk` for operators
- `numstk` for numbers (operands)

Each stack has its own push and pop operations.

### 4. Precedence Tables

Two arrays define the precedence rules:
- `prstk`: Precedence of the operator on top of the stack
- `prinp`: Precedence of the input operator

These tables determine whether to shift, reduce, or discard tokens during parsing.

### 5. Parsing Algorithm

The `calc` function implements the main parsing algorithm:
1. Get the next token
2. If it's a number, push it onto the number stack
3. If it's an operator, compare its precedence with the top of the operator stack:
   - If input precedence is higher: shift (push onto operator stack)
   - If precedences are equal: discard both (usually for parentheses matching)
   - If stack precedence is higher: reduce (evaluate top operation and push result)
4. Repeat until end of input is reached and all operations are evaluated

## Usage

The `main` function calls `calc` and prints the result of the evaluated expression.

## Limitations and Potential Improvements

1. Error handling is minimal
2. Only single-digit numbers are supported
3. The code uses some outdated C practices (e.g., `<conio.h>`)
4. Input is limited to a single line

To improve this parser, you could add better error handling, support for multi-digit numbers, and modernize the C code style. Additionally, extending it to handle more complex expressions or different types of operations could make it more versatile.
