import rclpy
from rclpy.node import Node

class GO2NavClient(Node):
    def __init__(self):
        super().__init__('go2_nav_client')
        self.get_logger().info('GO2 Navigation Client started')


def main(args=None):
    rclpy.init(args=args)
    node = GO2NavClient()
    rclpy.spin(node)
    rclpy.shutdown()


if __name__ == '__main__':
    main()