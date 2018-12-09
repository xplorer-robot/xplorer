

#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>

#include <tf/tf.h>
#include <tf/transform_listener.h>

ros::Publisher fixed_odom_pub;
ros::Publisher cmd_vel_pub;
tf::TransformListener* ptrListener;


double z_avg = 0.0;
double x_avg = 0.0;

double faked_z = 0.0;
double faked_x = 0.0;

void odom_callback(const nav_msgs::Odometry::ConstPtr & msg)
{
    nav_msgs::Odometry mod_data = *msg;
    /*
    mod_data.pose.pose.orientation.w=1;
    mod_data.pose.pose.orientation.x=0;
    mod_data.pose.pose.orientation.y=0;
    mod_data.pose.pose.orientation.z=0;

    mod_data.pose.pose.position.x=0;
    mod_data.pose.pose.position.y=0;
    mod_data.pose.pose.position.z=0;
    
    mod_data.twist.twist.linear.x=0;
    mod_data.twist.twist.linear.y/=100;
    mod_data.twist.twist.linear.z/=100;
    mod_data.twist.twist.angular.x/=100;
    mod_data.twist.twist.angular.y/=100;
    mod_data.twist.twist.angular.z=0;
    */
    
    
    mod_data.twist.twist.linear.x=faked_x;
    mod_data.twist.twist.linear.y/=100;
    mod_data.twist.twist.linear.z/=100;
    mod_data.twist.twist.angular.x/=100;
    mod_data.twist.twist.angular.y/=100;
    mod_data.twist.twist.angular.z=faked_z;
    
    fixed_odom_pub.publish(mod_data);
    
    /*if(mod_data.twist.twist.angular.z
    {*/

}

template <typename T> int sgn(T val)
{
return (T(0)<val)-(val<T(0));
}
 
void vel_callback(const geometry_msgs::Twist::ConstPtr & msg)
{

    geometry_msgs::Twist out = *msg;
    faked_z=out.angular.z;
    faked_x=out.linear.x;
//    out.angular.z=(out.angular.z!=0)?sgn(out.angular.z)*.2:0;
//    out.linear.x=(out.linear.x!=0)?sgn(out.linear.x)*.1:0;
    cmd_vel_pub.publish(out);
}

int main(int argc, char ** argv)
{

    ros::init(argc, argv, "odom_fixer");
    ros::NodeHandle nh;
    
    ROS_INFO("started fixer");
    
  
    ros::Subscriber sub = nh.subscribe("/odom", 10, odom_callback);
    ros::Subscriber vel_sub = nh.subscribe("/cmd_vel_w",10,vel_callback);
    cmd_vel_pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel",10);
    fixed_odom_pub = nh.advertise<nav_msgs::Odometry>("/odom_fixed", 1000);
    
    ros::spin();

}
