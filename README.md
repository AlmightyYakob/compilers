# Pascal Compiler Project

## Compiles Pascal to 32-bit AT&T Assembly
> To slay a dragon <br>
> The quest which seemed outlandish <br>
> Is now completed

### Tools required
* Bison
* Flex
* 32-bit gcc libraries

These can be installed with the commands:

```
sudo apt install bison flex
sudo apt install gcc-multilib
```

### What's working

#### Front-End
* Line numbering
* Two Styles of Comments
* Unlimited nesting of subprograms
* Array access on both sides of assignment
* Allow for statements
* Another loop construct (while)
* Visual Syntax Tree Printing
* Semantic Analysis
* Error Reporting

#### Backend (Code Generation)

* Input/Output statements
* Simple expressions (arithmetic and relational)
* Statements (assignment, conditional, loop)
* Nonlocal names: base frame pointer (static scope parent)
* Recursive routines
* Complex expressions (register spilling)
* Arrays (L-value, R-value, parameters, nonlocal)


### Left to do
* Floating point
* SLASH, AND, OR operators
