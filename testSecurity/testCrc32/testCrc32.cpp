#include <stdio.h>
#include "Crc32.hpp"
#include "FileInputStream.hpp"
#include "TestLog.hpp"

using namespace obotcha;

int main() {

    //testfile.data crc32 result is 82269724
    //encode(ByteArray b)
    long v1;
    long v2;
    long v3;

    while(1) {
        File f = createFile("testData.file");
        FileInputStream stream = createFileInputStream(f);
        stream->open();
        ByteArray array = stream->readAll();
        stream->close();
        Crc32 cc = createCrc32();
        v1 = cc->encode(array);
        if(v1 <= 0) {
            TEST_FAIL("[TestCrc32 Test {encode(ByteArray)} case1]");
            break;
        }

        TEST_OK("[TestCrc32 Test {encode(ByteArray)} case2]");
        break;
    }

    //encode(String)
    while(1) {
        File f = createFile("testData.file");
        FileInputStream stream = createFileInputStream(f);
        stream->open();
        ByteArray array = stream->readAll();
        stream->close();
        String str = array->toString();
        Crc32 cc = createCrc32();
        v2 = cc->encode(str);
        if(v2 <= 0) {
            TEST_FAIL("[TestCrc32 Test {encode(String)} case1]");
            break;
        }

        TEST_OK("[TestCrc32 Test {encode(String)} case2]");
        break;
    }


    //long encode(File);
    while(1) {
    	File f = createFile("testData.file");
        Crc32 cc = createCrc32();
        v3 = cc->encode(f);
        //TEST_FAIL("v is %ld \n",v);
        if(v3 <= 0) {
            TEST_FAIL("[TestCrc32 Test {encode(File)} case1]");
            break;
        }

        TEST_OK("[TestCrc32 Test {encode(File)} case2]");
        break;
    }

    if(v1 != v2 || v2!=v3 || v1!=v3) {
        TEST_FAIL("[TestCrc32 Test {encode(File)} case3]");
    }

    TEST_OK("[TestCrc32 Test {encode(File)} case4]");
}
