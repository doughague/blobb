```
*****************************************************************
*                 /---\ |        /---\ /---\     Bleed          *
*                 |___/ | /---\  |___/ |___/     or             *
*                 |   \ | |   |  |   \ |   \     Be             *
*                 |___/ | \___/  |___/ |___/     Bled           *
*****************************************************************
```
# BloBB
Bleed or Be Bled: A command-line arena game.


## Authors
* Jason Torpy, Archbishop, full of crazy ideas
* Doug Hague, Lord Privy Seal, getting things done


## Features
* Writen in C/C++
* Command-line interface
* ASCII Text Combat
* Stochastic, Fighter-centric, scalable combat engine
* Expansive discoverable backstory and in-game history
* Super Fun!
* Don't steal our idea (unless you make it better and share; GNP-v3)


## Dependencies
* Standard [C/C++ libraries](http://www.cplusplus.com/reference/).
* A C++11 compliant compiler (~>=gcc-4.7 or ~>=clang-3.4).
* [CMake](http://www.cmake.org/) build tool.
* Optionally [Doxygen](http://www.stack.nl/~dimitri/doxygen/) 
  for making API documentation.


## Build
The build process follows the standard cmake paradigm.

### GNU/Linix, BSD, MacOS
From the blobb directory:
```
$ mkdir build
$ cd build
$ cmake ..
$ make
```
(One liner: `mkdir build; cd build; cmake ..; make;`)

There are, of course, graphical cmake utilities, but I don't know how to use them.

#### Developers
Developers should add `make debug` after the `cmake ..` command 
(don't forget to also `make`).

For a fresh build from within the build directory(!) use:
`rm -rf *; cmake ..; make debug; make -j4`

Note that you can use src/progs/sandbox.cxx to play/test your ideas 
while leaving the main program intact.

### MacOS
One can create an XCode project by using
`cmake -G Xcode ..`

### Windows
It just might work .. who knows? 


## Play
```
$ ./bin/blobb
```

# Contribute
Please consider contributing to this project.

Some things to do include:

* Basically, almost everything: this is the alpha version.
* ASCII graphics, Crypto, Bitcoin, arenas and combat fields

# License
This software is licensed under the 
[GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html), 
see [License.txt](https://github.com/doughague/blobb/blob/master/License.txt).

This software uses (and redistributes) the 
[cereal C++11 library for serialization](https://github.com/USCiLab/cereal) 
which is licensed under the [BSD license](http://opensource.org/licenses/BSD-3-Clause).

