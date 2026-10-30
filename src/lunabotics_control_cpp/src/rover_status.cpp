#include <chrono>
#include <memory>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"

using namespace std::chrono_literals;

class RoverStatus : public rclcpp::Node
{
public:
    RoverStatus() : Node("rover_status")
    {
        publisher_ = create_publisher<std_msgs::msg::String>(
            "rover_status", 10);

        timer_ = create_wall_timer(
            1s,
            [this]() {
                auto message = std_msgs::msg::String();
                message.data = "Lunabotics rover systems operational";

                publisher_->publish(message);

                RCLCPP_INFO(
                    get_logger(),
                    "%s",
                    message.data.c_str());
            });

        RCLCPP_INFO(get_logger(), "Rover status node started");
    }

private:
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char * argv[])
{
    rclcpp::init(argc, argv);

    rclcpp::spin(std::make_shared<RoverStatus>());

    rclcpp::shutdown();
    return 0;
}