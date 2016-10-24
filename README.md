# larlite

## Building

Create a build directory somewhere NOT in the source tree, `cd` into it and cmake config via

~~~ bash
  cmake <path to larlite source>
~~~

or, utilize curses
~~~ bash
  ccmake <path to larlite source>
~~~

Then, make and install. The `-j 4` is added in to multithread the make command.

~~~  bash
make -j 4 install
~~~

Finally, the python path needs to be set to where the install was located.

~~~ bash
export PYTHON_PATH=<cmake install prefix>/python
~~~
