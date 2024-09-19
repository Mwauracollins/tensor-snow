import ctypes
import os

lib_ext = ".dll" if os.name == "nt" else ".so"
lib_path = os.path.join(os.path.dirname(__file__), '../../build/libtensor' + lib_ext)

tensor_lib = ctypes.CDLL(lib_path)


class Tensor(ctypes.Structure):
    _fields_ = [
        ("data", ctypes.POINTER(ctypes.c_float)),
        ("shape", ctypes.POINTER(ctypes.c_int)),
        ("ndim", ctypes.c_int),
        ("strides", ctypes.POINTER(ctypes.c_int)),
        ("size", ctypes.c_int),
    ]

# Bind the C++ functions
tensor_lib.createTensor.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.POINTER(ctypes.c_int), ctypes.c_int]
tensor_lib.createTensor.restype = ctypes.POINTER(Tensor)

tensor_lib.tensorGetItem.argtypes = [ctypes.POINTER(Tensor), ctypes.POINTER(ctypes.c_int)]
tensor_lib.tensorGetItem.restype = ctypes.c_float

def create_tensor(data, shape):
    """Creates a Tensor object using the C++ function."""
    data_array = (ctypes.c_float * len(data))(*data)
    shape_array = (ctypes.c_int * len(shape))(*shape)
    tensor = tensor_lib.createTensor(data_array, shape_array, len(shape))
    return tensor

def tensor_get_item(tensor, indices):
    """Fetches an item from the Tensor."""
    indices_array = (ctypes.c_int * len(indices))(*indices)
    return tensor_lib.tensorGetItem(tensor, indices_array)

if __name__ == "__main__":
    t = create_tensor([1.0, 2.0, 3.0, 4.0], [4])
    print(tensor_get_item(t, [2]))  
