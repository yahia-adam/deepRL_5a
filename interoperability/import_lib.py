import ctypes
import sys

def init_lib():
    if sys.platform == 'win32':
        lib_path = "../../myRustLib//target/release/mylib.dll"
    else:
        lib_path = "../myRustLib/target/release/libdeepRL_5a.so"

    my_lib = ctypes.cdll.LoadLibrary(lib_path)

    # -------------------------- lm --------------------------
    """ 
    add(
        a: u32,
        b: u32
    ) -> u32
    """

    my_lib.add.argtypes = [
        ctypes.c_uint32,
        ctypes.c_uint32,
    ]

    my_lib.add.restype = ctypes.c_uint32
    return my_lib

if __name__ == "__main__":
    my_lib = init_lib()
    print(my_lib.add(5,2))