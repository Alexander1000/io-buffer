#include <io-buffer.h>
#include <memory.h>
#include <iostream>

#define IO_MEMORY_BLOCK_SIZE 512

namespace IOBuffer
{
    IOMemoryBuffer::IOMemoryBuffer() : IOBuffer() {
        this->writePosition = 0;
        this->readPosition = 0;

        this->ioMemoryBlockSize = IO_MEMORY_BLOCK_SIZE;
        char *firstBlock = new char[this->ioMemoryBlockSize];
        this->blocks.clear();
        this->blocks.push_back(firstBlock);
        this->currentBlockNumber = 0;
    }

    IOMemoryBuffer::IOMemoryBuffer(int ioMemoryBlockSize) : IOBuffer() {
        this->writePosition = 0;
        this->readPosition = 0;

        this->ioMemoryBlockSize = ioMemoryBlockSize;
        char *firstBlock = new char[this->ioMemoryBlockSize];
        this->blocks.clear();
        this->blocks.push_back(firstBlock);
        this->currentBlockNumber = 0;
    }

    IOMemoryBuffer::~IOMemoryBuffer() {
        char *buffer = NULL;
        int size = this->blocks.size();

        for (int i = 0; i < size; ++i) {
            buffer = this->blocks.at(i);

            if (buffer != NULL) {
                delete buffer;
            }
        }

        this->blocks.clear();
    }

    int IOMemoryBuffer::write(char *buffer, int length) {
        int nearLimitBlock, localWriteIndex, leftSave, lengthForSave;

        int savedLength = 0;
        char *pBlock;

        while (savedLength < length) {
            // leftSave - осталось сохранить
            leftSave = length - savedLength;
            // lengthForSave - длина для сохранения
            lengthForSave = leftSave;

            nearLimitBlock = this->blocks.size() * IO_MEMORY_BLOCK_SIZE;
            localWriteIndex = this->writePosition % IO_MEMORY_BLOCK_SIZE;

            if (this->writePosition + leftSave > nearLimitBlock) {
                // осталось сохранить ещё больше лимита
                lengthForSave = nearLimitBlock - this->writePosition;
            }

            pBlock = this->blocks.at(this->currentBlockNumber);
            memcpy(pBlock + localWriteIndex, buffer, lengthForSave);
            this->writePosition += lengthForSave;

            if (this->writePosition % IO_MEMORY_BLOCK_SIZE == 0) {
                // если полностью заполнили блок, выделяем новый
                pBlock = new char[IO_MEMORY_BLOCK_SIZE];
                memset(pBlock, 0, sizeof(char) * IO_MEMORY_BLOCK_SIZE);
                ++this->currentBlockNumber;
                this->blocks.push_back(pBlock);
            }

            savedLength += lengthForSave;
        }

        return savedLength;
    }

    int IOMemoryBuffer::read(char *buffer, int length) {
        // прочитано данных
        int readLength = 0;
        // осталось прочитать
        int leftRead = 0;
        int currentReadBlock = 0;
        int lengthForRead = 0;

        int startCurrentBlock = 0, endCurrentBlock = 0;

        char *pBlock = NULL;

        if (length > this->writePosition) {
            length = this->writePosition;
        }

        while (readLength < length && this->readPosition < this->writePosition) {
            leftRead = length - readPosition;
            lengthForRead = leftRead;
            currentReadBlock = this->readPosition / IO_MEMORY_BLOCK_SIZE;
            // границы текущего блока
            endCurrentBlock = (currentReadBlock + 1) * IO_MEMORY_BLOCK_SIZE;
            startCurrentBlock = currentReadBlock * IO_MEMORY_BLOCK_SIZE;

            // если осталось прочитать больше чем данных в текущем блоке
            if (leftRead > endCurrentBlock - startCurrentBlock) {
                lengthForRead = endCurrentBlock - this->readPosition;
            }

            // читаем страницу данных
            pBlock = this->blocks.at(currentReadBlock);
            // копируем в буфер прочитанные данные
            memcpy(buffer + readLength, pBlock + (this->readPosition % IO_MEMORY_BLOCK_SIZE), lengthForRead);

            this->readPosition += lengthForRead;
            readLength += lengthForRead;
        }

        // set last byte to NULL
        buffer[readLength] = '\x00';

        return 0;
    }

    void IOMemoryBuffer::setPosition(int position) {
        this->readPosition = position;
    }

    int IOMemoryBuffer::length() {
        return this->writePosition;
    }
} // JsonStreamAnalyzer::Buffer
