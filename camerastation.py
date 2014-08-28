import os

import pickle

import RPi.GPIO as GPIO

GPIO.setmode(GPIO.BOARD)

GPIO.setmode(GPIO.BCM)

GPIO.setup( 10, GPIO.OUT)

GPIO.setup( 9, GPIO.IN)

GPIO.output(10, False)

while 1:

if(GPIO.input(9)==False) :

break

GPIO.output(10, True)

print "handshake completed"

fs=str('fswebcam -r 640x480 /home/pi/camimage/cam1pic')

ext=str('.jpg')

f=open('track.p', 'rb')

count= pickle.load(f)

while 1:

f=open('track.p', 'wb')

pickle.dump(count, f)

if(GPIO.input(9)==False):

print 'test inside loop'

count = count + 1

f=open('track.p', 'wb')

pickle.dump(count, f)

os.system(fs+str(count)+ext)

GPIO.output(10, False)

while (GPIO.input(9)==0):

print '.'

GPIO.output(10,True)

print 'photo taken=', count
