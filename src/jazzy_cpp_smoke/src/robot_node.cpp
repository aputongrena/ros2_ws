#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/float64.hpp>

class Robot
{public:
double speed=0;};

Robot xiaobai;
rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr fasong;

void jieshou(const std_msgs::msg::Float64 &xiaoxi)
{std::cout<<"收到了消息："<<xiaoxi.data<<std::endl;

if(xiaoxi.data<=2)
{xiaobai.speed=0;
std::cout<<"小白停车，当前speed: "<<xiaobai.speed<<std::endl;

}
else if(xiaoxi.data<=4)
{xiaobai.speed=1;
std::cout<<"小白减速，当前speed: "<<xiaobai.speed<<std::endl;

}
else
{xiaobai.speed=2;
   std::cout<<"小白前进，当前speed: "<<xiaobai.speed<<std::endl; 

}
std_msgs::msg::Float64 huifu;
huifu.data=xiaobai.speed;
fasong->publish(huifu);
}





int main(int a,char** b)
{rclcpp::init(a,b);
    auto node=rclcpp::Node::make_shared("jiedian");
    fasong=node->create_publisher<std_msgs::msg::Float64>(
        "robot_speed",
        10
    );
    auto subscriber=node->create_subscription<std_msgs::msg::Float64>(
        "robot_distance",
        10,
        jieshou
    );
std::cout<<"jiedian已启动，正在等待消息..."<<std::endl;
rclcpp::spin(node);
return 0;
}








