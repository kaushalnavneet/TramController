/*
 * wheels_driver.hpp
 *
 *  Dated: Dec, 2018
 *  Authors: Navneet Kaushal, Vithika Joshi
 */

#ifndef wheels_driver_HPP_
#define wheels_driver_HPP_

#include "mbed.h"

#include <iostream>
#include <fstream>
#include <string>
#include "wheels_port.hpp"

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

bool startWheel1 = true;
bool startWheel2 = true;

/* OUTPUT PORTS DRIVERS */
template<class TIME, class MSG>
bool WHEEL1_OUT<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept{
	if(startWheel1){
		bot.enable_left_motor();
		startWheel1 = false;
	}
	if(cmd==TOKEN){
		switch(v){
		case 12:
			bot.left_motor(0.2);
			break;
		case 13:
			bot.left_motor(-0.2);
			break;
		case 14:
			bot.left_motor(0);
			break;
		}}
	return true;
}

template<class TIME, class MSG>
bool WHEEL2_OUT<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept{
	if(startWheel2){
		bot.enable_right_motor();
		startWheel2 = false;
	}
	if(cmd==TOKEN){
		switch(v){
		case 12:
			bot.right_motor(0.2);
			break;
		case 13:
			bot.right_motor(-0.2);
			break;
		case 14:
			bot.right_motor(0);
			break;
		}}
	return true;
}

template<class TIME, class MSG>
bool LAST_STOP<TIME, MSG>::pDriver(int &cmd, int &v) const noexcept{

return true;
}


#endif /* wheels_driver_HPP_ */
