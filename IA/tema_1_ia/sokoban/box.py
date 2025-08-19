from .dummy import Dummy


class Box(Dummy):
    '''
    Box Class records the position of each box on the board

    Attributes:
    name: name of the box
    symbol: symbol of the box
    x: x-coordinate of the box
    y: y-coordinate of the box
    '''
    def __init__(self, name, symbol, x=0, y=0):
        self.name = name
        self.symbol = symbol
        super().__init__(x, y)

    def get_symbol(self):
        ''' Returns the symbol of the box'''
        return self.symbol
    
    def __str__(self):
        ''' Overriding toString method for Box class'''
        return f'Box named {self.name}: {self.symbol}, positioned at: ({self.x}, {self.y})'
