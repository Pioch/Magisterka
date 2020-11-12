#include <ros/ros.h> 
#include <sensor_msgs/PointCloud.h>
#include <gazebo_msgs/ModelStates.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include "std_msgs/String.h"

using namespace std;

float poz_x, poz_y, poz_th, q0, q1, q2, q3;
float odleglosc, przeszkoda_x, przeszkoda_y;
float x, y;
const char *path="/home/piotr/Magisterka/position_plugin/przeszkody.txt";

void robot_position_read(const gazebo_msgs::ModelStates::ConstPtr& msg)
{
	
	poz_x = msg->pose[1].position.x;
	poz_y = msg->pose[1].position.y;
	q0 = msg->pose[1].orientation.w;
	q1 = msg->pose[1].orientation.x;
	q2 = msg->pose[1].orientation.y;
	q3 = msg->pose[1].orientation.z;
	
	poz_th = atan2(2*(q0*q3 + q1*q2), 1 - 2*(pow(q2,2) + pow(q3,2)));
}

void chatterCallback(const sensor_msgs::PointCloud::ConstPtr& msg)
{
	ofstream myfile(path);
	
if(msg->points.size() != 0)
	{
		//ROS_INFO("size: %d", msg->points.size());
		for(int i = 0; i<= msg->points.size()-1; i++)
		{			
			if (((msg->points[i].x >= -10 && msg->points[i].x <= -0.01) || (msg->points[i].x >= 0.01 && msg->points[i].x <= 10)) && ((msg->points[i].y >= -10 && msg->points[i].y <= -0.01) || (msg->points[i].y >= 0.01 && msg->points[i].y <= 10)))
			{
				x = msg->points[i].x;
				y = msg->points[i].y;
				
				przeszkoda_x = x*sin(poz_th) + y*cos(poz_th) + poz_x;
				przeszkoda_y = -(x*cos(poz_th) - y*sin(poz_th)) + poz_y;
				
				ROS_INFO("x: %f, y: %f", przeszkoda_x, przeszkoda_y);
				
				
				odleglosc = sqrt(pow(poz_x - przeszkoda_x, 2) + pow(poz_y - przeszkoda_y, 2));
				ROS_INFO("Odleglosc: %f", odleglosc); //odleglosc od srodka robota
				
				if(odleglosc > 0.11)
				{
					myfile<<przeszkoda_x;
					myfile<<"	";
					myfile<<przeszkoda_y;
					myfile<<"	";				
					myfile<<odleglosc<<endl;
				}
					
			}
		}	
		
	}
		myfile.close();
  }
  


int main(int argc, char** argv) {
    ros::init(argc, argv, "topic_subscriber");
    ros::NodeHandle nh;
    ros::Subscriber sub = nh.subscribe("gazebo/model_states", 1000, robot_position_read);
    ros::Subscriber sub2 = nh.subscribe("/my_cloud", 1000, chatterCallback);
    ros::spin();
    return 0;
}
