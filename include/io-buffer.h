#include <stdio.h>
#include <vector>
#include <string>

#ifndef IO_BUFFER_INCLUDED_H
#define IO_BUFFER_INCLUDED_H

namespace IOBuffer {
    class IOWriter {
    public:
        virtual int write(char *buffer, int length) = 0;
    };

    class IOReader {
    public:
        virtual int read(char *buffer, int length) = 0;
    };

    class IOBuffer : public IOReader, public IOWriter {
    };

    class IOFileReader : public IOReader {
    public:
        IOFileReader(char *fileName);
        IOFileReader(const char* fileName);
        IOFileReader(std::string fileName);
        ~IOFileReader();
        int read(char *buffer, int length);
    private:
        char *fileName;
        FILE *hFile;
        FILE *getHandler();
    };

    class IOMemoryBuffer : public IOBuffer {
    public:
        IOMemoryBuffer();
        IOMemoryBuffer(int ioMemoryBlockSize);
        ~IOMemoryBuffer();
        int write(char *buffer, int length);
        int read(char *buffer, int length);
        void setPosition(int position);
        int length();
    protected:
        std::vector<char *> blocks;
        int ioMemoryBlockSize;
        int currentBlockNumber;
        int writePosition;
        int readPosition;
    };

} // IOBuffer

#endif /* IO_BUFFER_INCLUDED_H */
