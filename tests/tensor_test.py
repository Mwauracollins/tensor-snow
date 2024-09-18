import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../t-snow')))

from tensor.tensor import create_tensor, tensor_get_item
def test_create_tensor():
    t = create_tensor([1.0, 2.0, 3.0, 4.0], [4])
    assert tensor_get_item(t, [2]) == 3.0