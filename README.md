# cppchallenge
An implementation of a simple 2D Matrix library with testing.

## How to build/run
Simply create a build directory and run `cmake`, e.g.:

```
> mkdir build
> cd build && cmake .. && make
```

To run all tests, run `ctest` from the build directory:
``` 
> cd build && ctest 
```

## Structure of testfiles
To run the tests, one needs testfiles. The structure of the testfile is described in the [testfile.template](testfile.template) file.