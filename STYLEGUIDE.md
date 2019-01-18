# TimberWolf Style Guide
- version: **1.0**
- date: **2018-12-30**
- by: **Danger Interactive LLC**

## C++ Coding Style
The primary programming language used in the TimberWolf engine is C++. The majority of this code will be part of the engine API, and as such, there are strict style rules.

### C++ Version
C++ code should target standard C++17. This will advance in the future, however code written with a previous version does not need to be updated, but it is recommended to update code at your convenience. Non-standard extensions are not allowed. Compiler-specific code should be avoided at all costs, but if necessary, should be inside a macro that limits it to that specific compiler.

### Source Files
C++ source files should use the `.cpp` file extension. Source files should contain all implementation code, except in the case of template or header-only libraries.

### Header Files
C++ header files should use the `.hpp` file extension. Header files should contain declarations for all classes, methods, member variables, and functions that are part of the engine API.

### Include Guards
Include guards should be included in every C++ header file. Include guards should always be implemented as follows:
```c++
#include XXX_XXX_XXX
#define XXX_XXX_XXX

// declare stuff

#endif XXX_XXX_XXX
```

The naming convention for the include guards should be as follows:
- Packages (headers that include a group of other headers):
  - `TW_PACKAGE_PACKAGENAME` where "PACKAGENAME" is the name of the package
- Class declarations:
  - `TW_CLASS_CLASSNAME` where "CLASSNAME" is the name of the class
- Procedural functions:
  - `TW_FUNCTION_FUNCTIONGROUPNAME` where "FUNCTIONGROUPNAME" is the name of the group of functions

Note that "tw" was assumed to be the namespace of the headers. If a different namespace was used for some reason, please replace "TW" with the correct namespace.
