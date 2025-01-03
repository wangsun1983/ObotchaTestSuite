#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>

#include "Thread.hpp"
#include "Object.hpp"
#include "System.hpp"
#include "Barrier.hpp"
#include "ByteArrayReader.hpp"
#include "ByteArrayWriter.hpp"
#include "TestLog.hpp"
#include <string.h>

using namespace obotcha;


void testByteArrayWriterArray() {
    while(1) {
      ByteArray array = ByteArray::New(8);
      byte arr1[] = {1,2,3,4};
      byte arr2[] = {5,6,7,8};

      ByteArrayWriter writer = ByteArrayWriter::New(array);
      writer->write(ByteArray::New(arr1,4));
      writer->write(ByteArray::New(arr2,4));

      for(int i = 0;i<8;i++) {
        if(array[i] != i + 1) {
          TEST_FAIL("[TestByteArrayWriter Write Array case1],array[%d] is %d,real is %d",i,array[i],(i+1));
        }
      }

      break;
    }

    while(1) {
      ByteArray d1 = ByteArray::New(16);
      ByteArrayWriter writer = ByteArrayWriter::New(d1);

      byte data[] = {1,2,3,4,5,6};
      ByteArray d2 = ByteArray::New(data,6);
      writer->write(d2,2,3);
      if(d1[0] != 3 || d1[1] != 4 || d1[2] != 5) {
        TEST_FAIL("[TestByteArrayWriter Write Array case2]");
      }
      break;
    }

    while(1) {
      ByteArray d1 = ByteArray::New(16);
      ByteArrayWriter writer = ByteArrayWriter::New(d1);

      byte data[] = {1,2,3,4,5,6};
      writer->write(data+1,3);
      if(d1[0] != 2 || d1[1] != 3 || d1[2] != 4) {
        TEST_FAIL("[TestByteArrayWriter Write Array case3]");
      }
      break;
    }

    TEST_OK("[TestByteArrayWriter Write Array case100]");
}
