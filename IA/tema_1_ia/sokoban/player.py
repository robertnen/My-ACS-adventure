from .dummy import Dummy


class Player(Dummy):
    '''
    Player Class records the position of the player on the board

    Attributes:
    name: name of the player
    symbol: symbol of the player
    x: x-coordinate of the player
    y: y-coordinate of the player
    '''
    def __init__(self, name, symbol, x=0, y=0):
        self.name = name
        self.symbol = symbol
        super().__init__(x, y)

    def get_symbol(self):
        ''' Returns the symbol of the player'''
        return self.symbol
    
    def __str__(self):
        ''' Overriding toString method for Player class'''
        return f'Player positioned at: ({self.x}, {self.y})'
