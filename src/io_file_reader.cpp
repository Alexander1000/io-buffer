#include <io-buffer.h>
#include <iostream>

namespace IOBuffer
{
    IOFileReader::IOFileReader(char * fileName) : IOReader() {
        this->fileName = fileName;
        this->hFile = NULL;
    }

    IOFileReader::IOFileReader(const char* fileName) : IOReader() {
        this->fileName = (char*) fileName;
        this->hFile = NULL;
    }

    IOFileReader::IOFileReader(std::string fileName) : IOReader() {
        this->fileName = (char*) fileName.c_str();
        this->hFile = NULL;
    }

    IOFileReader::~IOFileReader() {
        if (this->hFile != NULL) {
            fclose(this->hFile);
        }
    }

    int IOFileReader::read(char *buffer, int length) {
        hFile = this->getHandler();

        if (hFile == NULL) {
            return -1;
        }

        size_t size = fread(buffer, sizeof(char), length, hFile);
        return (int) size;
    }

    FILE* IOFileReader::getHandler() {
        if (this->hFile != NULL) {
            return this->hFile;
        }

        this->hFile = fopen(this->fileName, "r");
        return this->hFile;
    }
} // IOBuffer
