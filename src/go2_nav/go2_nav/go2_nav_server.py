import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer
from go2_inter.action import Nav
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Point
from .sport_model import ROBOT_SPORT_API_IDS
from unitree_api.msg import Request
import json
from rclpy.action.server import CancelResponse, GoalResponse, ServerGoalHandle
import time
from rclpy.executors import MultiThreadedExecutor


class GO2NavServer(Node):
    def __init__(self):
        super().__init__('go2_nav_server')
        self.get_logger().info('GO2 Navigation Server started')
        self.point = Point()

        self.odom_subscriber = self.create_subscription(
            Odometry,
            'odom',
            self.odom_callback,
            10
        )

        self.action_server = ActionServer(
            self,
            Nav,
            'go2_nav_action',
            self.execute_callback,
            goal_callback = self.goal_callback,
            cancel_callback= self.cancel_callback,
        )   
        self.declare_parameter("x",0.3)
        self.declare_parameter("y",0.0)
        self.declare_parameter("z",0.0)

        # speed publisher
        self.api_id = ROBOT_SPORT_API_IDS["BALANCESTAND"]
        self.req_publisher = self.create_publisher(
            Request, '/api/sport/request', 10)
        self.timer = self.create_timer(0.1, self.on_timer)  

    def on_timer(self):
        req_msg = Request()
        req_msg.header.identity.api_id = self.api_id  # Set speed level to 1 (slow)
        js = {
            "x": self.get_parameter("x").get_parameter_value().double_value,
            "y": self.get_parameter("y").get_parameter_value().double_value,
            "z": self.get_parameter("z").get_parameter_value().double_value,
        }
        req_msg.parameter = json.dumps(js)
        self.req_publisher.publish(req_msg)

    def execute_callback(self, goal_handle: ServerGoalHandle):
        feedback = Nav.Feedback()
        while rclpy.ok():
            dis_x = self.point.x - self.goal.x
            dis_y = self.point.y - self.goal.y
            dis = (dis_x**2 + dis_y**2)**0.5
            distance = goal_handle.request.goal - dis
            feedback.distance = dis

            goal_handle.publish_feedback(feedback)

            time.sleep(0.5)
            if distance < 0.1:
                goal_handle.succeed()
                self.api_id = ROBOT_SPORT_API_IDS["STOPMOVE"]
                self.get_logger().info('Goal reached')
                break
        result = Nav.Result()
        result.point = self.point
        return result


    def goal_callback(self, goal_request: Nav.Goal):
        if goal_request.goal > 0.0:
            self.goal = self.point
            self.get_logger().info('Accepted goal request')
            self.api_id = ROBOT_SPORT_API_IDS["MOVE"]
            return GoalResponse.ACCEPT
        else:
            self.api_id = ROBOT_SPORT_API_IDS["STOPMOVE"]
            self.get_logger().error('Rejected goal request: goal must be positive.')
            return GoalResponse.REJECT
        

    # at every condition
    def cancel_callback(self, goal_handle):
        self.get_logger().info('Goal canceled')
        self.api_id = ROBOT_SPORT_API_IDS["STOPMOVE"]
        return CancelResponse.ACCEPT


    def odom_callback(self, odom:Odometry):
        self.point = odom.pose.pose.position

def main(args=None):
    rclpy.init(args=args)
    node = GO2NavServer()
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    executor.spin()
    rclpy.shutdown()


if __name__ == '__main__':
    main()