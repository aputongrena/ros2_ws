#include <iostream>
#include <rclcpp/rclcpp.hpp>
#include <std_msgs/msg/string.hpp>

class Robot
{public:
double speed=0;};

Robot xiaobai;
rclcpp::Publisher<std_msgs::msg::String>::SharedPtr fasong;

void jieshou(const std_msgs::msg::String &xiaoxi)
{std::cout<<"收到了消息："<<xiaoxi.data<<std::endl;
std_msgs::msg::String huifu;
if(xiaoxi.data=="前方有人")
{xiaobai.speed=0;
std::cout<<"小白停车，当前speed: "<<xiaobai.speed<<std::endl;
huifu.data="已停车";
}
else if(xiaoxi.data=="距离较近")
{xiaobai.speed=1;
std::cout<<"小白减速，当前speed: "<<xiaobai.speed<<std::endl;
huifu.data="已减速";
}
else
{xiaobai.speed=2;
   std::cout<<"小白前进，当前speed: "<<xiaobai.speed<<std::endl; 
huifu.data="正常前进";
}

fasong->publish(huifu);
}





int main(int a,char** b)
{rclcpp::init(a,b);
    auto node=rclcpp::Node::make_shared("jiedian");
    fasong=node->create_publisher<std_msgs::msg::String>(
        "robot_reply",
        10
    );
    auto subscriber=node->create_subscription<std_msgs::msg::String>(
        "robot_status",
        10,
        jieshou
    );
std::cout<<"jiedian已启动，正在等待消息..."<<std::endl;
rclcpp::spin(node);
return 0;
}








