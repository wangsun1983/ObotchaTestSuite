from socket import *
import sys
import select
import os
import time
import socket

import sys
sys.path.append(r'../../../../../common')
from NetPort import getEnvPort

host="127.0.0.1"

port = getEnvPort();

s = socket.socket()
s.connect(("127.0.0.1",port))

buf=4096*32
f = open("file",'wb')

print "cccc"
with open('data', 'r') as fp:
    while True:
        #print "dddd"
        data = fp.read(1024*4)
        s.send(data)
        time.sleep(0.1)
        if not data:
            break;


#print "Upload Donwloaded"