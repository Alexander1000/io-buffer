#include <io-buffer.h>

namespace IOBuffer
{
    IOFileWriter::IOFileWriter(char* fileName) : IOWriter() {
        this->fileName = fileName;
        this->hFile = nullptr;
        this->mode = "a+";
    }

    IOFileWriter::IOFileWriter(const char* fileName) : IOWriter() {
        this->fileName = (char*) fileName;
        this->hFile = nullptr;
        this->mode = "a+";
    }

    IOFileWriter::IOFileWriter(std::string fileName) : IOWriter() {
        this->fileName = (char*) fileName.c_str();
        this->hFile = nullptr;
        this->mode = "a+";
    }

    IOFileWriter::IOFileWriter(char* fileName, const char* mode) : IOWriter() {
        this->fileName = fileName;
        this->hFile = nullptr;
        this->mode = mode;
    }

    IOFileWriter::IOFileWriter(const char* fileName, const char* mode) : IOWriter() {
        this->fileName = (char*) fileName;
        this->hFile = nullptr;
        this->mode = mode;
    }

    IOFileWriter::IOFileWriter(std::string fileName, const char* mode) : IOWriter() {
        this->fileName = (char*) fileName.c_str();
        this->hFile = nullptr;
        this->mode = mode;
    }

    IOFileWriter::~IOFileWriter() {
        if (this->hFile != nullptr) {
            fclose(this->hFile);
        }
    }

    int IOFileWriter::write(char *buffer, int length) {
        hFile = this->getHandler();

        if (hFile == nullptr) {
            return -1;
        }

        size_t size = fwrite(buffer, sizeof(char), length, hFile);
        return (int) size;
    }

    FILE* IOFileWriter::getHandler() {
        if (this->hFile != nullptr) {
            return this->hFile;
        }

        this->hFile = fopen(this->fileName, this->mode);
        return this->hFile;
    }
} // IOBuffer
