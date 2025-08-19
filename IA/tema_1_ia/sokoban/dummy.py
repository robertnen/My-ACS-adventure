from .moves import *


__all__ = ['Dummy']


class Dummy:
    '''
    Dummy Class records the position of an object on the board

    Attributes:
    x: x-coordinate of the object
    y: y-coordinate of the object
    '''
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y


    def get_future_position(self, move):
        ''' Returns the future position of the object based on the move'''
        if move == LEFT:
            return (self.x, self.y - 1)
        elif move == RIGHT:
            return (self.x, self.y + 1)
        elif move == DOWN:
            return (self.x - 1, self.y)
        elif move == UP:
            return (self.x + 1, self.y)
        else:
            raise ValueError('Move doesn\'t exist')

    def get_opposite_position(self, move):
        ''' Returns the opposite position of the object based on the move'''
        if move == LEFT:
            return (self.x, self.y + 1)
        elif move == RIGHT:
            return (self.x, self.y - 1)
        elif move == DOWN:
            return (self.x + 1, self.y)
        elif move == UP:
            return (self.x - 1, self.y)
        else:
            raise ValueError('Move doesn\'t exist')

    def make_move(self, move):
        ''' Updates the position of the object based on the move'''
        if move == LEFT:
            self.y -= 1
        elif move == RIGHT:
            self.y += 1
        elif move == DOWN:
            self.x -= 1
        elif move == UP:
            self.x += 1
        else:
            raise ValueError('Move doesn\'t exist')

    def __str__(self):
        ''' Overriding toString method for Dummy class'''
        return f'Object positioned at: ({self.x}, {self.y})'
