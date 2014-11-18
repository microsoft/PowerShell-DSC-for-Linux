import ctypes
import struct
import sys
import time


MI_BOOLEAN = 0
MI_UINT8 = 1
MI_SINT8 = 2
MI_UINT16 = 3
MI_SINT16 = 4
MI_UINT32 = 5
MI_SINT32 = 6
MI_UINT64 = 7
MI_SINT64 = 8
MI_REAL32 = 9
MI_REAL64 = 10
MI_CHAR16 = 11
MI_DATETIME = 12
MI_STRING = 13
#MI_REFERENCE = 14
#MI_INSTANCE = 15
MI_BOOLEANA = 16
MI_UINT8A = 17
MI_SINT8A = 18
MI_UINT16A = 19
MI_SINT16A = 20
MI_UINT32A = 21
MI_SINT32A = 22
MI_UINT64A = 23
MI_SINT64A = 24
MI_REAL32A = 25
MI_REAL64A = 26
MI_CHAR16A = 27
MI_DATETIMEA = 28
MI_STRINGA = 29
#MI_REFERENCEA = 30
#MI_INSTANCEA = 31

MI_NULL_FLAG = 64


DO_TRACE = True
DO_VERBOSE_TRACE = False


def trace (text):
    if DO_TRACE:
        sys.stdout.write (text + '\n')

def verbose_trace (text):
    if DO_VERBOSE_TRACE:
        trace (text)


class file_desc:
    def sendall (self, buf):
        pass


class MI_Value:
    type
    value = None
    
    def __init__ (self, type):
        self.type = type

    def write (self, fd):
        trace ('  <MI_Value::write>')
        val = self.type
        if self.value is None:
            val = val | MI_NULL_FLAG
        trace ('    type: ' + str(self.type) +  ' ' + repr(self.value) )
        buf = struct.pack ('@B', val)
        fd.sendall (buf)
        trace ('  </MI_Value::write>')

    @staticmethod
    def read (fd):
        trace ('<MI_Value::read>')
        buf = fd.recv (1)
        type = struct.unpack ('@B', buf)[0]
        switch = type & ~(MI_NULL_FLAG)
        
        trace ('  type: ' + str(switch) )
        val = None
        if MI_BOOLEAN == switch:
            val = MI_Boolean.read (fd, type)
        elif MI_UINT8 == switch:
            val = MI_Uint8.read (fd, type)
        elif MI_SINT8 == switch:
            val = MI_Sint8.read (fd, type)
        elif MI_UINT16 == switch:
            val = MI_Uint16.read (fd, type)
        elif MI_SINT16 == switch:
            val = MI_Sint16.read (fd, type)
        elif MI_UINT32 == switch:
            val = MI_Uint32.read (fd, type)
        elif MI_SINT32 == switch:
            val = MI_Sint32.read (fd, type)
        elif MI_UINT64 == switch:
            val = MI_Uint64.read (fd, type)
        elif MI_SINT64 == switch:
            val = MI_Sint64.read (fd, type)
        elif MI_REAL32 == switch:
            val = MI_Real32.read (fd, type)
        elif MI_REAL64 == switch:
            val = MI_Real64.read (fd, type)
        elif MI_CHAR16 == switch:
            val = MI_Char16.read (fd, type)
        elif MI_DATETIME == switch:
            val = MI_Datetime.read (fd, type)
        elif MI_STRING == switch:
            val = MI_String.read (fd, type)
        elif MI_BOOLEANA == switch:
            val = MI_BooleanA.read (fd, type)
        elif MI_UINT8A == switch:
            val = MI_Uint8A.read (fd, type)
        elif MI_SINT8A == switch:
            val = MI_Sint8A.read (fd, type)
        elif MI_UINT16A == switch:
            val = MI_Uint16A.read (fd, type)
        elif MI_SINT16A == switch:
            val = MI_Sint16A.read (fd, type)
        elif MI_UINT32A == switch:
            val = MI_Uint32A.read (fd, type)
        elif MI_SINT32A == switch:
            val = MI_Sint32A.read (fd, type)
        elif MI_UINT64A == switch:
            val = MI_Uint64A.read (fd, type)
        elif MI_SINT64A == switch:
            val = MI_Sint64A.read (fd, type)
        elif MI_REAL32A == switch:
            val = MI_Real32A.read (fd, type)
        elif MI_REAL64A == switch:
            val = MI_Real64A.read (fd, type)
        elif MI_CHAR16A == switch:
            val = MI_Char16A.read (fd, type)
        elif MI_DATETIMEA == switch:
            val = MI_DatetimeA.read (fd, type)
        elif MI_STRINGA == switch:
            val = MI_StringA.read (fd, type)
        else:
            trace ('Received unexpected type: ' + str(type))
        trace ('</MI_Value::read>')
        return val


