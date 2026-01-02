# Expression Calculator (A&DS) — Integer Infix → Postfix (RPN) (C++)

---
This project is an **integer expression calculator** written in **C++** for an Algorithms & Data Structures assignment.  
It reads expressions in **infix notation**, converts them to **postfix (RPN)**, and evaluates them using a **custom stack**.

Key requirement of the assignment: **no `std::string` and no STL containers**.  
All tokens are handled with fixed-size `char[]`, and the stack is implemented as a **singly-linked list** with manual memory management (`new/delete`).

### Supported syntax
**Operators** (integer arithmetic):
- `a + b`, `a - b`
- `a * b`, `a / b` (integer division like C/C++; division by zero is an error)

**Functions**
- `IF(a, b, c)` → if `a > 0` return `b`, else return `c`
- `N a` → unary negation (`-a`)
- `MIN(a1, a2, ...)` and `MAX(a1, a2, ...)` → variadic (any number of args)

**Parentheses**: `( ... )`  
Each input formula ends with a dot `.` and tokens are whitespace-separated.

### Output behavior
For each formula the program prints:
1. The expression in **postfix (RPN)** form
    - Each occurrence of `MIN`/`MAX` is printed as `MINk` / `MAXk`, where `k` is the number of arguments.
2. Before executing each operation, prints:
    - The operator/function name and the current content of the evaluation stack
3. The final result
4. If division by zero occurs: prints `ERROR` and moves to the next expression

### EXAMPLE

**INPUT:**
```
1
N ( ( MAX ( 0 , 1 ) + N ( 1 ) ) ) .
```

***OUTPUT:***
```
0  1  MAX2  1  N  +  N
MAX2 1 0
N 1 1
+ -1 1
N 0
0
```

### Algorithms & data structures
- **Shunting-Yard algorithm** for infix → postfix conversion (with support for functions and parentheses)
- Custom **linked-list stack**:
    - `push`, `pop`, `top`, `isEmpty`, `clear`, `print`
- Argument counting for variadic functions (`MIN`, `MAX`) performed **during conversion**, without storing the entire infix expression.

