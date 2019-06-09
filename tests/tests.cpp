#include <cpp-unit-test.h>
#include <io-buffer.h>
#include <iostream>
#include <string>

CppUnitTest::TestCase* testCase_SmallFile_Positive()
{
    CppUnitTest::TestCase* t = new CppUnitTest::TestCase("small-file");
    t->printTitle();

    IOBuffer::IOFileReader file_buffer("../fixtures/001-test-case-small-file.txt");
    IOBuffer::CharStream charStream(&file_buffer);

    char* curChar = NULL;

    std::string assertCharacters = "It is some file for test...\n";

    for (int i = 0; i < assertCharacters.length(); i++) {
        curChar = charStream.getNext();
        CppUnitTest::assertNotNull(t, curChar);
        CppUnitTest::assertEquals(t, assertCharacters[i], *curChar);
    }

    t->finish();
    return t;
}

int main(int argc, char** argv) {
    CppUnitTest::TestSuite testSuite;
    testSuite.addTestCase(testCase_SmallFile_Positive());
    testSuite.printTotal();
    return 0;
}
