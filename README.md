# l-systems
Simple l-systems grammar parser and string generator

This is a simple command line program written in C++17 that takes in a grammar file, an iteration count and an axiom and generates a string from the grammar rules. It also allows you to create stochastic l-systems.

### Building & Running
This project was creating using CMake, so clone the project, then from its root directory run:
``` Bash
$ mkdir build
$ cd build
$ cmake ..
$ make
```

The project takes 3 command line arguments in this order: `path-to-grammar`, `iteration-count`, `axiom`.

- **path-to-grammar**: The path to your grammar file. These must be some kind of text file, .txt works fine.
- **iteration-count**: The number of iterations to apply to the string.
- **axiom**: The starting string.

To run:
``` Bash
$ ./l_system_parser <path> <iter-count> <axiom>
```

### Grammar Format & Rules

Grammars are parsed according to the following grammar (its grammars all the way down):
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
- To specify different probabilities for a variable, use the syntax: `ID (Probability) -> Production`. If no probability is specified, the probability for the rule is defaulted to 1.0. Probabilities aren't truly probabilities that must lie between 0 and 1, it's simply their ratios that matter. i.e. 
  ```
  X (0.5) -> abc
  X (0.5) -> xyz
  ```
  is the same as
  ```
  X (10) -> abc
  X (10) -> xyz
  ```
  both branches of X have a 50% change of being chosen during string generation.

#### Example - dragon_curve.txt
```
X -> X+YYF+
Y -> -FX-Y
```

## TODO
- Allow comments in grammars
- Allow context sensitive rules in grammars
- Create static library for embedding in other programs

