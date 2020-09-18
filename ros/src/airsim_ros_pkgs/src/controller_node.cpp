#include <ros/ros.h>
#include <signal.h>
#include <airsim_ros_pkgs/VelCmd.h>

class controllerNode{
  ros::NodeHandle nh;
  ros::Publisher vehcle_cmd_pub1;
  ros::Publisher vehcle_cmd_pub2;
  ros::Timer heartbeat;
public:
  controllerNode(){
    vehcle_cmd_pub1 = nh.advertise<airsim_ros_pkgs::VelCmd>("/airsim_node/car_1/vel_cmd_body_frame",10);
    vehcle_cmd_pub2 = nh.advertise<airsim_ros_pkgs::VelCmd>("/airsim_node/car_2/vel_cmd_body_frame",10);

    heartbeat = nh.createTimer(ros::Duration(1.0/100), &controllerNode::controlLoop, this);
    heartbeat.start();
  }

  void controlLoop(const ros::TimerEvent& t){
    airsim_ros_pkgs::VelCmd car1_cmd;
    airsim_ros_pkgs::VelCmd car2_cmd;
    if (ros::isShuttingDown()){
      car1_cmd.throttle = 0.0;
      car1_cmd.steering = 0.0;
      car2_cmd.throttle = 0.0;
      car2_cmd.steering = 0.0;      
    }
    else{
      car1_cmd.throttle = 1.0;
      car1_cmd.steering = 1.0;
      car1_cmd.brake = 0.0;
      car2_cmd.throttle = 1.0;
      car2_cmd.steering = 1.0;      
      car2_cmd.brake = 0.0;
    }
    vehcle_cmd_pub1.publish(car1_cmd);
    vehcle_cmd_pub2.publish(car2_cmd);
  }
};

int main(int argc, char** argv){
  ros::init(argc, argv, "controller_node");
  controllerNode n;
  ros::spin();
  return 0;
}
