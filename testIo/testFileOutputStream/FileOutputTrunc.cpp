#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "FileOutputStream.hpp"
#include "FileInputStream.hpp"
#include "File.hpp"
#include "TestLog.hpp"

using namespace obotcha;

void fileoutput_trunc_test() {

    //bool _FileOutputStream::write(char c)
    while(1) {
        File file = File::New("./tmp/trucn_test1.txt");
        file->createNewFile();
        FileOutputStream stream = FileOutputStream::New(file);
        stream->open(st(IO)::FileControlFlags::Trunc);
        stream->write('a');
        stream->flush();
        stream->close();

        FileOutputStream stream2 = FileOutputStream::New(file);
        stream2->open(st(IO)::FileControlFlags::Trunc);
        stream2->write('b');
        stream2->flush();
        stream2->close();

        if(file->length() != 1) {
            TEST_FAIL("[TestFileOutputStream Test {open(Trunc)} case1]");
            break;
        }

        FileInputStream inputstream = FileInputStream::New(file);
        inputstream->open();
        ByteArray content = inputstream->readAll();
        if(content == nullptr || content->size() != 1 ||content->at(0) != 'b') {
            TEST_FAIL("[TestFileOutputStream Test {open(Trunc)} case2]");
            break;
        }

        //file->removeAll();

        TEST_OK("[TestFileOutputStream Test {open(Trunc)} case3]");
        break;
    }

    while(1) {
        File file = File::New("./tmp/trucn_test2.txt");
        file->createNewFile();
        FileOutputStream stream = FileOutputStream::New(file);
        stream->open(st(IO)::FileControlFlags::Trunc);
        ByteArray data = ByteArray::New(12);
        for(int i = 0;i<12;i++) {
          data[i] = i;
        }

        stream->write(data,3,3);
        stream->flush();

        if(file->length() != 3) {
          TEST_FAIL("[TestFileOutputStream Test {open(Trunc)} case4] [FAILED],len is %ld \n",file->length());
          break;
        }

        int fd = open("./tmp/trucn_test2.txt",O_RDONLY);
        byte readbuf[3];
        read(fd,readbuf,3);

        if(readbuf[0] != 3 || readbuf[1] != 4 || readbuf[2] != 5) {
          TEST_FAIL("[TestFileOutputStream Test {open(Trunc)} case5]");
        }
        close(fd);

        TEST_OK("[TestFileOutputStream Test {open(Trunc)} case6]");
        break;
    }

}
