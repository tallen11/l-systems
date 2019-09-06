# l-systems
Simple l-systems grammar parser and string generator

This is a simple command line program written in C++17 that takes in a grammar file, an iteration count and an axiom and generates a string from the grammar rules. It also allows you to create stochastic l-systems (https://en.wikipedia.org/wiki/L-system).

![Demo](demo/demo_gif.gif)

### Building & Running
This project uses CMake, so clone the project, then from its root directory run
``` Bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

The project takes 3 command line arguments in this order: `path`, `iter-count`, `axiom`.

- **path**: The path to your grammar file. Grammars must be some kind of text file, .txt works fine.
- **iter-count**: The number of iterations to apply to the string.
- **axiom**: The starting string.

To run:
``` Bash
$ ./l_system_parser <path> <iter-count> <axiom>
```

### Grammar Format & Rules

Grammars are parsed according to the following grammar (it's grammars all the way down)
```
Grammar -> Rule*
Rule -> ID '->' Production
      | ID '(' Probability ')' '->' Production

Production -> ID+
ID -> <character>
Probability -> <number>
``` 
- IDs can only be a single character long as of now.
- The order of rules specified in your grammars doesn't matter.
- Rules have the following format: `ID -> Production`
- To specify different probabilities for a variable, use the syntax: `ID (Probability) -> Production`. If no probability is specified, the probability for the rule is defaulted to 1. Probabilities aren't truly probabilities that must lie between 0 and 1, rather it's their ratios that matter. i.e. 
  ```
  X (0.5) -> abc
  X (0.5) -> xyz
  ```
  is the same as
  ```
  X (10) -> abc
  X (10) -> xyz
  ```
  both branches of X have a 50% change of being chosen during string generation. Going further, a rule with only one branch specified will have a 100% chance of being chosen (since it's the only branch), regardless of the given probability.

#### Example
Grammar *dragon_curve.txt*
```
X -> X+YYF+
Y -> -FX-Y
```
Run
``` Bash
$ ./l_system_parser dragon_curve.txt 4 FX
```
Output

```
FX+YF++-FX-YF++-FX+YF+--FX-YF++-FX+YF++-FX-YF+--FX+YF+--FX-YF+
```

You can then use the resulting strings anywhere you want. For example, this [Processing Python](https://py.processing.org/) script will draw the actual dragon curve based on the generated string
``` Python
# Our generated string
L = "FX+YF++-FX-YF++-FX+YF+--FX-YF++-FX+YF++-FX-YF+--FX+YF+--FX-YF+"

def setup():
    size(256, 256)
    
    step_size = 20.0
    angle = 0.0
    pos = PVector(width / 2.0, height / 2.0)
    
    global L
    for c in L:
        if c == "F":
            next = PVector(pos.x + step_size*cos(angle), pos.y + step_size*sin(angle))
            line(pos.x, pos.y, next.x, next.y)
            pos = next
        elif c == "-":
            angle += PI / 2.0
        elif c == "+":
            angle -= PI / 2.0
```
![Generated Dragon Curve](demo/output.png)

---
### TODO
- Disallow duplicate rules in grammars.
- Allow comments in grammars.
- Allow context sensitive rules in grammars.
- Build static library for embedding in other programs.
- Use better RNG than rand().

