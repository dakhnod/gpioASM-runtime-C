# gpioASM runtime for C/C++
Platform agnostic runtime for [gpioASM bytecode](https://github.com/dakhnod/gpioASM/tree/main)

## Running the example
To test the example on any system with a compiler, just run
```
gcc example.c gpioasm.c -o example
./example
```

If you want to enable debug and error logging, you need to inject the apropriate functions by using defines:

```
gcc example.c gpioasm.c -o example -DGPIOASM_LOG_DEBUG=printf -DGPIOASM_LOG_ERROR=printf -DGPIOASM_LOG_IMPORT="<stdio.h>"
./example
```
