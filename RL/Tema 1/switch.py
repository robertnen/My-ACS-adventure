#!/usr/bin/python3
import sys
import struct
import wrapper
import threading
import time
import os
from wrapper import recv_from_any_link, send_to_link, get_switch_mac, get_interface_name

ADDON = 10
DEBUG = False
TRUNK = 'T'
BLOCKED = False
LISTEN = True
SWITCH_PATH = 'configs/switch'
SWTICH_CONF_EXTENSION = '.cfg'

def parse_ethernet_header(data):
    # Unpack the header fields from the byte array
    #dest_mac, src_mac, ethertype = struct.unpack('!6s6sH', data[:14])
    dest_mac = data[0:6]
    src_mac = data[6:12]

    # Extract ethertype. Under 802.1Q, this may be the bytes from the sw_inface TAG
    ether_type = (data[12] << 8) + data[13]

    id = -1
    # Check for sw_inface tag (0x8100 in network byte order is b'\x81\x00')
    if ether_type == 0x8200:
        sw_inface_tci = int.from_bytes(data[14:16], byteorder='big')
        id = sw_inface_tci & 0x0FFF  # extract the 12-bit sw_inface ID
        ether_type = (data[16] << 8) + data[17]

    return dest_mac, src_mac, ether_type, id

def create_vlan_tag(id):
    # 0x8100 for the Ethertype for 802.1Q
    # id & 0x0FFF ensures that only the last 12 bits are used
    return struct.pack('!H', 0x8200) + struct.pack('!H', id & 0x0FFF)

def send_bdpu_every_sec() -> None:
    global interfaces, ports, sw_inface, root_id, cost, bridge_id

    while True:
        if bridge_id != root_id:
            continue

        for interface in interfaces:
            if check_trunk(sw_inface, interface):
                data = struct.pack('!BBBBBB', 0x01, 0x80, 0xc2, 0x00, 0x00, 0x00) \
                        + struct.pack('!q', bridge_id) \
                        + struct.pack('!q', root_id) \
                        + struct.pack('!I', cost)

                length =  len(data)
                send_to_link(interface, length, data)

        time.sleep(1)

#* reads the configuration for each switch
def start_switch(switch_id: str) -> tuple[dict[str, str], int, int]:
    file_path = SWITCH_PATH + switch_id + SWTICH_CONF_EXTENSION

    if not os.path.exists(file_path):
        print(f'File path doesn\'t exist or can\'t be accessed. ({file_path})')
        exit(1)

    #? file content
    #* id
    #* rr_A_B T
    #* rr_C_D T
    #* r_E vlan_id
    #* r_F vlan_id
    #* .....
    fin = open(file_path, 'r')
    bridge_id = int(fin.readline())
    root_id = bridge_id

    sw_inface = {}

    for line in fin:
        ith = line.split()[0]
        id = line.split()[1]
        sw_inface[ith] = id

    return sw_inface, bridge_id, root_id

#* if the id is from a host it converts it to int or it replaces with 0 (trunk)
def convert_id(id: str) -> int:
    return 0 if id == TRUNK else int(id)

#! for me because I forget a lot
#* IEEE 802.1Q frame
#*  Destination MAC  |     Source Mac    |   Vlan Id   |       Payload     |
#*  1  2  3  4  5  6 |  1  2  3  4  5  6 |  1  2  3  4 |  1  .  .  .   n   |
#*  0  1  2  3  4  5 |  6  7  8  9 10 11 | 12 13 14 15 | 16  .  .  . n + 16|
#?               -> it removes this thing ^^^^^^^^^^^^^
def remove_vlan_id(frame: str) -> str:
    return frame[0:12] + frame[16:]

#! for me because I forget a lot
#* IEEE 802.1Q frame
#*  Destination MAC  |     Source Mac    |   Vlan Id   |       Payload     |
#*  1  2  3  4  5  6 |  1  2  3  4  5  6 |  1  2  3  4 |  1  .  .  .   n   |
#*  0  1  2  3  4  5 |  6  7  8  9 10 11 | 12 13 14 15 | 16  .  .  . n + 16|
#?                  -> it puts this thing ^^^^^^^^^^^^^
def add_vland_id(frame: str, id: int) -> str:
    return frame[0:12] + create_vlan_tag(id) + frame[12:]

#* verify if the resource is a trunk
def check_trunk(sw_inface: dict[str, str], inface: str) -> bool:
    return sw_inface.get(get_interface_name(inface)) == TRUNK

