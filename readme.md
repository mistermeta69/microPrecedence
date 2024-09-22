Table-based shift/Reduce parser for expressions
Based on Aho and Ullman description in Dragon book

Can handle addition, subtraction, multiplication, division, and parentheses. 

## Main Components

1. Token handling (`gettoken` function)
2. Operator and operand stacks
3. Precedence tables
4. Evaluation function
5. Main parsing algorithm (`calc` function)

## Functionality Breakdown

### 1. Token Handling

The `gettoken` function reads input characters and converts them into tokens:
- Numbers (0)
- Operators (+, -, *, /)
- Parentheses
- End of input (DONE)

### 2. Stacks

Two stacks are used:
- `opstk`: Operator stack
- `numstk`: Operand (number) stack

### 3. Precedence Tables

Two arrays define the precedence rules:
- `prstk`: Precedence of the operator on top of the stack
- `prinp`: Precedence of the input operator

### 4. Evaluation

The `eval` function performs the actual arithmetic operations.

### 5. Parsing Algorithm

The `calc` function implements the main parsing algorithm:
1. Read a token
2. If it's a number, push it onto the number stack
3. If it's an operator:
   - If input precedence > stack precedence: shift (push onto operator stack)
   - If input precedence = stack precedence: discard both (for matching parentheses)
   - If input precedence < stack precedence: reduce (evaluate top of stack)

## How It Works

1. The parser reads the input expression character by character.
2. It builds numbers from consecutive digits.
3. For operators and parentheses, it compares their precedence with the top of the operator stack.
4. Based on the precedence comparison, it decides to shift, reduce, or discard.
5. When reducing, it pops two numbers and an operator, evaluates them, and pushes the result back.
6. This process continues until the entire expression is parsed and evaluated.

## Limitations and Potential Improvements

1. No error handling for invalid expressions
2. Limited to integer arithmetic
3. No support for unary operators (like negation)
4. No support for floating-point numbers
5. Input is limited to a single line

Overall, this is a functional implementation of a precedence parser for basic arithmetic expressions, suitable for educational purposes or as a starting point for a more robust expression evaluator.