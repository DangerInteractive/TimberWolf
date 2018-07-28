# Contributing to TimberWolf

:tada::tada::tada: Thanks for contributing to TimberWolf and to the open source
game development community! :tada::tada::tada:

This document contains a collection of guidelines and rules concerning the
development and contribution to TimberWolf. If you have never contributed
before, please make sure to read through this guide to be sure you understand
the rules.

For those who regularly contribute, or who have contributed in the past, please
note that these guidelines and rules may change, so keep an eye out for updates
to this file and review any changes.


#### Table of Contents

[Code of Conduct](#code-of-conduct)

[Styleguides](#styleguides)
- [C++ Header Styleguide](#c++-header-styleguide)
- [C++ Source Styleguide](#c++-source-styleguide)



## Code of Conduct

This project and everyone participating in it is governed by the [TimberWolf
Code of Conduct](CODE_OF_CONDUCT.md). By participating, you are expected to
uphold this code. Please report unacceptable behavior to
[alex@dangerzonegames.com](mailto:alex@dangerzonegames.com).




## Styleguides

Code submitted to the TimberWolf project is expected to follow a series of
styleguides. If you submit a pull request, please make sure you've verified that
your code is following all of the styleguide rules. If your code is found to
violate any of them, your pull request may be rejected until fixed.

### C++ Header Styleguide

The following example header serves as the styleguide:

```c++
#define ANY "macros up here. Use all caps for title."

#ifndef TW_CLASS_CLASSNAME
#define TW_CLASS_CLASSNAME

#include <alphabetic-order>
#include <standard-library-stuff-first>

#include <alphabetic order/here-too.hpp>
#include <shared-library-stuff-second.hpp>

#include "alphabetic-order-also.hpp"
#include "TimberWolf-stuff-third.hpp"

// forward declarations
namespace tw {
    class CircularDependency;
}

namespace tw {
class ClassName : public ParentClass {

public:

    class NestedClassesHere {

    public:

        // ...

    }

    // typedefs here
    typedef TypeDefs GoHere;

    // constructors and destructor
    ClassName () = default; // if class is static only, make constructor PUBLIC, but DELETED!
    explicit ClassName (int); // make explicit if only one argument (unless genuinely interchangeable)
    ~ClassName () = default; // make virtual if class has virtual methods

    // always declare move constructor and copy assignment operator
    ClassName (ClassName&&) = default;
    ClassName& operator = (ClassName&&) = default;

    // always declare copy constructor and copy assignment operator
    ClassName (const ClassName&) = default;
    ClassName& operator = (const ClassName&) = default;

    // getters here
    int getMemberVariable () const;

    // setters here
    void setMemberVariable (int);

    // other methods here
    void doSomeMagic (const std::string&);

    // operators here
    bool operator == (const ClassName&);

protected:

    // if class is polymorphic, put most member variables here
    // but use private if possible

    // if class is not polymorphic, omit "protected:" entirely

private:

    // if class is not polymorphic, put all member variables here

    int m_memberVariable; // use "m_" prefix for all member variables
    std::mutex m_mutex_memberVariable

};
}

#endif
```

### C++ Source Styleguide

The following example source serves as the styleguide:

```c++
#include "../include/ClassName.hpp"
#include "../include/CircularDependency.hpp"

tw::ClassName::ClassName (int variable)
: m_memberVariable(variable), ParentClass() {};

int tw::ClassName::getMemberVariable () const {

    return m_memberVariable;

}
```
