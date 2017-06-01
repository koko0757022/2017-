#!/usr/bin/env python
from ev3dev.ev3 import *
from time import sleep

import socket
import time

TCP_IP = ''
TCP_PORT = 50006
BUFFER_SIZE = 24  # Normally 1024, but we want fast response

mA = LargeMotor('outA')  # line x motor
mB = MediumMotor('outB')  # injection motor
mC = MediumMotor('outC')  # line y motor
mD = LargeMotor('outD')  # injection's pistone

endSign = False
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind((TCP_IP, TCP_PORT))
s.listen(1)
data1 = ""
conn, addr = s.accept()
print('Connection address:', addr)
while 1:
    time.sleep(1)

    data = conn.recv(BUFFER_SIZE)
    if not data: break
    if data != data1:
        # print("received data:", data)
        p = str(data, encoding='utf-8')
        print("PointX:", int(p.split()[0]))
        print("PointY:", int(p.split()[1]))

        y = int(p.split()[0])
        x = int(p.split()[1])
        endSign = False
        # conn.send(endSign)
        while True:
            numZ1 = int(mB.position)
            # mB = DcMotor('outB')
            mB.run_direct(duty_cycle_sp=45)

            sleep(0.2)
            mB = MediumMotor('outB')
            numZ2 = int(mB.position)
            if numZ1 >= numZ2:
                mB.stop()
                # print(mB.position)
                mB.reset()
                print(mB.position)
                break
        while True:
            numY1 = int(mC.position)

            mC.run_forever(speed_sp=-200)
            sleep(0.2)
            numY2 = int(mC.position)
            if numY1 <= numY2:  # 135
                mC.run_timed(time_sp=500, speed_sp=150)
                sleep(1)
                mC.stop()
                mC.reset()
                break
        while True:
            numX1 = int(mA.position)
            mA.run_direct(duty_cycle_sp=-30)
            sleep(0.2)
            numX2 = int(mA.position)
            if numX1 <= numX2:
                # mA.run_timed(time_sp=100, speed_sp=-100)
                #  sleep(1)
                mA.stop(stop_action='brake')
                mA.reset()
                break

        mB.reset()
        sleep(1)  # sp_sp100
        mA.run_timed(time_sp=400, speed_sp=-100, stop_action='hold')
        sleep(0.5)

        mB.run_to_abs_pos(position_sp=-177, speed_sp=-350, stop_action='hold')
        sleep(1)
        # -167
        # 80,350
        mD.run_timed(time_sp=1000, speed_sp=-60, stop_action='hold')
        mB.run_to_abs_pos(position_sp=-197, speed_sp=-350, stop_action='brake')
        sleep(1.5)
        # -187
        mB.run_to_abs_pos(position_sp=0, speed_sp=-350)
        sleep(1)

        mA.reset()
        mC.reset()
        mA.run_to_abs_pos(position_sp=260 + (115 * x), speed_sp=350, stop_action="brake")
        mC.run_to_abs_pos(position_sp=50 + (120 * y), speed_sp=350, stop_action="brake")
        if x > y:
            sleep(0.6 * x)
        else:
            sleep(0.6 * y)

        mB.run_timed(time_sp=1000, speed_sp=-400)
        sleep(1)

        mD.run_timed(time_sp=1000, speed_sp=60, stop_action='hold')
        sleep(1)
        mB.run_timed(time_sp=1000, speed_sp=400)
        sleep(1)
        mA.run_to_abs_pos(position_sp=0, speed_sp=350, stop_action="brake")
        mC.run_to_abs_pos(position_sp=0, speed_sp=350, stop_action="brake")
        if x > y:
            sleep(0.6 * x)
        else:
            sleep(0.6 * y)

        endSign = True
        data1 = data

    conn.send(data)
    # echo
conn.close()