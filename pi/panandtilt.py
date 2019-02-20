# based on https://github.com/araffin/python-arduino-serial/blob/master/robust_serial/robust_serial.py

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
