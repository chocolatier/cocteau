# based on https://github.com/araffin/python-arduino-serial/blob/master/robust_serial/robust_serial.py
import serial.tools.list_ports
import struct

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

ports = list(serial.tools.list_ports.comports())
for p in ports:
	print(p)

	if "Arduino" in p[1]:
		f = serial.Serial(p[0])

def writePan(val):
    write_order(f, PANSERVO)
    write_i16(f, val)

def writeTilt(val):
    write_order(f, TILTSERVO)
    write_i16(f, val)

writePan(122)
writeTilt(45)
