#include <cpp-unit-test.h>
#include <io-buffer.h>
#include <iostream>
#include <string>
#include <memory.h>

CppUnitTest::TestCase* testCase_SmallFile_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("small-file");
    t->printTitle();

    IOBuffer::IOFileReader file_buffer("./fixtures/001-test-case-small-file.txt");
    IOBuffer::CharStream charStream(&file_buffer);

    char* curChar = NULL;

    std::string assertCharacters = "It is some file for test...\n";

    for (int i = 0; i < assertCharacters.length(); i++) {
        curChar = charStream.getNext();
        CppUnitTest::assertNotNull(t, curChar);
        CppUnitTest::assertEquals(t, assertCharacters[i], *curChar);
    }

    curChar = charStream.getNext();
    CppUnitTest::assertNull(t, curChar);

    t->finish();
    return t;
}

CppUnitTest::TestCase* testCase_ChunkedReadFile_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("chunked-read-file");
    t->printTitle();

    IOBuffer::IOFileReader file_buffer("./fixtures/001-test-case-small-file.txt");
    IOBuffer::CharStream charStream(&file_buffer, 10);

    char* curChar = NULL;

    std::string assertCharacters = "It is some file for test...\n";

    for (int i = 0; i < assertCharacters.length(); i++) {
        curChar = charStream.getNext();
        CppUnitTest::assertNotNull(t, curChar);
        CppUnitTest::assertEquals(t, assertCharacters[i], *curChar);
    }

    curChar = charStream.getNext();
    CppUnitTest::assertNull(t, curChar);

    t->finish();
    return t;
}

CppUnitTest::TestCase* testCase_CountReadFiles_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("return-read-count-memory");
    t->printTitle();

    IOBuffer::IOFileReader file_buffer("./fixtures/lorem-ipsum-short.txt");
    IOBuffer::IOMemoryBuffer ioMemory(256);

    char* buffer = (char*) malloc(sizeof(char) * 1024);
    memset(buffer, 0, sizeof(char) * 1024);

    int nSizeFile = file_buffer.read(buffer, 1024);
    ioMemory.write(buffer, nSizeFile);

    memset(buffer, 0, sizeof(char) * 1024);
    int size = ioMemory.read(buffer, 1024);

    CppUnitTest::assertEquals(t, 610, ioMemory.length());
    CppUnitTest::assertEquals(t, 610, size);

    t->finish();
    return t;
}

CppUnitTest::TestCase* testCase_RepeatableReadWithOverLength_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("repeatable-read-with-over-length");
    t->printTitle();

    const char* dataForTests = "It is data for repeatable read";

    IOBuffer::IOMemoryBuffer buffer(64);
    buffer.write((char*) dataForTests, strlen(dataForTests));

    char* readBlock = (char*) malloc(sizeof(char) * 21);
    memset(readBlock, 0, sizeof(char) * 21);

    int nRead = buffer.read(readBlock, 20);
    CppUnitTest::assertEquals(t, 20, nRead);
    CppUnitTest::assertEquals(t, readBlock, "It is data for repea");

    memset(readBlock, 0, sizeof(char) * 21);
    nRead = buffer.read(readBlock, 20);
    CppUnitTest::assertEquals(t, 10, nRead);
    CppUnitTest::assertEquals(t, readBlock, "table read");

    t->finish();
    return t;
}

CppUnitTest::TestCase* testRead_RepeatableReadWithOverLengthOnSmallBlocks_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("repeatable-read-with-over-length-on-small-blocks");
    t->printTitle();

    const char* dataForTests = "It is data for repeatable read";

    IOBuffer::IOMemoryBuffer buffer(16);
    buffer.write((char*) dataForTests, strlen(dataForTests));

    char* readBlock = (char*) malloc(sizeof(char) * 21);
    memset(readBlock, 0, sizeof(char) * 21);

    int nRead = buffer.read(readBlock, 20);
    CppUnitTest::assertEquals(t, 20, nRead);
    CppUnitTest::assertEquals(t, readBlock, "It is data for repea");

    memset(readBlock, 0, sizeof(char) * 21);
    nRead = buffer.read(readBlock, 20);
    CppUnitTest::assertEquals(t, 10, nRead);
    CppUnitTest::assertEquals(t, readBlock, "table read");

    t->finish();
    return t;
}

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;
    testSuite.addTestCase(testCase_SmallFile_Positive());
    testSuite.addTestCase(testCase_ChunkedReadFile_Positive());
    testSuite.addTestCase(testCase_CountReadFiles_Positive());
    testSuite.addTestCase(testCase_RepeatableReadWithOverLength_Positive());
    testSuite.addTestCase(testRead_RepeatableReadWithOverLengthOnSmallBlocks_Positive());
    testSuite.printTotal();
    return 0;
}
