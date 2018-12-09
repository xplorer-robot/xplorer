#include <ros/ros.h>
#include <ca_msgs/Bumper.h>
#include <nav_msgs/OccupancyGrid.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_core/grid_map_core.hpp>
#include <grid_map_msgs/GridMap.h>
#include <geometry_msgs/PoseStamped.h>
#include <grid_map_ros/GridMapRosConverter.hpp>
#include <stdlib.h> 
#include <tf/tf.h>
#include <tf/transform_listener.h>

using namespace grid_map;
ros::Publisher grid_map_pub;
ros::Publisher occu_grid_pub;
ros::Publisher orig_occu_grid_pub;
tf::TransformListener* ptrListener;

class Bumper 
{
  public:
    bool left_bumper,right_bumper;
    bool isInitialized;
    geometry_msgs::PoseStamped ps_in;
    geometry_msgs::PoseStamped ps_out;
    Index startlft;
    Index startrgt;
    Index endlft;
    Index endrgt;
   

     void bumperCallback(const ca_msgs::Bumper::ConstPtr& msg);
};

class Occupancy 
{
  public:
   double width, height,cell_size;
   bool isInit, convert;
   GridMap map;
   //make this a pointer if you run into problems

     void occupancyCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg);
};



Bumper  bumper;
Occupancy occupancy;

void Bumper::bumperCallback(const ca_msgs::Bumper::ConstPtr& msg) 
{
  ROS_WARN("bumper callback");
if(occupancy.isInit)
{
    left_bumper=msg->is_left_pressed;
    right_bumper=msg->is_right_pressed;

    if(!bumper.isInitialized)
       {
  	    occupancy.map.add("bumper");
  	    occupancy.map.add("combined");
        bumper.isInitialized=true;
        }
    
    ps_in.pose.orientation.w=1;
    ps_out.pose.orientation.w=1;
    ps_in.header.frame_id = "base_footprint";
    ps_in.header.stamp=ros::Time(0);

    //left bumper start_pos
    ps_in.pose.position.x = 0.0; 
    ps_in.pose.position.y = 0.174; 
    ps_in.pose.position.z = 0.0;   
  
    
    ptrListener->transformPose("map",ps_in,ps_out);
    startlft(ps_out.pose.position.x,ps_out.pose.position.y);

   //left bumper end_pos
    ps_in.pose.position.x = 0.174; 
    ps_in.pose.position.y = 0.0; 
    ps_in.pose.position.z = 0.0;   
  
    ptrListener->transformPose("map",ps_in,ps_out);
    endlft(ps_out.pose.position.x,ps_out.pose.position.y);
    //Right bumper start_pos
    ps_in.pose.position.x = 0.0; 
    ps_in.pose.position.y = -0.174; 
    ps_in.pose.position.z = 0.0;   
  
    ptrListener->transformPose("map",ps_in,ps_out);
    startrgt(ps_out.pose.position.x,ps_out.pose.position.y);

   
    //Right bumper end_pos
    ps_in.pose.position.x = 0.174; 
    ps_in.pose.position.y = 0.0; 
    ps_in.pose.position.z = 0.0;   
  
    ptrListener->transformPose("map",ps_in,ps_out);
    endrgt(ps_out.pose.position.x,ps_out.pose.position.y);

    //This improves efficiiency in traversing grid_map 
    grid_map::Matrix& data = occupancy.map["bumper"];

        //left bumper
        if(bumper.left_bumper)
           {
           ROS_WARN("left");
            for(grid_map::LineIterator iterator(occupancy.map,startlft,endlft); !iterator.isPastEnd();++iterator)
             {
               occupancy.map.at("bumper",*iterator)=100;
	      }
          }
        //Right bumper    
        if(bumper.right_bumper)
            {
            ROS_WARN("right");
             for(grid_map::LineIterator iterator(occupancy.map,startrgt,endrgt); !iterator.isPastEnd(); ++iterator){
                        occupancy.map.at("bumper",*iterator)=100; 
                      }
             }

        //if(grid_map_pub)
         //{
          grid_map_msgs::GridMap message;
          GridMapRosConverter::toMessage(occupancy.map,message);
          grid_map_pub.publish(message);
         //}
         
    }
    left_bumper=false;
    right_bumper=false; 
}

void Occupancy::occupancyCallback(const nav_msgs::OccupancyGrid::ConstPtr& msg) 
{
       ROS_WARN("occupancy callback");
	if(!isInit)
         {
  	  map.add("occupancy",-1.0);
  	  Position origin=Position(msg->info.origin.position.x, msg->info.origin.position.y);
  	  map.setPosition(origin);
  	  isInit=true;
	 }
    
    grid_map::Matrix& data = occupancy.map["occupancy"];
  	GridMapRosConverter::fromOccupancyGrid(*msg,"occupancy", map);
            ROS_WARN("map_convert");
        //combined occupancy grid
        if(bumper.isInitialized)
          {
              map["combined"]=map["occupancy"]+map["bumper"]; 
              nav_msgs::OccupancyGrid comb_grid;
             
         // if(occu_grid_pub)
         //    {
              comb_grid.header=msg->header;
              comb_grid.info=msg->info;
              GridMapRosConverter::toOccupancyGrid(map,"combined",0,100,comb_grid);
              occu_grid_pub.publish(comb_grid);
          //  }
          }
         
         //original occupancy grid
         //orig_occu_grid_pub.publish(msg);
           
}  

int main(int argc,char** argv)
{
    ros::init(argc,argv,"new_map_node");
    ros::NodeHandle nh;
    //Setup publishers
    grid_map_pub=nh.advertise<grid_map_msgs::GridMap>("/mike_grid_map",10,true);
    
    occu_grid_pub=nh.advertise<nav_msgs::OccupancyGrid>("/mike_occu_grid",10,true);
    
    //orig_occu_grid_pub=nh.advertise<nav_msgs::OccupancyGrid>("/mike_orig_grid",10,true);
    
    ptrListener=new tf::TransformListener;
    
    while(!ptrListener->waitForTransform("map","base_footprint",ros::Time(0),ros::Duration(5.0)))
    {
    ROS_WARN("Transform not available'waiting for transform");
    }
      
    ros::Subscriber bmpr_sub = nh.subscribe("/bumper",10,&Bumper::bumperCallback,&bumper);
    ros::Subscriber occu_sub = nh.subscribe("/map",10,&Occupancy::occupancyCallback,&occupancy);
    
    ros::spin();
    delete ptrListener;
    return 0;
}
 
