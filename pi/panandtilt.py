# Serial Communication based on https://github.com/araffin/python-arduino-serial/blob/master/robust_serial/robust_serial.py
# Face tracking based on https://github.com/pimoroni/PanTiltFacetracker/blob/master/facetracker_lbp.py
import serial.tools.list_ports
import struct

import cv2, sys, time, os


PANSERVO = 0
TILTSERVO = 1
STOP = 2
EXPLORE = 3

def write_i8(f, value):
    """
    :param f: file handler or serial file
    :param value: (int8_t)
    """
    if -128 <= value <= 127:
        f.write(struct.pack('<b', value))
    else:
        print("Value error:{}".format(value))

def write_i16(f, value):
    """
    :param f: file handler or serial file
    :param value: (int16_t)
    """
    f.write(struct.pack('<h', value))

def write_order(f, order):
    """
    :param f: file handler or serial file
    :param order: (Order Enum Object)
    """
    write_i8(f, order)

# https://stackoverflow.com/questions/24214643/python-to-automatically-select-serial-ports-for-arduino

f = None 

print ("Looking for Arduino")
while (f == None):
    ports = list(serial.tools.list_ports.comports())
    for p in ports:
        print(p)

        if "Arduino" in p[1]:
            f = serial.Serial(p[0])

def pan(val):
    print ("panval")
    print (val) 
    write_order(f, PANSERVO)
    write_i16(f, val)

def tilt(val):
    print ("tiltval")
    print (val)
    write_order(f, TILTSERVO)
    write_i16(f, val)

# Load the BCM V4l2 driver for /dev/video0
os.system('sudo modprobe bcm2835-v4l2')
# Set the framerate ( not sure this does anything! )
os.system('v4l2-ctl -p 1')

# Frame Size. Smaller is faster, but less accurate.
# Wide and short is better, since moving your head
# vertically is kinda hard!
FRAME_W = 1280
FRAME_H = 720

# Default Pan/Tilt for the camera in degrees.
# Camera range is from 0 to 180
cam_pan = 90
cam_tilt = 60

# Set up the CascadeClassifier for face tracking
#cascPath = 'haarcascade_frontalface_default.xml' # sys.argv[1]
cascPath = '/usr/share/opencv/lbpcascades/lbpcascade_frontalface.xml'
faceCascade = cv2.CascadeClassifier(cascPath)

# Set up the capture with our frame size
video_capture = cv2.VideoCapture(0)
video_capture.set(cv2.CAP_PROP_FRAME_WIDTH,  FRAME_W)
video_capture.set(cv2.CAP_PROP_FRAME_HEIGHT, FRAME_H)
time.sleep(2)

# Turn the camera to the default position
pan(cam_pan)
tilt(cam_tilt)

while True:
    # Capture frame-by-frame
    ret, frame = video_capture.read()
    # This line lets you mount the camera the "right" way up, with neopixels above
    frame = cv2.flip(frame, -1)
    
    if ret == False:
      print("Error getting image")
      continue

    # Convert to greyscale for detection
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    gray = cv2.equalizeHist( gray )

    loop_counter = 10

    # Do face detection
    if loop_counter == 10:
        faces = faceCascade.detectMultiScale(frame, 1.1, 3, 0, (10, 10))
        loop_counter = 0

    loop_counter = loop_counter + 1
  
    print (type(faces))

    for (x, y, w, h) in faces:
        # Draw a green rectangle around the face
        cv2.rectangle(frame, (x, y), (x+w, y+h), (0, 255, 0), 2)

        # Track first face
        
        # Get the center of the face
        x = x + (w/2)
        y = y + (h/2)

        # Correct relative to center of image
        turn_x  = float(x - (FRAME_W/2))
        turn_y  = float(y - (FRAME_H/2))

        # Convert to percentage offset
        turn_x  /= float(FRAME_W/2)
        turn_y  /= float(FRAME_H/2)

        # Scale offset to degrees
        turn_x   *= 2.5 # VFOV
        turn_y   *= 2.5 # HFOV
        cam_pan  += -turn_x
        cam_tilt += turn_y

        print(cam_pan, cam_tilt)

        # Clamp Pan/Tilt to 0 to 180 degrees
        cam_pan = max(0,min(180,cam_pan))
        cam_tilt = max(0,min(180,cam_tilt))

        # Update the servos
        pan(int(cam_pan))
        tilt(int(cam_tilt))

        break

    frame = cv2.resize(frame, (540,300))
    frame = cv2.flip(frame, 1)
   
    # Display the image, with rectangle
    # on the Pi desktop 
    cv2.imshow('Video', frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# When everything is done, release the capture
video_capture.release()
cv2.destroyAllWindows()
