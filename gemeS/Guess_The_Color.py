from Game import pnp, mv, cs, os, clr, t, sys, Game
from Player import Player
from random import randint
#class GTC_Player(Player):
class GTC_Player(Player):
    def __init__(self, name):
        super().__init__(name)
        self.__current_row = 0
        self.__current_color = 0
        self.__p_answer = [0x00, 0x00, 0x00, 0x00]
        self.__p_colors = (0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0)

    @property
    def p_answer(self):
        return self.__p_answer

    @staticmethod
    def draw_frame(frame_coordinate, color):
        clr.set_cmd_text_color(color)
        c_x, c_y = frame_coordinate[0], frame_coordinate[1]
        Guess_The_Color.draw_newMess(x = c_x, y = c_y, newMess = "*****")
        Guess_The_Color.draw_newMess(x = c_x, y = c_y + 3, newMess = "*****")
        star_coordinate = ((0, 1), (4, 1), (0, 2), (4, 2))
        for i, j in star_coordinate:
            Guess_The_Color.draw_newMess(x = c_x + i, y = c_y + j, newMess = "*")

    # retur row, color_no, finish, interrupt
    def player_fill_grids(self, col, first_time, fill_four):
        player_color = {"player 1" : 0x04, "player 2" : 0x06}
        init_choice_frame = (7, 5)
        init_color_frame = (7, 23)
        init_OK = (8, 21)
        OK = False
        if first_time:
            self.__current_row = self.__current_color = 0
            self.__p_answer = [0x00, 0x00, 0x00, 0x00]
        self.draw_frame([init_choice_frame[0] + col * 6, init_choice_frame[1] + self.__current_row * 4], 
                         player_color[self.name])
        self.draw_frame([init_color_frame[0] + self.__current_color * 6, init_color_frame[1]], 
                         player_color[self.name])
        if fill_four:
            clr.set_cmd_text_color(0x0a)
            Guess_The_Color.draw_newMess(x = init_OK[0] + col * 6, y = init_OK[1], newMess = "OK!")
        
        with pnp.keyboard.Events() as event:
            for i in event:
                key_event = i

                if isinstance(key_event, pnp.keyboard.Events.Press):
                    try:
                        if key_event.key.name == 'up':
                            if fill_four and OK:
                                OK = False
                                clr.set_cmd_text_color(0x0a)
                                Guess_The_Color.draw_newMess(x = init_OK[0] + col * 6, y = init_OK[1], newMess = "OK!")
                                self.draw_frame([init_choice_frame[0] + col * 6,
                                                 init_choice_frame[1] + self.__current_row * 4], 
                                                 player_color[self.name])
                            elif self.__current_row > 0:
                                self.draw_frame([init_choice_frame[0] + col * 6,
                                                 init_choice_frame[1] + self.__current_row * 4], 
                                                 0x0a)
                                self.__current_row -=1
                                self.draw_frame([init_choice_frame[0] + col * 6,
                                                 init_choice_frame[1] + self.__current_row * 4], 
                                                 player_color[self.name])
                        elif key_event.key.name == 'down':
                            if fill_four and self.__current_row == 3:
                                OK = True
                                clr.set_cmd_text_color(player_color[self.name])
                                Guess_The_Color.draw_newMess(x = init_OK[0] + col * 6, y = init_OK[1], newMess = "OK!")
                                self.draw_frame([init_choice_frame[0] + col * 6,
                                                 init_choice_frame[1] + self.__current_row * 4], 
                                                 0x0a)
                            elif self.__current_row < 3:
                                self.draw_frame([init_choice_frame[0] + col * 6,
                                                 init_choice_frame[1] + self.__current_row * 4], 
                                                 0x0a)
                                self.__current_row +=1
                                self.draw_frame([init_choice_frame[0] + col * 6,
                                                 init_choice_frame[1] + self.__current_row * 4], 
                                                 player_color[self.name])
                        elif key_event.key.name == 'left':
                            if self.__current_color > 0:
                                self.draw_frame([init_color_frame[0] + self.__current_color * 6,
                                                 init_color_frame[1]], 
                                                 0x0a)
                                self.__current_color -=1
                                self.draw_frame([init_color_frame[0] + self.__current_color * 6,
                                                 init_color_frame[1]], 
                                                 player_color[self.name])
                        elif key_event.key.name == 'right':
                            if self.__current_color < 5:
                                self.draw_frame([init_color_frame[0] + self.__current_color * 6,
                                                 init_color_frame[1]], 
                                                 0x0a)
                                self.__current_color +=1
                                self.draw_frame([init_color_frame[0] + self.__current_color * 6,
                                                 init_color_frame[1]], 
                                                 player_color[self.name])
                        elif key_event.key.name == 'space':
                            self.draw_frame([init_choice_frame[0] + col * 6,
                                             init_choice_frame[1] + self.__current_row * 4], 
                                             0x0a)
                            self.draw_frame([init_color_frame[0] + self.__current_color * 6,
                                             init_color_frame[1]], 
                                             0x0a)
                            Guess_The_Color.draw_newMess(x = init_OK[0] + col * 6, y = init_OK[1], newMess = "   ")
                            if not OK:
                                self.__p_answer[self.__current_row] = self.__p_colors[self.__current_color]
                            return self.__current_row, self.__current_color, OK, False
                        elif key_event.key.name == 'esc':
                            return int(), int(), bool(), True 
                    except:
                        pass

