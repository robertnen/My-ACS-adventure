from .player import Player
from .box import Box
from .moves import *

from matplotlib import pyplot as plt
from typing import Optional
import yaml
import os


OBSTACLE_SYMBOL = 1
BOX_SYMBOL = 2
TARGET_SYMBOL = 3


class Map:
    '''
    Map Class records the state of the board
    where the player is, what moves can the player make, where are the boxes and where they have to go, and the obstacles.

    Attributes:
    length: length of the map
    width: width of the map
    player: player object, positioned on the map
    boxes: list of box objects, positioned on the map
    obstacles: list of obstacles given as tuples for positions on the map
    targets: list of target objects, positioned on the map
    map: 2D matrix representing the map
    explored_states: number of explored states
    undo_moves: number of undo moves made // e.g. _ P B => P B _
    '''
    def __init__(self, length, width, player_x, player_y, boxes, targets, obstacles, test_name='test'):
        self.length = length
        self.width = width
        self.map = [[0 for _ in range(width)] for _ in range(length)]
        self.obstacles = obstacles
        self.test_name = test_name

        self.explored_states = 0
        self.undo_moves = 0

        for obstacle_x, obstacle_y in self.obstacles:
            self.map[obstacle_x][obstacle_y] = OBSTACLE_SYMBOL

        self.player = Player('player', 'P', player_x, player_y)

        self.boxes = {}

        # Dictionary internally used with (x, y) as key and box_name as value
        self.positions_of_boxes = {}

        for box_name, box_x, box_y in boxes:
            self.boxes[box_name] = Box(box_name, 'B', box_x, box_y)

            self.positions_of_boxes[(box_x, box_y)] = box_name

            self.map[box_x][box_y] = BOX_SYMBOL

        self.targets = []
        for target_x, target_y in targets:
            self.targets.append((target_x, target_y))
            self.map[target_x][target_y] = TARGET_SYMBOL

    @classmethod
    def from_str(cls, state_str):
        rows = state_str.strip().split('\n')
        grid = [row.strip().split() for row in reversed(rows)]

        length = len(grid)
        width = len(grid[0]) if length > 0 else 0

        player_x = player_y = None
        boxes = []
        targets = []
        obstacles = []

        for i in range(length):
            for j in range(width):
                cell = grid[i][j]

                if cell == 'P':
                    player_x, player_y = i, j
                elif cell == '/':
                    obstacles.append((i, j))
                elif cell == 'B':
                    box_name = f"box{i}_{j}"
                    boxes.append((box_name, i, j))
                elif cell == 'X':
                    targets.append((i, j))

        return cls(length, width, player_x, player_y, boxes, targets, obstacles)


    @classmethod
    def from_yaml(cls, path):
        with open(path, 'r') as file:
            data = yaml.load(file, Loader=yaml.FullLoader)

        return cls(
            length=data['height'], 
            width=data['width'], 
            player_x=data['player'][0], 
            player_y=data['player'][1], 
            boxes=data['boxes'], 
            targets=data['targets'], 
            obstacles=data['walls'], 
            test_name=path.split('/')[-1].split('.')[0]
        )

    def object_in_bounds_move(self, checking_object, move):
        ''' Checks if the object moves inside the map'''
        if move == LEFT:
            if checking_object.y == 0:
                return False
        elif move == RIGHT:
            if checking_object.y == self.width - 1:
                return False
        elif move == DOWN:
            if checking_object.x == 0:
                return False
        elif move == UP:
            if checking_object.x == self.length - 1:
                return False
        else:
            raise ValueError('object_in_bounds_move outside range error')

        return True

    def object_valid_move(self, checking_object, move):
        ''' Checks if the object moves outside the map / hits an obstacle or a box'''

        if not self.object_in_bounds_move(checking_object, move):
            return False

        future_position = checking_object.get_future_position(move)

        if not future_position:
            raise ValueError('object_valid_move future position doesn\'t exist')

        x, y = future_position

        # Future position is outside the map
        # if x < 0 or x >= self.length or y < 0 or y >= self.width:
        #     return False

        if self.map[x][y] == OBSTACLE_SYMBOL:
            return False

        if self.map[x][y] == BOX_SYMBOL:
            return False

        return True

    def player_valid_move(self, move):
        ''' Checks if the player moves outside the map / hits an obstacle'''

        if not self.object_in_bounds_move(self.player, move):
            return False

        future_position = self.player.get_future_position(move)

        if self.map[future_position[0]][future_position[1]] == OBSTACLE_SYMBOL:
            return False

        if future_position in self.positions_of_boxes:
            box = self.boxes[self.positions_of_boxes[future_position]]
            return self.object_valid_move(box, move)

        return True

    def box_valid_move(self, move):
        '''
        Checks player moves with the box
        Player has to not hit an obstacle or another box or fall of the map
        Box has to not hit an obstacle or another box or fall of the map
        '''
            # You have to be able to apply "box_move" for both positions:
            # Example:
            # _ B P => B P _  // Forward move
            # or
            # _ P B => P B _ // Backward move

        # Moves higher than 4 highlight the player carrying the box
        # The real, implicit move is the move - 4
        implicit_move = move - 4

        if self.player_valid_move(implicit_move):
            # Player gets in the position of the box
            future_position = self.player.get_future_position(implicit_move)

            # Or player gets to an empty space and drags the box behind him
            # Case in which the box is in the opposite position of the player for the move

            straight_move_flag = False
            if self.map[future_position[0]][future_position[1]] == BOX_SYMBOL:
                straight_move_flag = self.object_valid_move(self.boxes[self.positions_of_boxes[future_position]], implicit_move)

            opposite_position = self.player.get_opposite_position(implicit_move)
            if 0 <= opposite_position[0] < self.length and 0 <= opposite_position[1] < self.width:
                if self.map[opposite_position[0]][opposite_position[1]] == BOX_SYMBOL:
                    straight_move_flag = (straight_move_flag or self.object_valid_move(self.boxes[self.positions_of_boxes[opposite_position]], implicit_move))

            return straight_move_flag

        return False

    def is_valid_move(self, move):
        ''' Checks if the move is valid'''

        # Check if the player moves outside the map / hits an obstacle
        if move < BOX_LEFT:
            return self.player_valid_move(move)
        # Check player with box moves
        elif move <= BOX_DOWN:
            return self.box_valid_move(move)
        else:
            raise ValueError('is_valid_move outside range error')

    def apply_move(self, move):
        ''' Applies the move to the map'''

        if move < BOX_LEFT:
            if self.player_valid_move(move):
                future_position = self.player.get_future_position(move)
                if self.map[future_position[0]][future_position[1]] == BOX_SYMBOL:
                    box = self.boxes[self.positions_of_boxes[future_position]]

                    # Update the position of the box in the dictionary
                    del self.positions_of_boxes[(box.x, box.y)]
                    self.map[box.x][box.y] = 0

                    box.make_move(move)
                    self.map[box.x][box.y] = BOX_SYMBOL
                    self.positions_of_boxes[(box.x, box.y)] = box.name

                self.player.make_move(move)
            else:
                raise ValueError('Apply Error: Got to make an invalid move')
        elif move <= BOX_DOWN:
            # Moves higher than 4 highlight the player carrying the box
            # The real, implicit move is the move - 4
            implicit_move = move - 4

            if self.box_valid_move(move):
                future_position = self.player.get_future_position(implicit_move)
                if future_position in self.positions_of_boxes:
                    box = self.boxes[self.positions_of_boxes[future_position]]
                else:
                    opposite_position = self.player.get_opposite_position(implicit_move)

                    if not opposite_position in self.positions_of_boxes:
                        raise ValueError('Player has to be next to the box to push it')

                    box = self.boxes[self.positions_of_boxes[opposite_position]]
                    self.undo_moves += 1

                # Update the position of the box in the dictionary
                del self.positions_of_boxes[(box.x, box.y)]
                self.map[box.x][box.y] = 0

                box.make_move(implicit_move)
                self.map[box.x][box.y] = BOX_SYMBOL
                self.positions_of_boxes[(box.x, box.y)] = box.name

                self.player.make_move(implicit_move)
            else:
                raise ValueError('Apply Error: Got to make an invalid move')
        else:
            raise ValueError('Apply Error: Got to make an invalid move')

        self.explored_states += 1

        # Regenerate the targets on the map, if the box moved off them
        for target_x, target_y in self.targets:
            if (target_x, target_y) not in self.positions_of_boxes:
                self.map[target_x][target_y] = TARGET_SYMBOL

    def is_solved(self):
        ''' Checks if all the boxes are on the targets'''
        for target_x, target_y in self.targets:
            if not (target_x, target_y) in self.positions_of_boxes:
                return False

        return True

    def filter_possible_moves(self):
        ''' Returns the possible moves the player can make'''
        possible_moves = []
        for move in range(LEFT, BOX_DOWN + 1):
            if self.is_valid_move(move):
                possible_moves.append(move)
        return possible_moves

    def copy(self):
        ''' Returns a copy of the current state'''
        new_map = Map(self.length, self.width, self.player.x, self.player.y, [(box.name, box.x, box.y) for box in self.boxes.values()], self.targets, self.obstacles)
        new_map.map = [row.copy() for row in self.map]
        new_map.positions_of_boxes = self.positions_of_boxes.copy()
        new_map.explored_states = self.explored_states
        new_map.undo_moves = self.undo_moves
        return new_map

    def get_neighbours(self):
        ''' Returns the neighbours of the current state'''
        neighbours = []
        for move in self.filter_possible_moves():
            new_map = self.copy()
            new_map.apply_move(move)
            neighbours.append(new_map)
        return neighbours

    def check_existing_folder(self, path):
        ''' Checks if the path exists, if not creates it'''

        directory = os.path.dirname(path)

        if not os.path.exists(directory):
            os.makedirs(directory)

        return path

    def save_to_yaml(self, path):
        ''' Saves the map to a yaml file'''

        path = self.check_existing_folder(path)

        data = {}
        data['height'] = self.length
        data['width'] = self.width
        data['player'] = [self.player.x, self.player.y]
        data['boxes'] = [(box.name, box.x, box.y) for box in self.boxes.values()]
        data['targets'] = self.targets
        data['walls'] = self.obstacles

        with open(path, 'w') as file:
            yaml.dump(data, file)

        print(f"Map has been saved to {path}")


    def _create_figure(
        self, 
        show: bool = True, 
        save_path: Optional[str] = None, 
        save_name: Optional[str] = None
    ) -> None:
        fig, ax = plt.subplots()
        ax.imshow(self.map, cmap='viridis')

        marker_size = 10
        ax.invert_yaxis()

        width_labels = [x - 0.5 for x in range(self.width)]
        length_labels = [y - 0.5 for y in range(self.length)]

        ax.grid(True, which='major', color='black', linewidth=1.5)
        ax.set_xticks(width_labels)
        ax.set_yticks(length_labels)
        ax.xaxis.set_ticks_position('none')
        ax.yaxis.set_ticks_position('none')
        ax.xaxis.set_ticklabels([])
        ax.yaxis.set_ticklabels([])

        ax.plot(self.player.y, self.player.x, 'ro', markersize=1.5 * marker_size)

        for box in self.boxes.values():
            ax.plot(box.y, box.x, 'bs', markersize=marker_size)

        for target_x, target_y in self.targets:
            ax.plot(target_y, target_x, 'gx', markersize=marker_size)

        if save_path:
            os.makedirs(save_path, exist_ok=True)
            if save_name is None:
                save_name = 'default.png'
            if not save_name.endswith('.png'):
                save_name += '.png'
            fig.savefig(os.path.join(save_path, save_name))

        if show:
            plt.show()

        plt.close(fig)

    def plot_map(self, save_path: Optional[str] = None, save_name: Optional[str] = None):
        self._create_figure(show=True, save_path=save_path, save_name=save_name)

    def save_map(self, save_path: str, save_name: str):
        self._create_figure(show=False, save_path=save_path, save_name=save_name)

    def __lt__(self, other):
        return str(self) < str(other)

    def __str__(self):
        ''' Overriding toString method for Map class'''
        name = ''
        for i in range(self.length):
            for j in range(self.width):
                if self.player.x == i and self.player.y == j:
                    name += f"{self.player.get_symbol()} "
                elif self.map[i][j] == 1:
                    name += f"/ "
                elif self.map[i][j] == 2:
                    name += f"B "
                elif self.map[i][j] == 3:
                    name += f"X "
                else:
                    name += f"_ "

            name += '\n'

        pieces = name.split('\n')
        aligned_corner  = reversed(pieces)
        return '\n'.join(aligned_corner)
