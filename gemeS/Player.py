#class Player
class Player():
    def __init__(self, name):
        self.__name = name
        self.__state = "none"

    @property
    def name(self):
        return self.__name

    @property
    def state(self):
        return self.__state

    def set_state(self, new_state):
        self.__state = new_state