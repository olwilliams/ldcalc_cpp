# ldcalc_cpp
Ldcalc ported to C++. A linear dichroism simulator.
Owen Williams

1. Introduction
Ldcalc is a program that simulates the rotational diffusion of a protein embedded in a spherical membrane vesicle.
The original version was written in Matlab to study the linear dichroism observed in rhodopsin. However, the
simulation could take several minutes to an hour to completely run, so the C++ version was born.

2. Comparison to Matlab version
Advantages:
*Execution speed (~100 times faster on my machine)
*Free - no need to purchase a Matlab license!
Disadvanages:
*No built-in visualization or analysis - this must be done with a separate program

3. Compatibility
Ldcalc should be compatible with any machine capable of using C++. That being said, I do not have a Linux or OSX
system, so those setups are completely untested. I only have binaries for Windows, so for other architectures
you need to compile from source.

4. Usage
Run ldcalc.exe and follow the menu options. The results are saved to the current working directory, which should
be the same directory the executable is in. Results are saved as a column of text data in descending order.
