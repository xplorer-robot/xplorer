# Xplorer Autonomous Robot

This project is the first tier to developing a personal care robot that would cater to the needs of elderly people. As the first tier of a long-term goal, this pioneer project sought to tackle only the autonomous exploration aspect of the ultimate goal, a personal care robot.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

## Prerequisites

This project is intended to function on the Robot Operating System(ROS) kinetic  working within Ubuntu environment. These must be installed prior to installing other packages listed in the Installing section below. This project was specified using the following components: iRobot Create 2 platform, RPLiDAR A2, LattePanda processor, and PhidgetSpatial Precision 3/3/3 High Resolution IMU.

## Installing

     To install ros kinetic:  http://wiki.ros.org/kinetic/Installation

### Environment setup:

1. Build a workspace via terminal

       $ mkdir -p ~/workspace_name/src

       $ cd ~/workspace_name/

       $ catkin_make

       $ cd src
       
       
2. To properly source workspace for the first time

       $ cd 
       
       $ echo "source /opt/ros/kinetic/setup.bash
             source ~/xplorer_ws/devel/setup.bash" >> .bashrc
       
       $ source ~/.bashrc
       
       From now on, sourcing the workspace is simply just the command below
       
       $ source ~/.bashrc
       
       

3. The packages below are required. In the src folder in your workspace, clone the packages below from the provided github repos.

           ROS grid_map packages : https://github.com/anybotics/grid_map

           ROS transforms (tf), though tf2_ros is recommended : https://github.com/ros/geometry

           ROS robot_pose_ekf : https://github.com/ros-planning/navigation

           ROS gmapping package: https://github.com/ros-perception/slam_gmapping

           ROS move_base package: included in robot_pose_ekf (c)

           ROS imu_filter_madgwick package: https://github.com/ccny-ros-pkg/imu_tools

           ROS phidget_imu package:https://github.com/ros-drivers/phidgets_drivers

           ROS create_autonomy package: https://github.com/AutonomyLab/create_autonomy

           ROS rplidar_ros package: https://github.com/Slamtec/rplidar_ros 
     
 
     Example 1, adding gmapping package to your workspace
     
       $ cd ~/workspace_name/src
     
       $ git clone https://github.com/ros-perception/slam_gmapping
     
       $ cd ..
     
       $ catkin_make
     
     
4.  Create a package:
   
        http://wiki.ros.org/ROS/Tutorials/CreatingPackage
       
       
5.   Launch files:
   
        
 
 
## Documentation

 Access to team drive provided by maintainer, see maintainer section.

      Xplorer Team Drive: https://drive.google.com/drive/u/0/folders/0AHRYQvPb7AVcUk9PVA
 
      Xplorer System Manual: https://docs.google.com/document/d/15QjLc6g1BTSyCGFoR9ucj6v30LYu_Sau0RSgYr9VZXw/edit#
 

## General Debugging

The data published by the RPLiDAR sensor, IMU and the ICreate 2 wheel odometry can be viewed and verified on RViz (ROS            Visualization) and rqt. Transform trees are easily viewed via rqt as well as verified for correctness in spatial relationships. The results of the package built must be launched from the workspace first (roslaunch package_name) before the result of corresponding package can be displayed on a new tab in the terminal. The software developed for robots mapping and navigation, once launched, can be displayed on RViz. The environment must be sourced especially after making changes to files in the workspace as well as running catkin_make after adding, building or modifying packages. 

     Ros Wiki:   http://wiki.ros.org

     Ros Support: http://www.ros.org/support/

     RPlidar A2 Support: https://www.slamtec.com/en/Support#rplidar-a2

     icreate2 Support: https://homesupport.irobot.com/?_ga=2.150987254.1346950700.1544131673-1962793892.1543973985

     Phidget IMU Support: https://www.phidgets.com/docs/General_Troubleshooting#Device_Troubleshooting


## Built With

     ROS (Robot Operating System) - The open source framework used

     Rosdep - Dependency Management


## Maintainer

     Mentor: Dr Powsiri Klinkhachorn
     Email: xplorer.wvu@gmail.com

 
## Authors

     Lucas Eans - West Virginia University

     Kingsley Enoka - West Virginia University

     Matthew Gramlich - West Virginia University

     Faythe Maston - West Virginia University

     Mike Muponda - West Virginia University



## Acknowledgments

We would like to acknowledge West Virginia University’s Lane Department of Computer Science and Electrical Engineering as our sponsor and Dr. Powsiri Klinkhachorn as our mentor professor. We also acknowledge the Robotic Operating System’s open source libraries.
