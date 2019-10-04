#include <stdio.h>

#include <chrono>
#include <algorithm>
#include <boost/simulation.hpp>
#include <boost/rational.hpp>
#include <boost/lexical_cast.hpp>

// Atomic models
#include "StopController.hpp"
#include "WheelController.hpp"
//Port models
#include "eTime.h"
#include "eMessage.hpp"
#include "user_drivers/stop_driver.hpp"
#include "user_drivers/stop_port.hpp"
#include "user_drivers/wheels_driver.hpp"
#include "user_drivers/wheels_port.hpp"

using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;
using namespace std;

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"


int main(int argc, char* argv[])
{
	printf("Nucleo Board - Embedded CD-Boost \n\n");

	// Atomic models definition
	printf("Creating atomic models ... \n");
	auto scontrol = make_atomic_ptr<StopController<Time, Message>>();
	auto wcontrol = make_atomic_ptr<WheelController<Time, Message>>();

	//Coupled model definition
	printf("Creating Coupled models ... \n");
	shared_ptr<flattened_coupled<Time, Message>> ControlUnit( new flattened_coupled<Time, Message>{{scontrol,wcontrol}, {scontrol}, {{scontrol,wcontrol}}, {wcontrol}});

	//Top I/O port definition
	printf("Defining top I/O ports ... \n");

	// Input ports
	auto start = make_port_ptr<START_IN<Time, Message>>();
	auto stop1 = make_port_ptr<STOP1_IN<Time, Message>>();
	auto stop2 = make_port_ptr<STOP2_IN<Time, Message>>();
	auto stop3 = make_port_ptr<STOP3_IN<Time, Message>>();
	auto stop4 = make_port_ptr<STOP4_IN<Time, Message>>();
	auto stop5 = make_port_ptr<STOP5_IN<Time, Message>>();
	auto ostop1 = make_port_ptr<OSTOP1_IN<Time, Message>>();
	auto ostop2 = make_port_ptr<OSTOP2_IN<Time, Message>>();
	auto ostop3 = make_port_ptr<OSTOP3_IN<Time, Message>>();
	auto ostop4 = make_port_ptr<OSTOP4_IN<Time, Message>>();
	auto ostop5 = make_port_ptr<OSTOP5_IN<Time, Message>>();

    // Output ports
	auto wheel1 = make_port_ptr<WHEEL1_OUT<Time, Message>>();
	auto wheel2 = make_port_ptr<WHEEL2_OUT<Time, Message>>();

    // Execution parameter definition
	printf("Preparing runner \n");
	Time initial_time{Time::currentTime()};
	erunner<Time, Message> root{ControlUnit, {{start,scontrol},{stop1,scontrol},{stop2,scontrol},{stop3,scontrol},{stop4,scontrol},{stop5,scontrol},{ostop1,scontrol},{ostop2,scontrol},{ostop3,scontrol},{ostop4,scontrol},{ostop5,scontrol}} , {{wheel1,wcontrol},{wheel2,wcontrol}}};
	Time end_time{Time(0,30,0,0)};

	printf(("Starting simulation until time: seconds " + end_time.asString() + "\n").c_str());
	end_time = root.runUntil(end_time);


}

#pragma GCC diagnostic pop

// ----------------------------------------------------------------------------
