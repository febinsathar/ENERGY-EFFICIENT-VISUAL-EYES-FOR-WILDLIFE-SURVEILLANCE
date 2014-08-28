import os

import pickle

f=open('upload.p', 'rb')

lastup=pickle.load(f)

f=open('upload.p', 'wb')

pickle.dump(lastup, f)

fs=str('/home/pi/camimage/cam1pic')

ext=str('.jpg')

checkfile=fs+str(lastup+1)+ext

print checkfile

while 1:

checkfile=fs+str(lastup+1)+ext

if(os.path.isfile(checkfile) == True ):

 os.system('./dropbox_uploader.sh upload ' + checkfile )

lastup=lastup+1

f=open('upload.p', 'wb')

pickle.dump(lastup, f)
