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

    class IOFileWriter : public IOWriter {
    public:
        IOFileWriter(char* fileName);
        IOFileWriter(const char* fileName);
        IOFileWriter(std::string fileName);
        IOFileWriter(char* fileName, const char* mode);
        IOFileWriter(const char* fileName, const char* mode);
        IOFileWriter(std::string fileName, const char* mode);
        ~IOFileWriter();
        int write(char *buffer, int length);
    private:
        char* fileName;
        const char* mode;
        FILE* hFile;
        FILE* getHandler();
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

    class CharStream
    {
    public:
        CharStream(IOReader* reader);
        CharStream(IOReader* reader, int bufferSize);
        ~CharStream();
        char* getNext();
    private:
        void init();
        IOReader* reader;
        int bufferSize;
        char* currentBuffer;
        char* forwardBuffer;
        // текущая позиция для чтения
        int currentPosition;
        // позиция начала текущего блока
        int posCurrent;
        // позиция начала следующего блока
        int posForward;
        // признак конца потока
        bool eof;
        bool lastFrame;
    };
} // IOBuffer

#endif /* IO_BUFFER_INCLUDED_H */
