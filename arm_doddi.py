# -*- coding: utf-8 -*-
"""
-------------------------------------------------------------------------------
Created during Winter Semester 2015

OpenCV Human face tracker combined with arduino powered bot to
follow humans.

         @authors:
Yash Chandak    Ankit Dhall


TODO:
convert frame specific values to percentages
-------------------------------------------------------------------------------
"""

import numpy as np
import sys
import time

"""
PySerial library required for arduino connection
OpenCV library requierd for face tracking
"""

from serial import Serial
import cv2

"""
Arduino connected at port No. COM28,
Confirm and change this value accordingly from control panel

Baud Rate = 9600
"""

arduino = Serial('COM9', 9600)
time.sleep(2) # waiting the initialization...
print("initialised")

#gets the direction for Arduino serial
def direction(bound, initArea=40000):
    """
    Direction control Index:

    '<' , '>' are the frame check bits for serial communication

    Numbers represent the direction to be moved as per their position on numpad
    1: Back Left
    2: Back
    3: Back right
    4: Left
    5: Stay still
    6: Right
    7: Front Left
    8: Forward
    9: Forward right
    """     

    #anchor the centre position of the image
    center=(320, 240)
    #current rectangle center
    curr = (bound[0] + bound[2]/2, bound[1]+bound[3]/2)
    
    print ("bound 0>", bound[0])
    print ("bound 1>", bound[1])
    print ("bound 2>", bound[2])
    print ("bound 3>", bound[3])
    print ("curr>", curr)
    print("magic number -- ", repr(bound[2]*bound[3]))
    print("fart", bound[2]*bound[3])

    out=0
    flag=0
    fb = 0 #0-stay 1-fwd  2-bwd
    lr = 0 #0-stay 1-left 2-right
    ud = 0 #0-stay 1-up   2-down

    #if the object is coming closer i.e. it's size is increasing then move bwd
    if bound[2]*bound[3] > (50000):
        fb = 2
    #if the object os moving away i.e. it's size is decreasing then move towards it
    elif bound[2]*bound[3] < (10000):
        fb = 1
    else :
        fb = 0

    #move right
    if curr[0] > (center[0] + 100):
        lr = 2
    #move left
    elif curr[0] < (center[0] - 100):
        lr = 1
    else:
        lr = 0

    #move up
    if bound[1]<50:
        ud = 1
    #move down
    elif (bound[1]+bound[3])>430:
        ud = 2
    else:
        ud = 0

    if lr == 0 and fb == 0 and ud == 0:
        out = 1
        print("stay")
    elif lr == 0 and fb == 1 and ud == 0:
        out =2
        print("fwd")
    elif lr == 0 and fb == 2 and ud == 0:
        out = 3
        print("back")
    elif lr == 0 and fb == 0 and ud == 1:
        out = 4
        print("su")
    elif lr == 0 and fb == 1 and ud == 1:
        out = 5
        print("slu")
    elif lr == 0 and fb == 2 and ud == 0:
        out = 6
        print("sl")
    elif lr == 0 and fb == 0 and ud == 0:
        out = 7
        print("sld")
    elif lr == 0 and fb == 1 and ud == 0:
        out = 8
        print("sd")
    elif lr == 0 and fb == 2 and ud == 0:
        out = 9
        print("srd")
    elif lr == 0 and fb == 2 and ud == 0:
        out = 10
        print("sr")
    elif lr == 0 and fb == 1 and ud == 0:
        out = 11
        print("sru")
    elif lr == 0 and fb == 2 and ud == 0:
        out = 12
        print("bu")
    elif lr == 1 and fb == 0 and ud == 0:
        out = 13
        print("blu")
    elif lr == 1 and fb == 1 and ud == 0:
        out = 14
        print("bl")
    elif lr == 1 and fb == 2 and ud == 0:
        out = 15
        print("bld")
    elif lr == 2 and fb == 0 and ud == 0:
        out = 16
        print("bd")
    elif lr == 2 and fb == 1 and ud == 0:
        out = 17
        print("brd")
    elif lr == 2 and fb == 2 and ud == 0:
        out = 18
        print("br")
    elif lr == 2 and fb == 2 and ud == 0:
        out = 19
        print("bru")
    elif lr == 0 and fb == 1 and ud == 0:
        out = 20
        print("fu")
    elif lr == 0 and fb == 2 and ud == 0:
        out = 21
        print("flu")
    elif lr == 1 and fb == 0 and ud == 0:
        out = 22
        print("fl")
    elif lr == 1 and fb == 1 and ud == 0:
        out = 23
        print("fld")
    elif lr == 1 and fb == 2 and ud == 0:
        out = 24
        print("fd")
    elif lr == 2 and fb == 0 and ud == 0:
        out = 25
        print("frd")
    elif lr == 2 and fb == 1 and ud == 0:
        out = 26
        print("fr")
    elif lr == 2 and fb == 2 and ud == 0:
        out = 27
        print("fru")     
    else :
        out = 28
        print("BASE")

    #Write the encoded direction value on the serial communication line
    print(out)
    arduino.write('<'.encode())
    arduino.write(str(out).encode())
    arduino.write('>'.encode())

