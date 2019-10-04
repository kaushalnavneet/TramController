/*
 * stop_driver.hpp
 *
 *  Dated: Dec, 2018
 *  Authors: Navneet Kaushal, Vithika Joshi
 */

#ifndef stop_driver_HPP_
#define stop_driver_HPP_

#include "mbed.h"
#include <iostream>
#include <fstream>
#include <string>
#include "SeeedStudioShieldBot.h"
#include "stop_port.hpp"

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

DigitalIn start_btn(PC_13);
DigitalIn push1(D3);
DigitalIn push2(D2);
DigitalIn push3(D6);
DigitalIn push4(SERIAL_TX);
DigitalIn push5(D7);

SeeedStudioShieldBot bot(
    D8, D9, D11,              // Wheel 1 pins
    D12, D10, D13,            // Wheel 2 pins
    A0, A1, A2, A3, D4        // Stop Sensors' pins
);

bool isStarted = false;

/* INPUT PORTS DRIVERS */
template<class TIME, class MSG>
bool START_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	  if(!start_btn){
		if(!isStarted){
			isStarted = true;
			v = 200;
		}
		else{
			isStarted = false;
			v = 201;
		}
		return true;
	  }
	  else{
		return false;
	  }
}

template<class TIME, class MSG>
bool STOP1_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	if(bot.leftSensor == 0){
		v=1;
	}
	else v=0;
	return true;
}

template<class TIME, class MSG>
bool STOP2_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	if(bot.inLeftSensor == 0){
		v=1;
	}
	else v=0;
	return true;
}

template<class TIME, class MSG>
bool STOP3_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	if(bot.getCentreSensor() == 0){
		v=1;
	}
	else v=0;
	return true;
}

template<class TIME, class MSG>
bool STOP4_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	if(bot.inRightSensor == 0){
		v=1;
	}
	else v=0;
	return true;
}


template<class TIME, class MSG>
bool STOP5_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	if(bot.rightSensor == 0){
		v=1;
	}
	else v=0;
	return true;
}

template<class TIME, class MSG>
bool OSTOP1_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	v=push1;
	return true;
}
template<class TIME, class MSG>
bool OSTOP2_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	v=push2;
	return true;
}
template<class TIME, class MSG>
bool OSTOP3_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	v=push3;
	return true;
}
template<class TIME, class MSG>
bool OSTOP4_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	v=push4;
	return true;
}
template<class TIME, class MSG>
bool OSTOP5_IN<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept {
	v=push5;
	return true;
}


#endif /* stop_driver_HPP_ */
