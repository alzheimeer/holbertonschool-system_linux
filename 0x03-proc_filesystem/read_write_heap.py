#!/usr/bin/python3
"""Finds & overwrites a string in a process' mem file"""

from sys import argv

USAGE = "USAGE: read_write_heap.py pid search_string replace_string"


def search_in_maps(pid):
    """search in maps file"""
    ini = final = None
    try:
        with open("/proc/{:d}/maps".format(pid), "r") as maps:
            for line in maps:
                if "heap" in line:
                    ini = line.split(" ")[0].split("-")[0]
                    final = line.split(" ")[0].split("-")[1]
                    ini = int(ini, 16)
                    final = int(final, 16)
    except Exception as e:
        print(e) or exit(1)
    if not ini or not final:
        print("[ERROR] Heap address not found.") or exit(1)
    print("[*] Heap starts at {:02X}".format(ini))
    return ini, final


def write_in_mem(pid, search_string, replace_string, ini, final):
    """finds string in mem and replace string"""
    try:
        with open("/proc/{:d}/mem".format(pid), "r+b") as f:
            f.seek(ini)
            data = f.read(final - ini)
            print("[*] Read {:d} bytes".format(final - ini))
            string_offset = data.index(bytes(search_string, "ASCII"))
            if string_offset > -1:
                print("[*] String found at {:02X}"
                      .format(ini + string_offset))
                f.seek(ini + string_offset)
                written = f.write(replace_string.encode() + b'\x00')
                print("[*] {:d} bytes written!".format(written))
            else:
                print(
                    "[ERROR] String '{:s}' not found in heap."
                    .format(search_string))
                exit(1)
    except Exception as e:
        print(e) or exit(1)


if len(argv) < 4 or len(argv[2]) < len(argv[3]):
    print(USAGE) or exit(1)
ini, final = search_in_maps(int(argv[1]))
write_in_mem(int(argv[1]), argv[2], argv[3], ini, final)
