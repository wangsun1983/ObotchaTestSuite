#include <stdio.h>
#include <unistd.h>

//#include "Thread.hpp"
//#include "ArrayList.hpp"
#include "Uint16.hpp"
#include "StrongPointer.hpp"
#include "String.hpp"
#include "TextLineReader.hpp"
#include "TestLog.hpp"
#include "MappedFile.hpp"
#include "MappedFileInputStream.hpp"
#include "FileInputStream.hpp"

using namespace obotcha;

void testMappedFileOutputStream() {

  //readLine();
  while(1) {
      MappedFile file = MappedFile::New("./tmp/base_data",128);
      OutputStream stream = file->getOutputStream();
      
      stream->write(String::New("abcdef")->toByteArray());
      stream->flush();

      FileInputStream fstream = FileInputStream::New("./tmp/base_data");
      fstream->open();
      ByteArray dd = ByteArray::New(256);
      fstream->read(dd);

      if(!dd->toString()->sameAs("abcdefworld,this is a test data.")) {
        TEST_FAIL("MappedFileOutputStream Test case1");
      }
      break;
  }
  
  while(1) {
      MappedFile file = MappedFile::New("./tmp/base_data2",128);
      OutputStream stream = file->getOutputStream();
      
      stream->write('c');
      stream->flush();

      FileInputStream fstream = FileInputStream::New("./tmp/base_data2");
      fstream->open();
      ByteArray dd = ByteArray::New(256);
      fstream->read(dd);

      if(!dd->toString()->sameAs("c")) {
        TEST_FAIL("MappedFileOutputStream Test case2");
      }
      break;
  }

  TEST_OK("[MappedFileOutputStream Test case100]");
}