class MI_Boolean (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_BOOLEAN)
        if val is not None:
            #ctypes.c_bool not available if python < 2.6.6
            try:
                self.value = ctypes.c_bool (val)
            except:
                self.value = ctypes.c_int (val)
    def write (self, fd):
        verbose_trace ('<MI_Boolean.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            verbose_trace ('  value: ' + str (self.value.value))
            if self.value.value : 
                tmp=1 
            else:
                tmp=0
            buf = struct.pack ('@B', tmp)
            fd.sendall (buf)
        verbose_trace ('</MI_Boolean.write>')

    @staticmethod
    def read (fd, flags):
        verbose_trace ('<MI_Boolean.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (1)
            val = struct.unpack ('@B', buf)[0]
            verbose_trace ('val is ' +str(int(val))+'\n')
            if val :
                tmp='True'
            else:
                tmp='False'
            verbose_trace ('  value: ' + tmp)
        rval = MI_Boolean (val)
        verbose_trace ('</MI_Boolean.read>')
        return rval


class MI_Uint8 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_UINT8)
        if val is not None:
            self.value = ctypes.c_ubyte (val)

    def write (self, fd):
        trace ('<MI_Uint8.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@B', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Uint8.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Uint8.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (1)
            val = struct.unpack ('@B', buf)[0]
        rval = MI_Uint8 (val)
        trace ('</MI_Uint8.read>')
        return rval


class MI_Sint8 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_SINT8)
        if val is not None:
            self.value = ctypes.c_byte (val)

    def write (self, fd):
        trace ('<MI_Sint8.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@b', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Sint8.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Sint8.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (1)
            val = struct.unpack ('@b', buf)[0]
        rval = MI_Sint8 (val)
        trace ('</MI_Sint8.read>')
        return rval


class MI_Uint16 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_UINT16)
        if val is not None:
            self.value = ctypes.c_ushort (val)

    def write (self, fd):
        trace ('<MI_Uint16.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@H', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Uint16.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Uint16.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (2)
            val = struct.unpack ('@H', buf)[0]
        rval = MI_Uint16 (val)
        trace ('</MI_Uint16.read>')
        return rval


class MI_Sint16 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_SINT16)
        if val is not None:
            self.value = ctypes.c_short (val)

    def write (self, fd):
        trace ('<MI_Sint16.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@h', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Sint16.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Sint16.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (2)
            val = struct.unpack ('@h', buf)[0]
        rval = MI_Sint16 (val)
        trace ('</MI_Sint16.read>')
        return rval


class MI_Uint32 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_UINT32)
        if val is not None:
            self.value = ctypes.c_uint (val)

    def write (self, fd):
        trace ('<MI_Uint32.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@I', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Uint32.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Uint32.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (4)
            val = struct.unpack ('@I', buf)[0]
        rval = MI_Uint32 (val)
        trace ('</MI_Uint32.read>')
        return rval


class MI_Sint32 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_SINT32)
        if val is not None:
            self.value = ctypes.c_int (val)

    def write (self, fd):
        trace ('<MI_Sint32.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@i', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Sint32.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Sint32.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (4)
            val = struct.unpack ('@i', buf)[0]
        rval = MI_Sint32 (val)
        trace ('</MI_Sint32.read>')
        return rval


class MI_Uint64 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_UINT64)
        if val is not None:
            self.value = ctypes.c_ulonglong (val)

    def write (self, fd):
        trace ('<MI_Uint64.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@Q', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Uint64.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Uint64.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (8)
            val = struct.unpack ('@Q', buf)[0]
        rval = MI_Uint64 (val)
        trace ('</MI_Uint64.read>')
        return rval


class MI_Sint64 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_SINT64)
        if val is not None:
            self.value = ctypes.c_longlong (val)

    def write (self, fd):
        trace ('<MI_Sint64.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@q', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Sint64.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Sint64.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (8)
            val = struct.unpack ('@q', buf)[0]
        rval = MI_Sint64 (val)
        trace ('</MI_Sint64.read>')
        return rval


class MI_Real32 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_REAL32)
        if val is not None:
            self.value = ctypes.c_float (val)

    def write (self, fd):
        trace ('<MI_Real32.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@f', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Real32.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Real32.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (8)
            val = struct.unpack ('@f', buf)[0]
        rval = MI_Real32 (val)
        trace ('</MI_Real32.read>')
        return rval


class MI_Real64 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_REAL64)
        if val is not None:
            self.value = ctypes.c_double (val)

    def write (self, fd):
        trace ('<MI_Real64.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@d', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Real64.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Real64.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (8)
            val = struct.unpack ('@d', buf)[0]
        rval = MI_Real64 (val)
        trace ('</MI_Real64.read>')
        return rval


class MI_Char16 (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_CHAR16)
        if val is not None:
            self.value = ctypes.c_ushort (val)

    def write (self, fd):
        trace ('<MI_Char16.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            trace ('  value: ' + str(self.value.value))
            buf = struct.pack ('@H', self.value.value)
            fd.sendall (buf)
        trace ('</MI_Char16.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Char16.read>')
        val = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (2)
            val = struct.unpack ('@H', buf)[0]
        rval = MI_Char16 (val)
        trace ('</MI_Char16.read>')
        return rval


class MI_Datetime (MI_Value):
    def __init__ (self, isTimestamp):
        MI_Value.__init__ (self, MI_DATETIME)
        try:
            self.value = ctypes.c_bool (isTimestamp)
        except:
            self.value = ctypes.c_int (isTimestamp)

    def write (self, fd):
        trace ('  <MI_Datetime.write>')
        MI_Value.write (self, fd)
        trace ('  </MI_Datetime.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Datetime.read>')
        rval = None
        if 0 == (MI_NULL_FLAG & flags):
            rval = MI_Datetime.read_data (fd)
        trace ('</MI_Datetime.read>')
        return rval

    @staticmethod
    def read_data (fd):
        trace ('  <MI_Datetime.read_data>')
        rval = None
        buf = fd.recv (1)
        isTimestamp=None
        try:
            isTimestamp = ctypes.c_bool (struct.unpack ('@B', buf)[0])
        except:
            isTimestamp = ctypes.c_int (struct.unpack ('@B', buf)[0])
        if isTimestamp:
            rval = MI_Timestamp.read_data (fd)
        else:
            rval = MI_Interval.read_data (fd)
        trace ('  </MI_Datetime.read_data>')
        return rval


class MI_Timestamp (MI_Datetime):
    def __init__ (self,
                  year = None,
                  month = None,
                  day = None,
                  hour = None,
                  minute = None,
                  second = None,
                  microseconds = None,
                  utc = None):
        if year is None and \
               month is None and \
               day is None and \
               hour is None and \
               minute is None and \
               second is None and \
               microseconds is None and \
               utc is None:
            MI_Datetime.__init__ (self, None)
        else:
            MI_Datetime.__init__ (self, True)
        if year != None :
            t=year
        else:
            t=0
        self.year = ctypes.c_uint (t)
        if month != None :
            t=month
        else:
            t=0
        self.month = ctypes.c_uint (t)
        if day != None :
            t=day
        else:
            t=0
        self.day = ctypes.c_uint (t)
        if hour != None :
            t=hour
        else:
            t=0
        self.hour = ctypes.c_uint (t)
        if minute != None :
            t=minute
        else:
            t=0
        self.minute = ctypes.c_uint (t)
        if second != None :
            t=second
        else:
            t=0
        self.second = ctypes.c_uint (t)
        if microseconds != None :
            t=microseconds
        else:
            t=0
        self.microseconds = ctypes.c_uint32 (t)
        if utc != None :
            t=utc
        else:
            t=0
        self.utc = ctypes.c_int(int(t))

    def write (self, fd):
        trace ('<MI_Timestamp.write>')
        MI_Datetime.write (self, fd)
        if self.value is not None:
            self.write_data (fd)
        trace ('</MI_Timestamp.write>')

    def write_data (self, fd):
        trace ('  <MI_Timestamp.write_data>')
        trace ('    isTimestamp:' + str (self.value.value))
        trace ('    year:' + str (self.year.value))
        trace ('    month:' + str (self.month.value))
        trace ('    day:' + str (self.day.value))
        trace ('    hour:' + str (self.hour.value))
        trace ('    minute:' + str (self.minute.value))
        trace ('    second:' + str (self.second.value))
        trace ('    microseconds:' + str (self.microseconds.value))
        trace ('    utc:' + str (self.utc.value))
        buf = struct.pack ('@B', self.value.value)
        buf += struct.pack ('@I', self.year.value)
        buf += struct.pack ('@I', self.month.value)
        buf += struct.pack ('@I', self.day.value)
        buf += struct.pack ('@I', self.hour.value)
        buf += struct.pack ('@I', self.minute.value)
        buf += struct.pack ('@I', self.second.value)
        buf += struct.pack ('@I', self.microseconds.value)
        buf += struct.pack ('@i', self.utc.value)
        fd.sendall (buf)
        trace ('  </MI_Timestamp.write_data>')

    @staticmethod
    def read_data (fd):
        trace ('    <MI_Timestamp.read_data>')
        buf = fd.recv (4)
        year = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        month = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        day = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        hour = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        minute = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        second = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        microseconds = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        utc = struct.unpack ('@i', buf)[0]
        buf = fd.recv (4)
        rval = MI_Timestamp (year, month, day, hour, minute, second,
                             microseconds, utc)
        trace ('      isTimestamp: True')
        trace ('      year:' + str (year))
        trace ('      month:' + str (month))
        trace ('      day:' + str (day))
        trace ('      hour:' + str (hour))
        trace ('      minute:' + str (minute))
        trace ('      second:' + str (second))
        trace ('      microseconds:' + str (microseconds))
        trace ('      utc:' + str (utc))
        trace ('    </MI_Timestamp.read_data>')
        return rval

    @staticmethod
    def from_time (seconds):
        trace ('<MI_Timestamp.from_time>')
        tm = time.gmtime (seconds)
        ts = MI_Timestamp (tm.tm_year, tm.tm_mon, tm.tm_mday, tm.tm_hour,
                           tm.tm_min, tm.tm_sec, 0, time.timezone / 60)
        trace ('</MI_Timestamp.from_time>')
        return ts


class MI_Interval (MI_Datetime):
    def __init__ (self,
                  days = None,
                  hours = None,
                  minutes = None,
                  seconds = None,
                  microseconds = None):
        if days is None and \
               hours is None and \
               minutes is None and \
               seconds is None and \
               microseconds is None:
            MI_Datetime.__init__ (self, None)
        else:
            MI_Datetime.__init__ (self, True)
        if days != None :
            t=day
        else:
            t=0
        self.days = ctypes.c_uint (t)
        if hours != None :
            t=hour
        else:
            t=0
        self.hours = ctypes.c_uint (t)
        if minutes != None :
            t=minute
        else:
            t=0
        self.minutes = ctypes.c_uint (t)
        if seconds != None :
            t=second
        else:
            t=0
        self.seconds = ctypes.c_uint (t)
        if microseconds != None :
            t=microsecond
        else:
            t=0
        self.microseconds = ctypes.c_uint32 (t)

    def write (self, fd):
        trace ('<MI_Interval.write>')
        MI_Datetime.write (self, fd)
        if self.value is not None:
            self.write_data (fd)
        trace ('</MI_Interval.write>')

    def write_data (self, fd):
        trace ('  <MI_Interval.write_data>')
        trace ('    isTimestamp:' + str (self.value.value))
        trace ('    days:' + str (self.days.value))
        trace ('    hours:' + str (self.hours.value))
        trace ('    minutes:' + str (self.minutes.value))
        trace ('    seconds:' + str (self.seconds.value))
        trace ('    microseconds:' + str (self.microseconds.value))
        buf = struct.pack ('@B', self.value.value)
        buf += struct.pack ('@I', self.days.value)
        buf += struct.pack ('@I', self.hours.value)
        buf += struct.pack ('@I', self.minutes.value)
        buf += struct.pack ('@I', self.seconds.value)
        buf += struct.pack ('@I', self.microseconds.value)
        fd.sendall (buf)
        trace ('  </MI_Interval.write>')

    @staticmethod
    def read_data (fd):
        trace ('    <MI_Interval.read_data>')
        buf = fd.recv (4)
        days = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        hours = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        minutes = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        seconds = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        microseconds = struct.unpack ('@I', buf)[0]
        buf = fd.recv (4)
        rval = MI_Timestamp (days, hours, minutes, seconds, microseconds)
        trace ('      isTimestamp: False')
        trace ('      days:' + str (days))
        trace ('      hours:' + str (hours))
        trace ('      minutes:' + str (minutes))
        trace ('      seconds:' + str (seconds))
        trace ('      microseconds:' + str (microseconds))
        trace ('    </MI_Interval.read_data>')
        return rval


class MI_String (MI_Value):
    def __init__ (self, val):
        MI_Value.__init__ (self, MI_STRING)
        if val is not None :
            if type(val) != str:
                self.value=str(val)
            else:
                self.value=val
    def write (self, fd):
        verbose_trace ('<MI_String.write>')
        MI_Value.write (self, fd)
        if self.value is not None:
            verbose_trace ('  len: ' + str(len (self.value)) + ', value: ' + self.value)
            buf = struct.pack ('@i', len (self.value))
            if type(buf) != str:
                buf += bytes (self.value, 'utf8')
            else:
                buf += self.value
            fd.sendall (buf)
        verbose_trace ('</MI_String.write>')

    @staticmethod
    def read (fd, flags):
        verbose_trace ('<MI_String.read>')
        strg = None
        if 0 == (MI_NULL_FLAG & flags):
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            if len > 0:
                buf = fd.recv (len)
                strg = buf.decode ('utf8')
            verbose_trace ('  len: ' + str(len) + ', value: ' + str(strg))
        rval = MI_String (strg)
        verbose_trace ('</MI_String.read>')
        return rval


class MI_BooleanA (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_BOOLEANA)
        self.value = []
        if vals is not None:
            for val in vals:
                try:
                    self.value.append (ctypes.c_bool (val))
                except:
                    self.value.append (ctypes.c_int (val))

    def write (self, fd):
        trace ('<MI_BooleanA.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                if self.value.value : 
                    tmp=1 
                else:
                    tmp=0
                buf = struct.pack ('@B',tmp)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_BooleanA.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_BooleanA.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (1)
                val = struct.unpack ('@B', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_BooleanA (vals)
        trace ('</MI_BooleanA.read>')
        return rval


class MI_Uint8A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_UINT8A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_ubyte (val))

    def write (self, fd):
        trace ('<MI_Uint8A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@B', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Uint8A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_UintA.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (1)
                val = struct.unpack ('@B', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Uint8A (vals)
        trace ('</MI_Uint8A.read>')
        return rval


class MI_Sint8A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_SINT8A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_byte (val))

    def write (self, fd):
        trace ('<MI_Sint8A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@b', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Sint8A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_SintA.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (1)
                val = struct.unpack ('@b', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Sint8A (vals)
        trace ('</MI_Sint8A.read>')
        return rval


class MI_Uint16A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_UINT16A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_ushort (val))

    def write (self, fd):
        trace ('<MI_Uint16A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@H', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Uint16A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Uint16A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (2)
                val = struct.unpack ('@H', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Uint16A (vals)
        trace ('</MI_Uint16A.read>')
        return rval


class MI_Sint16A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_SINT16A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_short (val))

    def write (self, fd):
        trace ('<MI_Sint16A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@h', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Sint16A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Sint16A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (2)
                val = struct.unpack ('@h', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Sint16A (vals)
        trace ('</MI_Sint16A.read>')
        return rval


class MI_Uint32A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_UINT32A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_uint (val))

    def write (self, fd):
        trace ('<MI_Uint32A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@I', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Uint32A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Uint32A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (4)
                val = struct.unpack ('@I', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Uint32A (vals)
        trace ('</MI_Uint32A.read>')
        return rval


class MI_Sint32A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_SINT32A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_int (val))

    def write (self, fd):
        trace ('<MI_Sint32A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('    len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@i', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Sint32A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Sint32A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (4)
                val = struct.unpack ('@i', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Sint32A (vals)
        trace ('</MI_Sint32A.read>')
        return rval


class MI_Uint64A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_UINT64A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_ulonglong (val))

    def write (self, fd):
        trace ('<MI_Uint64A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@Q', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Uint64A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Uint64A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (8)
                val = struct.unpack ('@Q', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Uint64A (vals)
        trace ('</MI_Uint64A.read>')
        return rval


class MI_Sint64A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_SINT64A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_longlong (val))

    def write (self, fd):
        trace ('<MI_Sint64A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@q', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Sint64A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Sint64A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (8)
                val = struct.unpack ('@q', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Sint64A (vals)
        trace ('</MI_Sint64A.read>')
        return rval


class MI_Real32A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_REAL32A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_float (val))

    def write (self, fd):
        trace ('<MI_Real32A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@f', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Real32A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Real32A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (4)
                val = struct.unpack ('@f', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Real32A (vals)
        trace ('</MI_Real32A.read>')
        return rval


class MI_Real64A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_REAL64A)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (ctypes.c_double (val))

    def write (self, fd):
        trace ('<MI_Real64A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('    <values>')
            for val in self.value:
                trace ('      value: ' + str(val.value))
                buf = struct.pack ('@d', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Real64A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Real64A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (8)
                val = struct.unpack ('@d', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Real64A (vals)
        trace ('</MI_Real64A.read>')
        return rval


class MI_Char16A (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_CHAR16A)
        self.value = []
        if val is not None:
            for val in vals:
                self.value.append (ctypes.c_ushort (val))

    def write (self, fd):
        trace ('<MI_Char16A.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('  <values>')
            for val in self.value:
                trace ('    value: ' + str(val.value))
                buf = struct.pack ('@H', val.value)
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG))
        trace ('</MI_Char16A.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_Char16A.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (2)
                val = struct.unpack ('@H', buf)[0]
                trace ('  value: ' + str(val))
                vals.append (val)
        rval = MI_Char16A (vals)
        trace ('</MI_Char16A.read>')
        return rval


class MI_DatetimeA (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_DATETIMEA)
        self.values = []
        for val in vals:
            self.values.append (val)

    def write (self, fd):
        trace ('<MI_DatetimeA.write>')
        MI_Value.write (self, fd)
        trace ('  len:' + str (len (self.values)))
        buf = struct.pack ('@i', len (self.values))
        fd.sendall (buf)
        for val in self.values:
            val.write_data (fd)
        trace ('</MI_Datetime.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_DatetimeA.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                val = MI_Datetime.read_data (fd)
                vals.append (val)
        rval = MI_DatetimeA (vals)
        trace ('</MI_DatetimeA.read>')
        return rval


class MI_StringA (MI_Value):
    def __init__ (self, vals):
        MI_Value.__init__ (self, MI_STRINGA)
        self.value = []
        if vals is not None:
            for val in vals:
                self.value.append (str (val))

    def write (self, fd):
        trace ('<MI_StringA.write>')
        if self.value is not None and 0 < len (self.value):
            MI_Value.write (self, fd)
            trace ('  len:' + str (len (self.value)))
            buf = struct.pack ('@i', len (self.value))
            fd.sendall (buf)
            trace ('  <values>')
            for val in self.value:
                trace('  len: ' + str(len (val)) + ', value: ' + str(val))
                buf = struct.pack ('@i', len (val))
                if type (buf) != str:
                    buf += bytes (val, 'utf8')
                else:
                    buf += val
                fd.sendall (buf)
            trace ('  </values>')
        else:
            trace ('    type: ' + str(self.type))
            fd.sendall (struct.pack ('@B', self.type | MI_NULL_FLAG)) 
        trace ('</MI_StringA.write>')

    @staticmethod
    def read (fd, flags):
        trace ('<MI_StringA.read>')
        vals = None
        if 0 == (MI_NULL_FLAG & flags):
            vals = []
            buf = fd.recv (4)
            len = struct.unpack ('@i', buf)[0]
            trace ('  len:' + str (len))
            for i in range (len):
                buf = fd.recv (4)
                len = struct.unpack ('@i', buf)[0]
                strg = ''
                if len > 0:
                    buf = fd.recv (len)
                    strg = buf.decode ('utf8')
                trace ('  value: ' + str(strg))
                vals.append (str)
        rval = MI_StringA (vals)
        trace ('</MI_StringA.read>')
        return rval
