#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>
#include <geometry_msgs/msg/twist.hpp>

class Robot
{public:
double speed=0;
double turn=0;};

Robot xiaobai;
rclcpp::Publisher<geometry_msgs::msg::Twist>::SharedPtr fasong;

void jieshou(const std_msgs::msg::Float64 &xiaoxi)
{std::cout<<"前方距离："<<xiaoxi.data<<" 米"<<std::endl;

if(xiaoxi.data<=2)
{xiaobai.speed=0;
    xiaobai.turn=0.5;
std::cout<<"小白遇障左转，speed: "<<xiaobai.speed<<" turn: "<<xiaobai.turn<<std::endl;

}
else if(xiaoxi.data<=4)
{xiaobai.speed=1;
    xiaobai.turn=0;
std::cout<<"小白减速直行，speed: "<<xiaobai.speed<<" turn: "<<xiaobai.turn<<std::endl;

}
else
{xiaobai.speed=2;
   xiaobai.turn=0;
std::cout<<"小白前进，speed: "<<xiaobai.speed<<" turn: "<<xiaobai.turn<<std::endl;

}
geometry_msgs::msg::Twist huifu;
huifu.linear.x=xiaobai.speed;
huifu.angular.z=xiaobai.turn;
fasong->publish(huifu);
}





int main(int a,char** b)
{rclcpp::init(a,b);
    auto node=rclcpp::Node::make_shared("jiedian");
    fasong=node->create_publisher<geometry_msgs::msg::Twist>(
        "cmd_vel",
        10
    );
    auto subscriber=node->create_subscription<std_msgs::msg::Float64>(
        "robot_distance",
        10,
        jieshou
    );
std::cout<<"jiedian已启动，正在等待消息..."<<std::endl;
rclcpp::spin(node);
fasong.reset();
    rclcpp::shutdown();
return 0;
}