#class Guess_The_Color(Game):
class Guess_The_Color(Game):
    def __init__(self):
        super().__init__([GTC_Player("player 1"), GTC_Player("player 2")], Guess_The_Color.readmap("map Guess_The_Color.txt"))
        self.__colors = (0xa0, 0xb0, 0xc0, 0xd0, 0xe0, 0xf0)
        self.__answer = [0x00, 0x00, 0x00, 0x00]

    def init_colors(self, color_repeat):
        colors_no = [0, 1, 2, 3, 4, 5]
        for i in range(4):
            current_color = randint(0, len(colors_no) - 1)
            self.__answer[i] = self.__colors[colors_no[current_color]]
            if not color_repeat:
                del colors_no[current_color]

    @staticmethod
    def instruction():
        os.system('cls')
        clr.set_cmd_text_color(0x0a)
        print("\n      ~猜顏色    遊戲介紹~ >_<\n")
        clr.set_cmd_text_color(0x0e)
        print('\n       -規則-\n\
        \n       成功猜出每個格子內的顏色吧!\n\
        \n       玩家必須在八次以內猜對所有格子內的顏色，否則遊戲失敗。\n\n\
        \n       雙人模式\n\
        \n       雙方必須輪流猜測每個格子內的顏色。\n\
        \n       當一方正確猜測出每個格子內的顏色時獲勝。\n\
        \n       若在八次以內無法猜對所有格子內的顏色，則視為平手，遊戲失敗。\n\
        \n\n       ~~本遊戲提供單人及PVP模式~~')

    def choice_list(self):
        return super().choice_list(2, 25)

    def play_game(self):
        pvp_mode = self.choose_pvp_mode()
        color_repeat = self.choose_color_mode()
        self.init_colors(color_repeat)
        self.init_draw(pvp_mode)
        player_id = 0
        turn = 0                        # turn == col
        while(not self.game_finish):
            mv.gotoxy(44, 27)
            clr.set_cmd_text_color(0x0b)
            print("現在是", self.players[player_id].name, "的回合")
            interrupt = self.fill_grids(self.players[player_id], turn)
            if interrupt:
                break
            self.game_finish = self.check_game_finish(self.players[player_id], turn)
            turn += 1
            if pvp_mode:
                player_id = 1 - player_id
        if not interrupt:
            self.finish_game()

    def choose_pvp_mode(self):
        clr.set_cmd_text_color(0x0c)
        self.draw_newMess(x = 7, y = 23, newMess = "-選擇模式-")
        self.draw_newMess(x = 7, y = 25, newMess = " 單人模式")
        self.draw_newMess(x = 7, y = 27, newMess = " 雙人模式    ")
        oldx = x = 2
        oldy = y = 25
        self.draw_newMess(oldx, oldy, x, y, ">>>", "   ")
        pvp_mode = False

        with pnp.keyboard.Events() as event:
            for i in event:
                key_event = i

                if isinstance(key_event, pnp.keyboard.Events.Press):
                    try:
                        if key_event.key.name == 'up':
                            if y == 27:
                                y -= 2
                                pvp_mode = False
                        elif key_event.key.name == 'down':
                            if y == 25:
                                y += 2
                                pvp_mode = True
                        elif key_event.key.name == 'enter':
                            return pvp_mode
                
                        self.draw_newMess(oldx, oldy, x, y, ">>>", "   ")
                        oldy = y
                    except:
                        pass

    def choose_color_mode(self):
        clr.set_cmd_text_color(0x0b)
        self.draw_newMess(x = 30, y = 23, newMess = "-顏色重複-")
        self.draw_newMess(x = 30, y = 25, newMess = " 無        ")
        self.draw_newMess(x = 30, y = 27, newMess = " 有            ")
        oldx = x = 25
        oldy = y = 25
        self.draw_newMess(oldx, oldy, x, y, ">>>", "   ")
        color_repeat = False

        with pnp.keyboard.Events() as event:
            for i in event:
                key_event = i

                if isinstance(key_event, pnp.keyboard.Events.Press):
                    try:
                        if key_event.key.name == 'up':
                            if y == 27:
                                y -= 2
                                color_repeat = False
                        elif key_event.key.name == 'down':
                            if y == 25:
                                y += 2
                                color_repeat = True
                        elif key_event.key.name == 'enter':
                            return color_repeat
                
                        self.draw_newMess(oldx, oldy, x, y, ">>>", "   ")
                        oldy = y
                    except:
                        pass

    def init_draw(self, pvp_mode):
        os.system('cls')
        clr.set_cmd_text_color(0x0a)
        print("\n                         ~~~猜顏色~~~\n\n\n")
        for line in self.map:
            print("       " + line, end="")
        mv.gotoxy(7, 3)
        if not pvp_mode:
            print("  1  >  2  >  3  >  4  >  5  >  6  >  7  >  8")
        else:
            print("  1P >  2P >  1P >  2P >  1P >  2P >  1P >  2P")
        player_list = [(0, 44, 0x40), (1, 60, 0x60)] if pvp_mode else  [(0, 44, 0x40)]
        for i in range(6):
            clr.set_cmd_text_color(self.__colors[i])
            self.draw_newMess(x = i * 6 + 8, y = 24, newMess = "   ")
            self.draw_newMess(x = i * 6 + 8, y = 25, newMess = "   ")

        for i, p, c in player_list:
            mv.gotoxy(p, 23)
            clr.set_cmd_text_color(0x0e)
            print(self.players[i].name, " : ", sep='')
            clr.set_cmd_text_color(c)
            self.draw_newMess(x = p + 11, y = 23, newMess = "  ")

        clr.set_cmd_text_color(0x0e)
        self.draw_newMess(x = 44, y = 25, newMess = "使用 上下左右方向鍵 及 空白鍵 填入顏色吧")
        clr.set_cmd_text_color(0x0f)
        self.draw_newMess(x = 68, y = 5, newMess = ". . . 遊戲中 . . .")
        self.draw_newMess(x = 68, y = 11, newMess = "每次猜測的左 右下方分別會顯示")
        self.draw_newMess(x = 68, y = 13, newMess = "左下:位置與顏色都猜對的格子數")
        self.draw_newMess(x = 68, y = 15, newMess = "右下:只有顏色猜對的格子數")
        self.draw_newMess(x = 68, y = 17, newMess = "猜對所有顏色就贏了peko!")
        self.draw_newMess(x = 68, y = 19, newMess = "按 esc鍵 以中斷遊戲")
        
    def fill_grids(self, current_player:GTC_Player, col):
        first_time = True
        fill_four = False
        finish = False
        while(not(fill_four and finish)):
            row, color_no, finish, interrupt = current_player.player_fill_grids(col, first_time, fill_four) # 一次放一格
            if interrupt:
                return interrupt
            if not finish:
                self.draw_grid_color((row, col), color_no)
                first_time = False
                if current_player.p_answer[0] != 0x00 and current_player.p_answer[1] != 0x00 and\
                   current_player.p_answer[2] != 0x00 and current_player.p_answer[3] != 0x00:
                    fill_four = True
        return False

    def draw_grid_color(self, location, color_no):
        clr.set_cmd_text_color(self.__colors[color_no])
        c_y, c_x = 6 + location[0] * 4, 8 + location[1] * 6
        for i in range(2):
            Guess_The_Color.draw_newMess(x = c_x, y = c_y + i, newMess = "   ")

    def check_game_finish(self, current_player:GTC_Player, col):
        if current_player.p_answer == self.__answer:
            return self.someOne_win(current_player.name)
        ac = 0
        for i in range(4):
            if current_player.p_answer[i] == self.__answer[i]:
                ac += 1

        ans = [0, 0, 0, 0, 0, 0]
        p_ans = [0, 0, 0, 0, 0, 0]
        for i in range(4):
            if self.__answer[i] == 0xa0:
                ans[0] += 1
            elif self.__answer[i] == 0xb0:
                ans[1] += 1
            elif self.__answer[i] == 0xc0:
                ans[2] += 1
            elif self.__answer[i] == 0xd0:
                ans[3] += 1
            elif self.__answer[i] == 0xe0:
                ans[4] += 1
            elif self.__answer[i] == 0xf0:
                ans[5] += 1
            if current_player.p_answer[i] == 0xa0:
                p_ans[0] += 1
            elif current_player.p_answer[i] == 0xb0:
                p_ans[1] += 1
            elif current_player.p_answer[i] == 0xc0:
                p_ans[2] += 1
            elif current_player.p_answer[i] == 0xd0:
                p_ans[3] += 1
            elif current_player.p_answer[i] == 0xe0:
                p_ans[4] += 1
            elif current_player.p_answer[i] == 0xf0:
                p_ans[5] += 1

        same_color = 0
        for i in range(6):
            same_color += min(ans[i], p_ans[i])

        same_color -= ac
        clr.set_cmd_text_color(0x0c)
        self.draw_newMess(x = 8 + col * 6, y = 21, newMess = str(ac))
        clr.set_cmd_text_color(0x08)
        self.draw_newMess(x = 10 + col * 6, y = 21, newMess = str(same_color))
        clr.set_cmd_text_color(0x0e)
        mv.gotoxy(68, 7)
        print(ac, "個全對  ", same_color, "個半對", sep='')
        t.sleep(2)
        self.draw_newMess(x = 68, y = 7, newMess = "                ")
        if col == 7:
            return True
        return False

    def someOne_win(self, player_name):
        if player_name == "player 1":
            self.players[0].set_state("win")
        elif player_name == "player 2":
            self.players[1].set_state("win")
        return True

    def finish_game(self):
        for i in range(3):
            for j in range(4):
                clr.set_cmd_text_color(self.__answer[j])
                self.draw_newMess(x = 61 - i, y = 6 + 4 * j, newMess = ' ')
                self.draw_newMess(x = 61 - i, y = 7 + 4 * j, newMess = ' ')
            t.sleep(1)

        mv.gotoxy(68, 5)
        clr.set_cmd_text_color(0x0f)
        if self.players[0].state == "win":
            print("~~~ players 1 獲勝!!! ~~~")
        elif self.players[1].state == "win":
            print("~~~ players 2 獲勝!!! ~~~")
        else:
            print("~~ 挑戰失敗 再試一次吧 ^_^ ~~")
        mv.gotoxy(68, 7)
        os.system('pause')