def detectAndDisplay(frame):
    #use OpenCV HAAR face detetcion algorithm to detect faces
    faces = cascade.detectMultiScale(frame, scaleFactor=1.1, minNeighbors=3,
                                            minSize=(30, 30),maxSize=(500,500),
                                            flags=2)

    #if any face is detected then process else continue searching
    if(len(faces)!=0):
        #If number of faces in the image is more than 1
        #Then choose the one with maximum size
        max_area=-1
        i=0
        for (x,y,w,h) in faces:
            if w*h > max_area:
                max_area=w*h
                pos=i
            i=i+1

        RECT=faces[pos]
        #Mark the face being tracked on the image display
        cv2.rectangle(frame, (RECT[0], RECT[1]), (RECT[0]+RECT[2], RECT[1]+RECT[3]), (0, 255, 0), 2)
        #draw_str(frame, (RECT[0], RECT[3]+16), 'x: %.2f y: %.2f size: %.2f' % (RECT[2]-RECT[0])/2 % (RECT[3]-RECT[1])/2 % RECT[2]*RECT[3])

        #Put the text details about the ROI on imdisplay
        cv2.putText(frame, repr(RECT[0] + RECT[2]/2)+'  '+repr(RECT[1]+RECT[3]/2)+' '+repr(RECT[2]*RECT[3]), (RECT[0],RECT[1]+RECT[3]),  cv2.FONT_HERSHEY_SIMPLEX , 1, (0,0,255));

        #compute direction for the arduino bot to be moved.
        direction(RECT)

    else:
        print('No face go to base')
        arduino.write('<'.encode())
        arduino.write(str(28).encode())
        arduino.write('>'.encode())

    cv2.imshow('frame',frame)


cascade = cv2.CascadeClassifier('haarcascade_frontalface_default.xml')
#cascade = cv2.CascadeClassifier('haarcascade_frontalface_alt.xml')


cap = cv2.VideoCapture(0)
cap.set(3,640)
cap.set(4,480)
cap.grab()
ret, frame = cap.retrieve()

#Run the tracker in infinite loop
while(1):

    #grab the frames from web camera
    cap.grab()
    ret, frame = cap.retrieve()
    if ret ==0:
        print("frame not loaded")
    if ret==True:

        #Resize the frame for faster computation
        #cv2.resize(frame,(240,320))

        #Process the frame and pass data to arduino
        detectAndDisplay(frame)

        #press ESC to exit program
        ch = cv2.waitKey(1)
        if ch==27:
            break

#Free up memory on exit
cap.release()
cv2.destroyAllWindows()
arduino.close()