#* remove (possible) loops
def stp(interface: str, data: str) -> None:
    global root_id, cost, bridge_id, interfaces, ports, sw_inface, root_port

    #* get bpdu information
    src_bid = int.from_bytes(data[6:14], byteorder='big')
    root_bid = int.from_bytes(data[14:22], byteorder='big')
    path_cost = int.from_bytes(data[22:26], byteorder='big')

    #? check if the current switch the root
    is_root = False
    if bridge_id == root_id:
        is_root = True

    #* check if there is a new root
    if root_bid < root_id:
        root_id = root_bid
        cost = path_cost + ADDON
        root_port = interface

        #* block every port which is not a root
        if is_root:
            for inface in interfaces:
                if inface != root_port and check_trunk(sw_inface, inface):
                    ports[inface] = BLOCKED

        #* if blocked, unlock the root port
        if ports[root_port] == BLOCKED:
                    ports[root_port] = LISTEN

        #? bpdu packet to send
        data = struct.pack('!BBBBBB', 0x01, 0x80, 0xc3, 0x00, 0x00, 0x00) \
                        + struct.pack('!q', bridge_id) \
                        + struct.pack('!q', root_id) \
                        + struct.pack('!I', cost)

        length = len(data)

        #* send bpdu to the other ports
        for inface in interfaces:
            if inface != root_port and check_trunk(sw_inface, inface):
                send_to_link(inface, length, data)

    #* check if the path cost is different
    elif root_bid == root_id:
        if interface == root_port and path_cost + ADDON < cost:
            cost = path_cost + ADDON
        elif interface != root_port and path_cost > cost:
            ports[interface] = LISTEN

    #* check if the bridge is the source
    elif src_bid == bridge_id:
        ports[interface] = BLOCKED

    #* root has to listen
    if bridge_id == root_id:
        for inface in interfaces:
            if inface != root_port and check_trunk(sw_inface, inface):
                ports[inface] = LISTEN

def main():
    global root_id, cost, bridge_id, interfaces, ports, sw_inface, root_port

    cost = 0
    mac_table = {}
    root_port = None
    switch_id = sys.argv[1]
    num_interfaces = wrapper.init(sys.argv[2:])

    interfaces = range(0, num_interfaces)
    ports = [LISTEN] * num_interfaces

    sw_inface, bridge_id, root_id = start_switch(switch_id)

    t = threading.Thread(target=send_bdpu_every_sec)
    t.start()

    while True:
        interface, data, length = recv_from_any_link()
        if ports[interface] == BLOCKED:
            continue

        if DEBUG:
            print(f'mac_table = {mac_table}')
            print(f'sw_inface = {sw_inface}')
            print(f'switch_id = {switch_id}')
            print(f'bridge_id = {bridge_id}')
            print(f'root_id = {root_id}')
            print(f'cost = {cost}')
            print(f'num_interfaces = {num_interfaces}')
            print(f'interfaces = {interfaces}')
            print(f'port_state = {ports}')

        #* check if BPDU (01:80:C2:00:00 multicast addr)
        if data[0:6] == b'\x01\x80\xc2\x00\x00\x00':
            stp(interface, data)
            continue

        dest_mac, src_mac, ethertype, id = parse_ethernet_header(data)

        if id == -1:
            id = sw_inface.get(get_interface_name(interface))
            id = convert_id(id)

        mac_table[src_mac] = interface

        sw_inface_src = sw_inface.get(get_interface_name(interface))
        sw_inface_src = convert_id(sw_inface_src)

        if sw_inface_src == 0:
            data_standard = remove_vlan_id(data)
        else:
            length = length + 4
            data_standard = data
            data = add_vland_id(data, id)

        if dest_mac[0] & 1 == 0 and dest_mac in mac_table:
            dest_type = sw_inface.get(get_interface_name(mac_table.get(dest_mac)))
            dest_type = convert_id(dest_type)

            length = length - 4 if dest_type != 0 else length
            data = data_standard if dest_type != 0 else data

            send_to_link(mac_table.get(dest_mac), length, data)
        else:
            for inface in interfaces:
                if inface != interface and ports[inface]:
                    dest_type = sw_inface.get(get_interface_name(inface))
                    dest_type = convert_id(dest_type)
                    if dest_type == 0:
                        send_to_link(inface, length, data)
                    elif dest_type == id:
                        send_to_link(inface, length - 4, data_standard)


if __name__ == "__main__":
    main()