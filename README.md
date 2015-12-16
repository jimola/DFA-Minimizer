# DFA-Minimizer

This is my DFA Minimizer project for 15-354: Computational Discrete Math
I've already compiled this code, and the executable is in the a.out file.
If you want to compile it yourself, use C++11, and compile Partition.cpp, Minimize.cpp. DFAFactory.cpp, and DFA.cpp.
For instance, I compile this code by typing:
g++ -std=c++11 Partition.cpp Minimize.cpp DFAFactory.cpp DFA.cpp

I made an effort to understand both algorithms, and I was able to understand and implement Hopcroft's algorithm.
However, Valmari-Lehtinen has to be implemented in a specific way to achieve the better runtime. They spend much of their paper explaining its implementation, but their paper is so dense (or I am) that I could not implement it myself.
This is the reason for the awkward Valmari.cpp file; it is code from Valmari that I changed in some places to be compatible with the rest of this project.
Valmari's code is available at http://www.cs.tut.fi/~ava/DFA_minimizer.cc

Because of this problem, there is less uniformity between the implementations of Hopcroft and Valmari-Lehtinen than I would have liked.
I would have liked both implementations to use my Partition.cpp and the function called complete in Minimize.cpp
I still made an effort to make them uniform. Both implementations exclusively use the stack, vectors, and copy the DFA transitions at most once.
I do think that my implementation of Hopcroft is less memory-efficient than Valmari's implementation of his algorithm.

It looks like Valmari is anywhere from 1.25 to 4 times faster than Hopcroft. On the DFAs with lots of order, the factor is low, around 1.25, which I believe is caused by inferior implementation.
On DFAs with lots of randomness or DFAs that are already almost-minimal, the factor increases to around 4. I believe this is because Valmari-Lehtinen is just a more efficient algorithm.

For bugs or comments or other things, feel free to contact me, Jacob Imola, at jimola@andrew.cmu.edu. Thanks.