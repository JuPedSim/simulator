# Coding Standards
Thank you for your interest in developing JuPedSim **simulator**

The following guidelines should help us to develop a consistent project. 
Please don't be put off by these guidelines as they are guidelines and not strict rules. 

### Contents

- [C++ Coding Guidelines](#c-coding-guidelines)
    - [Formatting](#formatting)
    - [Naming](#naming)
    - [Misc](#misc)
- [Python Coding Guidelines](#python-coding-guidelines)
- [General](#general)
    - [Commit Messages and Pull Requests](#commit-messages-and-pull-requests)
    - [Language](#language)


## C++ Coding Guidelines
JPS **simulator** is written in *modern* C++. Currently we stick to the 2017 Language Standard. 

### Formatting

The C++ code should be formatted using [clang-format](https://clang.llvm.org/docs/ClangFormat.html). 
The format configuration can be found in the [`.clang-format`](https://github.com/JuPedSim/simulator/blob/main/.clang-format) configuration file.

### Naming 

The C++ naming conventions for JPS **simulator** are the following: 

#### Classes, Structs, Enums and Typedefs
CamelCase

#### Functions and Methods
camelCase

#### Variables, Members and Parameters
lower_case
 
#### Global Constants and Macros
UPPER_CASE
 
#### Prefixes
Private and Protected Members: `m_`  
Function Parameters: `p_`
 
These conventions are enforced using clang-tidy's *readability-identifier-naming* checks. 
The configuration can be found in the [top level configuration file](https://github.com/JuPedSim/simulator/blob/main/cpp/.clang-tidy).

### Misc
The following additional guidelines should be used when developing code for JPS **simulator**: 

#### East Const
``` c++
int const int_var
Type const * const
```


#### Trailing Return Types
``` c++
auto getID() const -> int;
auto addPedestrian(Pedestrian const & p_pedestrian) -> void;
```

## Python Coding Guidelines
For python development [black](https://github.com/psf/black) should be used for formatting the code, as well as [isort](https://github.com/PyCQA/isort) for sorting of imports. 

Please stick to the following additional guidelines: 

- Use type hints (see [python documentation](https://docs.python.org/3/library/typing.html))

## General

### Commit Messages and Pull Requests
The commit message should consist of a short **title** and a **description** and should be written in present tense.
The title should be around **50 characters** and the description should be wrapped at **72 characters**. 
Please try to explain in details what you did and why.

For the Pull Request Message the same rules apply.
Please **squash your commits** in the Pull Request by content and **rebase on the main** branch before merging. 

### Language
Please use american English (en_US).
