import sys
if sys.prefix == '/usr':
    sys.real_prefix = sys.prefix
    sys.prefix = sys.exec_prefix = '/home/m2m/Unitree_GO2_ws/install/go2_ctrl'
