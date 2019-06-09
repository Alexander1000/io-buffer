# io-buffer

Example how use it (iterate characters from `IOBuffer::IOReader`):
```c++
#include <iostream>
#include <io-buffer.h>

int main (int argc, char** argv) {
    IOBuffer::IOFileReader fileReader("some-file.txt");
    IOBuffer::CharStream charStream(&fileReader);
    std::cout << "First symbol: " << charStream.getNext() << std::endl;
    return 0;
}
```

Build library:
```shell
cmake .
make
make install
```
