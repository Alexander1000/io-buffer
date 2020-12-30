# Changelog io-buffer

## 0.1.6
  - fix bug with multi block read data
  - add tests

## 0.1.5
  - fix bug multi block writing data
  - add tests

## 0.1.4
  - fix segfault on repeatable read when (length for read) + (read position) more than (write position)

## 0.1.3
  - `IOBuffer::IOMemoryBuffer::read()` - return count read bytes

## 0.1.2
  - fixed allocation with flexible buffer size

## 0.1.1
  - read not more than buffer wrote bytes

## 0.1.0
  - add `IOBuffer::CharStream` class

## 0.0.1
  - initial commit
