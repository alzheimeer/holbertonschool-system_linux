#!/usr/bin/python3
"""overwrite a string in a process"""

from sys import argv

msn = "USAGE: read_write_heap.py pid search_string replace_string"


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
        with open("/proc/{:d}/mem".format(pid), "r+b") as mem:
            # read heap
            mem.seek(ini)
            numbytes = final - ini
            data = mem.read(numbytes)
            print("[*] Read {:d} bytes".format(numbytes))
            # find string
            i = data.index(bytes(search_string, "ASCII"))
            if i > -1:
                print("[*] String found at {:02X}"
                      .format(ini + i))
                mem.seek(ini + i)
                written = mem.write(bytes(replace_string, "ASCII"))
                print("[*] {:d} bytes written!".format(written))
            else:
                print(
                    "[ERROR] String '{:s}' not found in heap."
                    .format(search_string))
                exit(1)
    except Exception as e:
        print(e) or exit(1)


if __name__ == "__main__":
    if len(argv) < 4 or len(argv[2]) < len(argv[3]):
        print(msn) or exit(1)
    ini, final = search_in_maps(int(argv[1]))
    write_in_mem(int(argv[1]), argv[2], argv[3], ini, final)
