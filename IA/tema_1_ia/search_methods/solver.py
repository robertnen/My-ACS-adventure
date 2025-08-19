from sokoban.map import Map


class Solver:

    def __init__(self, map: Map) -> None:
        self.map = map

    def solve(self):
        raise NotImplementedError
