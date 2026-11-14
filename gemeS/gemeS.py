from Game import pnp, mv, cs, os, clr, t, sys, Game, Interrupt
from Connect_Four import Connect_Four
from Guess_The_Color import Guess_The_Color
from Dots_And_Boxes import Dots_And_Boxes

gameList = ["四子棋",
            "猜顏色",
            #"點格棋",
            "結束遊戲"]

def start():
    cs.hide()
    print("\n\n\n              ~遊戲開始~ >_<\n")
    print("               一起玩吧\n")
    t.sleep(3)

def finish():
    os.system('cls')
    mv.gotoxy(0, 0)
    print("\n\n\n              ~遊戲結束~ ^_^\n")
    print("               再來玩喔\n")
    t.sleep(3)

def choose_game():
    play = True
    while(play):
        os.system('cls')
        mv.gotoxy(0, 0)
        for gameName in gameList:
            clr.printRandomColor("\n\n       " + gameName)
        clr.printRandomColor("\n\n\n       使用 上下方向鍵 及 Enter鍵 選擇想玩的遊戲吧 (◍•ᴗ•◍)")
        play = choose()

def choose():
    oldx = x = 2
    oldy = y = 2
    Game.draw_newMess(oldx, oldy, x, y, ">>>", "   ")

    with pnp.keyboard.Events() as event:
        for i in event:
            key_event = i

            if isinstance(key_event, pnp.keyboard.Events.Press):
                try:
                    if key_event.key.name == 'up':
                        if y > 2:
                            y -= 2
                    elif key_event.key.name == 'down':
                        if y < 2 * len(gameList):
                            y += 2
                    elif key_event.key.name == 'enter':
                        choice = y // 2
                        if choice == len(gameList):
                            return False
                        else:
                            continue_play = True
                            while continue_play:
                                if choice == 1:
                                    newGame = Connect_Four()
                                elif choice == 2:
                                    newGame = Guess_The_Color()
                                elif choice == 3:
                                    newGame = Dots_And_Boxes()
                                try:
                                    continue_play = newGame.play()
                                except:
                                    pass
                            return True
                
                    Game.draw_newMess(oldx, oldy, x, y, ">>>", "   ")
                    oldy = y
                except Interrupt as itr:
                    itr.interrupt()
                except:
                    pass

if __name__ == '__main__':
    os.system("mode con cols=100 lines=30")
    start()
    choose_game()
    finish()