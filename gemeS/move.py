import ctypes

class COORD(ctypes.Structure):
   _fields_ = [("X", ctypes.c_short), ("Y", ctypes.c_short)] 

   def __init__(self,x,y):
       self.X = x
       self.Y = y

def gotoxy(x,y):
    INIT_POS = COORD(x,y)
    STD_OUTPUT_HANDLE = -11
    hOut = ctypes.windll.kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
    ctypes.windll.kernel32.SetConsoleCursorPosition(hOut,INIT_POS)