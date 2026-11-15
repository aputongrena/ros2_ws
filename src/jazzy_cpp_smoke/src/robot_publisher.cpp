#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>
#include <chrono>

int main(int a,char** b)
{rclcpp::init(a,b);
auto node=rclcpp::Node::make_shared("robot_publisher");
auto publisher=node->create_publisher<std_msgs::msg::String>(
"robot_status",
10
);

std_msgs::msg::String message;
message.data="机器人准备完毕";
rclcpp::sleep_for(std::chrono::seconds(2));
publisher->publish(message);


rclcpp::shutdown();
return 0;
}








