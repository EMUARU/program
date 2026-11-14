#! /usr/bin/env python
#coding=utf-8
import ctypes, sys, os
from random import choice
STD_INPUT_HANDLE = -10
STD_OUTPUT_HANDLE = -11
STD_ERROR_HANDLE = -12
# 字型顏色定義 ,關鍵在於顏色編碼,由2位十六進位制組成,分別取0~f,前一位指的是背景色,後一位指的是字型色
#由於該函式的限制,應該是隻有這16種,可以前景色與背景色組合。也可以幾種顏色通過或運算組合,組合後還是在這16種顏色中
# Windows CMD命令列 字型顏色定義 text colors
FOREGROUND_BLACK = 0x00 # black.
FOREGROUND_DARKBLUE = 0x01 # dark blue.
FOREGROUND_DARKGREEN = 0x02 # dark green.
FOREGROUND_DARKSKYBLUE = 0x03 # dark skyblue.
FOREGROUND_DARKRED = 0x04 # dark red.
FOREGROUND_DARKPINK = 0x05 # dark pink.
FOREGROUND_DARKYELLOW = 0x06 # dark yellow.
FOREGROUND_DARKWHITE = 0x07 # dark white.
FOREGROUND_DARKGRAY = 0x08 # dark gray.
FOREGROUND_BLUE = 0x09 # blue.
FOREGROUND_GREEN = 0x0a # green.
FOREGROUND_SKYBLUE = 0x0b # skyblue.
FOREGROUND_RED = 0x0c # red.
FOREGROUND_PINK = 0x0d # pink.
FOREGROUND_YELLOW = 0x0e # yellow.
FOREGROUND_WHITE = 0x0f # white.

# Windows CMD命令列 背景顏色定義 background colors
BACKGROUND_BLUE = 0x10 # dark blue.
BACKGROUND_GREEN = 0x20 # dark green.
BACKGROUND_DARKSKYBLUE = 0x30 # dark skyblue.
BACKGROUND_DARKRED = 0x40 # dark red.
BACKGROUND_DARKPINK = 0x50 # dark pink.
BACKGROUND_DARKYELLOW = 0x60 # dark yellow.
BACKGROUND_DARKWHITE = 0x70 # dark white.
BACKGROUND_DARKGRAY = 0x80 # dark gray.
BACKGROUND_BLUE = 0x90 # blue.
BACKGROUND_GREEN = 0xa0 # green.
BACKGROUND_SKYBLUE = 0xb0 # skyblue.
BACKGROUND_RED = 0xc0 # red.
BACKGROUND_PINK = 0xd0 # pink.
BACKGROUND_YELLOW = 0xe0 # yellow.
BACKGROUND_WHITE = 0xf0 # white.

# get handle
std_out_handle = ctypes.windll.kernel32.GetStdHandle(STD_OUTPUT_HANDLE)
def set_cmd_text_color(color, handle=std_out_handle):
    Bool = ctypes.windll.kernel32.SetConsoleTextAttribute(handle, color)
    return Bool
#reset white
def resetColor():
    set_cmd_text_color(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE)
###############################################################
#暗藍色
#dark blue
def printDarkBlue(mess):
    set_cmd_text_color(FOREGROUND_DARKBLUE)
    sys.stdout.write(mess)
    resetColor()
#暗綠色
#dark green
def printDarkGreen(mess):
    set_cmd_text_color(FOREGROUND_DARKGREEN)
    sys.stdout.write(mess)
    resetColor()
#暗天藍色
#dark sky blue
def printDarkSkyBlue(mess):
    set_cmd_text_color(FOREGROUND_DARKSKYBLUE)
    sys.stdout.write(mess)
    resetColor()
#暗紅色
#dark red
def printDarkRed(mess):
    set_cmd_text_color(FOREGROUND_DARKRED)
    sys.stdout.write(mess)
    resetColor()
#暗粉紅色
#dark pink
def printDarkPink(mess):
    set_cmd_text_color(FOREGROUND_DARKPINK)
    sys.stdout.write(mess)
    resetColor()
#暗黃色
#dark yellow
def printDarkYellow(mess):
    set_cmd_text_color(FOREGROUND_DARKYELLOW)
    sys.stdout.write(mess)
    resetColor()
