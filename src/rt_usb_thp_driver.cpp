#include "ros/ros.h"
// #include "serial/serial.h"
#include "sensor_msgs/Temperature.h"
#include "sensor_msgs/RelativeHumidity.h"
#include "sensor_msgs/FluidPressure.h"

int main(int argc, char **argv)
{
    const std::string node_name = "rt_usb_thp_driver";
    ros::init(argc, argv, node_name);
    ros::NodeHandle n;

    std::string port, frame_id;

    //Publisher
    ros::Publisher temp_pub = n.advertise<sensor_msgs::Temperature>("thp/temperature", 10);
    ros::Publisher rh_pub = n.advertise<sensor_msgs::RelativeHumidity>("thp/relative_humidity", 10);
    ros::Publisher press_pub = n.advertise<sensor_msgs::FluidPressure>("thp/pressure", 10);

    //Meseage
    sensor_msgs::Temperature temp_msg;
    sensor_msgs::RelativeHumidity rh_msg;
    sensor_msgs::FluidPressure press_msg;

    ros::Rate loop_rate(10);

    n.param("port", port, std::string("/dev/ttyACM0"));
    n.getParam(node_name + "/port", port);

    n.param("frame_id", frame_id, std::string("thp_link"));
    
    while(ros::ok()){
        ros::Time ros_time = ros::Time::now();

        temp_msg.header.frame_id = frame_id;
        temp_msg.header.stamp = ros_time;
        temp_msg.temperature = 0;
        temp_msg.variance = 0;

        rh_msg.header.frame_id = frame_id;
        rh_msg.header.stamp = ros_time;
        rh_msg.relative_humidity = 0; // 1.0 == humidity100%
        rh_msg.variance = 0;

        press_msg.header.frame_id = frame_id;
        press_msg.header.stamp = ros_time;
        press_msg.fluid_pressure = 0;
        press_msg.variance = 0;

        temp_pub.publish(temp_msg);
        rh_pub.publish(rh_msg);
        press_pub.publish(press_msg);
    }

    return 0;
}
