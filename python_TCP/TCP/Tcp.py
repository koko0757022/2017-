#!/usr/bin/env python
import socket
import time
TCP_IP = 'localhost'
TCP_PORT = 50007
BUFFER_SIZE = 24  # Normally 1024, but we want fast response

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
data1=""
conn, addr = s.accept()
print('Connection address:', addr)
while 1:
    time.sleep(1)
    data = conn.recv(BUFFER_SIZE)
    if not data: break
    if data!=data1:
        #print("received data:", data)
        p=str(data,encoding='utf-8')
        print("PointX:", int(p.split()[0]))
        print("PointY:", int(p.split()[1]))

        data1=data
    if the==0:
        conn.send("1")  # echo
    else:
        conn.send("0")

conn.close()