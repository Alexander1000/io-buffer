namespace IOBuffer
{
    char* CharStream::getNext()
    {
        if (this->lastFrame && this->currentPosition == this->posCurrent) {
            // достигнут конец
            return NULL;
        }

        if (this->currentPosition == 0 && this->posCurrent == 0) {
            // первый раз тут, читаем данные
            // позиция в буфере
            this->posCurrent = this->reader->read(this->currentBuffer, STREAM_BUFFER_SIZE);
            this->posForward = 0;

            if (this->posCurrent < STREAM_BUFFER_SIZE) {
                this->eof = true;
                this->lastFrame = true;
            } else {
                this->posForward = this->reader->read(this->forwardBuffer, STREAM_BUFFER_SIZE);
                if (this->posForward < STREAM_BUFFER_SIZE) {
                    this->eof = true;
                }
            }
        }

        // если текущий указатель перешел в forward-буфер
        if (this->currentPosition >= STREAM_BUFFER_SIZE) {
            // очищаем буфер со старыми данными
            memset(this->currentBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));
            // копируем данные из forward buffer в current
            memcpy(this->currentBuffer, this->forwardBuffer, STREAM_BUFFER_SIZE);
            // копируем конечную позицию в буфере из forward в current
            this->posCurrent = this->posForward;
            // смещаем текущую позицию
            this->currentPosition -= STREAM_BUFFER_SIZE;
            // подготавливаем память для заливки новых данных
            memset(this->forwardBuffer, 0, STREAM_BUFFER_SIZE * sizeof(char));

            if (!this->eof) {
                // если не был достигнут конец файла, читаем новый forward-буфер
                this->posForward = this->reader->read(this->forwardBuffer, STREAM_BUFFER_SIZE);

                if (this->posForward < STREAM_BUFFER_SIZE) {
                    this->eof = true;
                }
            } else {
                // если конец файла, то освобождаем память от forward-буфера
                this->posForward = 0;
                this->lastFrame = true;
            }
        }

        return &this->currentBuffer[this->currentPosition];
    }
}
