import move as mv, os, time as t, sys

class Interrupt(Exception):
    def interrupt(self):
        print("\n              ~遊戲中斷~ @_@\n\n              ", end='')
        t.sleep(2)
        sys.exit(0)