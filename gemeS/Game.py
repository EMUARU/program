import pynput as pnp, move as mv, cursor as cs, os, color as clr, time as t, sys
from Interrupt import Interrupt
from abc import ABC, abstractmethod
#class Game
class Game(ABC):
    def __init__(self, players, map):
        self.__players = players
        self.__map = map
        self.__game_finish = False

    @property
    def players(self):
        return self.__players

    @property
    def map(self):
        return self.__map

    @property
    def game_finish(self):
        return self.__game_finish

    @game_finish.setter
    def game_finish(self, game_finish):
        self.__game_finish = game_finish

    @abstractmethod
    def instruction(self):
        pass

    def play(self):
        self.instruction()
        return self.choice_list()
    
    @staticmethod
    def readmap(map_name:str):
        try:
            with open(map_name, mode="r") as file:
                for line in file:
                    map = file.readlines()
        except:
            os.system('cls')
            mv.gotoxy(0, 0)
            print("\n\n\n              no map\n\n              ", end='')
            os.system('pause')
            raise Interrupt
        return map

    def choice_list(self, init_x, init_y):
        clr.set_cmd_text_color(0x0b)
        print("\n\n       -選單-")
        print("\n        開始遊戲\n\
        \n        返回遊戲選單")
        return self.choose_choice_list(init_x, init_y)

    def choose_choice_list(self, init_x, init_y):
        oldx = x = init_x
        oldy = y = init_y
        self.draw_newMess(oldx, oldy, x, y, ">>>", "   ")

        with pnp.keyboard.Events() as event:
            for i in event:
                key_event = i

                if isinstance(key_event, pnp.keyboard.Events.Press):
                    try:
                        if key_event.key.name == 'up':
                            if y == init_y + 2:
                                y -= 2
                        elif key_event.key.name == 'down':
                            if y == init_y:
                                y += 2
                        elif key_event.key.name == 'enter':
                            choice = (y - (init_y - init_x)) // 2

                            if choice == 1:
                                self.play_game()
                                return True
                            elif choice == 2:
                                return False
                
                        self.draw_newMess(oldx, oldy, x, y, ">>>", "   ")
                        oldy = y
                    except:
                        pass

    @staticmethod
    def draw_newMess(oldx = 0, oldy = 0, x = 0, y = 0, newMess = "", clear = ""):
        cs.hide()
        mv.gotoxy(oldx, oldy)
        print(clear)
        mv.gotoxy(x, y)
        print(newMess)

    @abstractmethod
    def play_game(self):
        pass

    @abstractmethod
    def init_draw(self):
        pass

    @abstractmethod
    def check_game_finish(self):
        pass

    @abstractmethod
    def finish_game(self):
        pass