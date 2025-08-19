from sokoban import (
    Box,
    DOWN,
    Map,
    Player
)


if __name__ == '__main__':
    
    # Maps can be created using the Map class
    map_from_init = Map(7, 10, 0, 0, [('box1', 3, 3), ('box2', 4, 5)], [(5, 6), (6, 8)], [(2, 4), (3, 4), (4, 4), (5, 2), (5, 3), (6, 2), (3, 7), (4, 7)], 'large_map1')

    # Maps can be created through yaml files
    map_from_yaml = Map.from_yaml('tests/large_map1.yaml')

    assert str(map_from_init) == str(map_from_yaml), "Reading from yaml file Failed"

    # Maps can also be created from their string representation
    map_str = str(map_from_init)
    map_from_str = Map.from_str(map_str)

    assert str(map_from_init) == str(map_from_str), "String conversion Failed"

    plot_flag = False
    crt_map = map_from_init

    if plot_flag:
        crt_map.plot_map()
    else:
        print(crt_map)
        print(f"Is solved: {crt_map.is_solved()}")
        print("Neighbours:")
        for neighbour in crt_map.get_neighbours():
            print(neighbour)
