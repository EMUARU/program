from Game import pnp, mv, cs, os, clr, t, sys, Game
from Player import Player
#class CF_Player(Player):
class CF_Player(Player):
    def __init__(self, name):
        super().__init__(name)
        self.__start_x = 20
        self.__start_y = 3
        self.__col = 3

    def player_put_chessPiece(self):
        color = {"player 1" : 0x04, "player 2" : 0x06}
        clr.set_cmd_text_color(color[self.name])
        Connect_Four.draw_newMess(x = self.__start_x,
                                  y = self.__start_y,
                                  newMess = "⇣⇣⇣")
        with pnp.keyboard.Events() as event:
            for i in event:
                key_event = i

                if isinstance(key_event, pnp.keyboard.Events.Press):
                    try:
                        if key_event.key.name == 'left':
                            if self.__start_x > 8:
                                Connect_Four.draw_newMess(x = self.__start_x,
                                                          y = self.__start_y,
                                                          newMess = "   ")
                                self.__start_x = self.__start_x - 4
                                self.__col = self.__col - 1
                        elif key_event.key.name == 'right':
                            if self.__start_x < 32:
                                Connect_Four.draw_newMess(x = self.__start_x,
                                                          y = self.__start_y,
                                                          newMess = "   ")
                                self.__start_x = self.__start_x + 4
                                self.__col = self.__col + 1
                        elif key_event.key.name == 'space':
                            Connect_Four.draw_newMess(x = self.__start_x,
                                                      y = self.__start_y,
                                                      newMess = "   ")
                            return self.__col, False 
                        elif key_event.key.name == 'esc':
                            return int(), True
                
                        Connect_Four.draw_newMess(x = self.__start_x,
                                                  y = self.__start_y,
                                                  newMess = "⇣⇣⇣")
                    except:
                        pass
