# SLC

SLC is a compiler. Tell our story here...

### Installation

The project uses CMake as a build tool. To build the `Makefile` out-of-source, run

```sh
$ mkdir build
$ cd build
$ cmake ..
```

Then, to build the `joosc` executable, run

```sh
$ make
```

The executable will be under the `bin` directory.

### Development

To run tests, go to build directory, run

```sh
$ ./bin/joosc-test
```

To submit a project to Marmoset, go to root directory, run

```sh
$ ./tools/submit.sh A1
```