#暗白色
#dark white
def printDarkWhite(mess):
    set_cmd_text_color(FOREGROUND_DARKWHITE)
    sys.stdout.write(mess)
    resetColor()
#暗灰色
#dark gray
def printDarkGray(mess):
    set_cmd_text_color(FOREGROUND_DARKGRAY)
    sys.stdout.write(mess)
    resetColor()
#藍色
#blue
def printBlue(mess):
    set_cmd_text_color(FOREGROUND_BLUE)
    sys.stdout.write(mess)
    resetColor()
#綠色
#green
def printGreen(mess):
    set_cmd_text_color(FOREGROUND_GREEN)
    sys.stdout.write(mess)
    resetColor()
#天藍色
#sky blue
def printSkyBlue(mess):
    set_cmd_text_color(FOREGROUND_SKYBLUE)
    sys.stdout.write(mess)
    resetColor()
#紅色
#red
def printRed(mess):
    set_cmd_text_color(FOREGROUND_RED)
    sys.stdout.write(mess)
    resetColor()
#粉紅色
#pink
def printPink(mess):
    set_cmd_text_color(FOREGROUND_PINK)
    sys.stdout.write(mess)
    resetColor()
#黃色
#yellow
def printYellow(mess):
    set_cmd_text_color(FOREGROUND_YELLOW)
    sys.stdout.write(mess)
    resetColor()
#白色
#white
def printWhite(mess):
    set_cmd_text_color(FOREGROUND_WHITE)
    sys.stdout.write(mess)
    resetColor()
#自定義顏色
#Custom
def printCustomColor(mess, clr):
    set_cmd_text_color(clr)
    sys.stdout.write(mess)
    resetColor()
#隨機顏色
#Random
def printRandomColor(mess):
    clr = choice([0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f])
    set_cmd_text_color(clr)
    sys.stdout.write(mess)
    resetColor()   
##################################################
#白底黑字
#white bkground and black text
def printWhiteBlack(mess):
    set_cmd_text_color(FOREGROUND_BLACK | BACKGROUND_WHITE)
    sys.stdout.write(mess)
    resetColor()
#白底黑字
#white bkground and black text
def printWhiteBlack_2(mess):
    set_cmd_text_color(0xf0)
    sys.stdout.write(mess)
    resetColor()
#粉底藍字
#Pink bkground and Blue text
def printPinkBlue(mess):
    set_cmd_text_color(0xd9)
    sys.stdout.write(mess)
    resetColor()
##############################################################
if __name__ == '__main__':
    printDarkBlue('printDarkBlue:暗藍色文字\n')
    printDarkGreen('printDarkGreen:暗綠色文字\n')
    printDarkSkyBlue('printDarkSkyBlue:暗天藍色文字\n')
    printDarkRed('printDarkRed:暗紅色文字\n')
    printDarkPink('printDarkPink:暗粉紅色文字\n')
    printDarkYellow('printDarkYellow:暗黃色文字\n')
    printDarkWhite('printDarkWhite:暗白色文字\n')
    printDarkGray('printDarkGray:暗灰色文字\n')
    printBlue('printBlue:藍色文字\n')
    printGreen('printGreen:綠色文字\n')
    printSkyBlue('printSkyBlue:天藍色文字\n')
    printRed('printRed:紅色文字\n')
    printPink('printPink:粉紅色文字\n')
    printYellow('printYellow:黃色文字\n')
    printWhite('printWhite:白色文字\n')
    printCustomColor('printCustomColor:自定義色文字\n', 0xb2)
    printWhiteBlack('printWhiteBlack:白底黑字輸出\n')
    printWhiteBlack_2('printWhiteBlack_2:白底黑字輸出(直接傳入16進位制引數)\n')
    printPinkBlue('printYellowRed:粉底藍字輸出\n')
    set_cmd_text_color(0x60)
    print("  ")
    set_cmd_text_color(0x40)
    print("  ")
    set_cmd_text_color(0xa0)
    print("  ")
    set_cmd_text_color(0xb0)
    print("  ")
    set_cmd_text_color(0xc0)
    print("  ")
    set_cmd_text_color(0xd0)
    print("  ")
    set_cmd_text_color(0xe0)
    print("  ")
    set_cmd_text_color(0xf0)
    print("  ")
    os.system("pause")