import Game as G

class Dots_And_Boxes(G.Game):
    def __init__(self):
        pass

    @staticmethod
    def instruction():
        G.os.system('cls')

    def draw(self):
        pass

    def play(self):
        Dots_And_Boxes.instruction()
        print("\n      ~Dots_And_Boxes遊戲開始~ >_<\n")
        G.t.sleep(3)


