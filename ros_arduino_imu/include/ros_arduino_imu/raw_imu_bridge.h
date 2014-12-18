/*
Copyright (c) 2013, Tony Baltovski
All rights reserved.
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
 * Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
 * Redistributions in binary form must reproduce the above copyright
   notice, this list of conditions and the following disclaimer in the
   documentation and/or other materials provided with the distribution.
 * Neither the name of  nor the names of its contributors may be used to
   endorse or promote products derived from this software without specific
   prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _RAW_IMU_BRIDGE_H_
#define _RAW_IMU_BRIDGE_H_

#include <ros/ros.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/MagneticField.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <ros_arduino_msgs/RawImu.h>

class RawImuBridge
{
  private:
    ros::NodeHandle nh_, pnh_;
    bool use_accelerometer_, use_gyroscope_, use_magnetometer_;
    bool use_mag_msg_;
    std::string frame_id_;
    double linear_acc_stdev_, angular_vel_stdev_, magnetic_field_stdev_;
    boost::array<double, 9> linear_acc_covar_;
    boost::array<double, 9> angular_vel_covar_;
    boost::array<double, 9> magnetic_field_covar_;
    // Used for mag scaling
    double mag_x_min_, mag_x_max_;
    double mag_y_min_, mag_y_max_;
    double mag_z_min_, mag_z_max_;
    // ROS pub/sub
    ros::Publisher imu_pub_;
    ros::Publisher mag_pub_;
    ros::Subscriber raw_sub_;
    // ROS Member functions
    void rawCallback(const ros_arduino_msgs::RawImuConstPtr& raw_msg);
    void fillRowMajor(boost::array<double, 9> & covaw, double stdev);
  public:
    RawImuBridge(ros::NodeHandle nh, ros::NodeHandle pnh);
    virtual ~RawImuBridge();
};

#endif  // _RAW_IMU_BRIDGE_H_