#class Connect_Four(Game):
class Connect_Four(Game):
    def __init__(self):
        super().__init__([CF_Player("player 1"), CF_Player("player 2")], Connect_Four.readmap("map Connect_Four.txt"))
        self.__chessPieces = [['n', 'n', 'n', 'n', 'n', 'n', 'n'],
                              ['n', 'n', 'n', 'n', 'n', 'n', 'n'],
                              ['n', 'n', 'n', 'n', 'n', 'n', 'n'],
                              ['n', 'n', 'n', 'n', 'n', 'n', 'n'],
                              ['n', 'n', 'n', 'n', 'n', 'n', 'n'],
                              ['n', 'n', 'n', 'n', 'n', 'n', 'n']]

    @staticmethod
    def instruction():
        os.system('cls')
        clr.set_cmd_text_color(0x0a)
        print("\n      ~屏風式四子棋 遊戲介紹~ >_<\n")
        clr.set_cmd_text_color(0x0e)
        print('\n       -規則-\n\
        \n       雙方必須輪流把一枚己棋投入開口，讓棋子因地心引力落下在底部或其他棋子上。\n\
        \n       當己方四枚棋子以縱、橫、斜方向連成一線時獲勝。\n\
        \n       棋盤滿棋時，無任何連成四子，則平手。\n\
        \n\n       ~~本遊戲目前僅提供PVP模式~~')

    def choice_list(self):
        return super().choice_list(2, 18)

    def play_game(self):
        self.init_draw()
        player_id = 0
        color = [0x40, 0x60]
        while(not self.game_finish):
            mv.gotoxy(7, 25)
            clr.set_cmd_text_color(0x0b)
            print("現在是", self.players[player_id].name, "的回合")
            location, interrupt = self.put_chessPiece(self.players[player_id])
            if interrupt:
                break
            self.draw_chessPiece(location, color[player_id])
            player_id = 1 - player_id
            self.game_finish = self.check_game_finish()
        if not interrupt:
            self.finish_game()

    def init_draw(self):
        os.system('cls')
        clr.set_cmd_text_color(0x0a)
        print("\n            ~~~屏風式 四子棋~~~\n\n\n")
        for line in self.map:
            print("       " + line, end="")

        for i, p, c in [(0, 7, 0x40), (1, 23, 0x60)]:
            mv.gotoxy(p, 20)
            clr.set_cmd_text_color(0x0e)
            print(self.players[i].name, " : ", sep='')
            clr.set_cmd_text_color(c)
            self.draw_newMess(x = p + 11, y = 20, newMess = "  ")

        clr.set_cmd_text_color(0x0e)
        print("\n       使用 左右方向鍵 及 空白鍵 放置棋子吧")
        clr.set_cmd_text_color(0x0f)
        self.draw_newMess(x = 54, y = 5, newMess = ". . . 遊戲中 . . .")
        self.draw_newMess(x = 54, y = 15, newMess = "把四個棋子連成直線就贏了peko!")
        self.draw_newMess(x = 54, y = 17, newMess = "按 esc鍵 以中斷遊戲")
        
    def put_chessPiece(self, current_player:CF_Player):
        clr.set_cmd_text_color(0x0e)
        put_success = False
        color = {"player 1" : 'r', "player 2" : 'y'}
        while(not put_success):
            col, interrupt = current_player.player_put_chessPiece() #return col
            if interrupt:
                return None, interrupt
            if self.__chessPieces[0][col] == 'n':
                put_success = True
        for row in range(5, -1, -1): #row
            if self.__chessPieces[row][col] == 'n':
                self.__chessPieces[row][col] = color[current_player.name]
                break
        return (row, col), False

    def draw_chessPiece(self, location, color):
        start_x = 8 + location[1] * 4
        start_y = 6 + location[0] * 2
        clr.set_cmd_text_color(color)
        self.draw_newMess(x = start_x, y = start_y, newMess = "   ")
        self.draw_newMess(x = start_x, y = start_y + 1, newMess = "___")

    def check_game_finish(self):
        for i in range(6):
            char = self.__chessPieces[i][3]
            if  char != 'n':
                # ---
                try:
                    if self.__chessPieces[i][0] == self.__chessPieces[i][1] == self.__chessPieces[i][2] == char:
                        return self.someOne_win(char)
                except:
                    pass
                try:
                    if self.__chessPieces[i][1] == self.__chessPieces[i][2] == char == self.__chessPieces[i][4]:
                        return self.someOne_win(char)
                except:
                    pass
                try:
                    if  self.__chessPieces[i][2] == char == self.__chessPieces[i][4] == self.__chessPieces[i][5]:
                        return self.someOne_win(char)
                except:
                    pass
                try:
                    if char == self.__chessPieces[i][4] == self.__chessPieces[i][5] == self.__chessPieces[i][6]:
                        return self.someOne_win(char)
                except:
                    pass

                # \
                try:
                    if char == self.__chessPieces[i + 1][4] == self.__chessPieces[i + 2][5] == self.__chessPieces[i + 3][6]:
                        return self.someOne_win(char)
                except:
                    pass
                try:
                    if i >= 1:
                        if self.__chessPieces[i - 1][2] == char == self.__chessPieces[i + 1][4] == self.__chessPieces[i + 2][5]:
                            return self.someOne_win(char)
                except:
                    pass
                try:
                    if i >= 2:
                        if self.__chessPieces[i - 2][1] == self.__chessPieces[i - 1][2] == char == self.__chessPieces[i + 1][4]:
                            return self.someOne_win(char)
                except:
                    pass
                try:
                    if i >= 3:
                        if self.__chessPieces[i - 3][0] == self.__chessPieces[i - 2][1] == self.__chessPieces[i - 1][2] == char:
                            return self.someOne_win(char)
                except:
                    pass

                # /
                try:
                    if self.__chessPieces[i + 3][0] == self.__chessPieces[i + 2][1] == self.__chessPieces[i + 1][2] == char:
                        return self.someOne_win(char)
                except:
                    pass
                try:
                    if i >= 1:
                        if self.__chessPieces[i + 2][1] == self.__chessPieces[i + 1][2] == char == self.__chessPieces[i - 1][4]:
                            return self.someOne_win(char)
                except:
                    pass
                try:
                    if i >= 2:
                        if self.__chessPieces[i + 1][2] == char == self.__chessPieces[i - 1][4] == self.__chessPieces[i - 2][5]:
                            return self.someOne_win(char)
                except:
                    pass
                try:
                    if i >= 3:
                        if char == self.__chessPieces[i - 1][4] == self.__chessPieces[i - 2][5] == self.__chessPieces[i - 3][6]:
                            return self.someOne_win(char)
                except:
                    pass

        for j in range(7):
            char = self.__chessPieces[3][j]
            if  char != 'n':
                # |
                try:
                    if self.__chessPieces[2][j] == char == self.__chessPieces[4][j] == self.__chessPieces[5][j]:
                        return self.someOne_win(char)
                except:
                    pass
                try:
                    if self.__chessPieces[1][j] == self.__chessPieces[2][j] == char == self.__chessPieces[4][j]:
                        return self.someOne_win(char)
                except:
                    pass
                try:
                    if self.__chessPieces[0][j] == self.__chessPieces[1][j] == self.__chessPieces[2][j] == char:
                        return self.someOne_win(char)
                except:
                    pass

        #沒人贏 但還沒下完
        for i in range(6):
            for j in range(7):
                if self.__chessPieces[i][j] == 'n':
                    return False
        # 平手
        return True

    def someOne_win(self, char):
        if char == 'r':
            self.players[0].set_state("win")
        elif char == 'y':
            self.players[1].set_state("win")
        return True

    def finish_game(self):
        mv.gotoxy(54, 5)
        clr.set_cmd_text_color(0x0f)
        if self.players[0].state == "win":
            print("~~~ players 1 獲勝!!! ~~~")
        elif self.players[1].state == "win":
            print("~~~ players 2 獲勝!!! ~~~")
        else:
            print("~~~ 平手 再試一次吧 ^_^ ~~~")
        mv.gotoxy(54, 7)
        os.system('pause')