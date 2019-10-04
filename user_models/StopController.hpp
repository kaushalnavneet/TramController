/*
 * StopController.hpp
 *
 *  Dated: Dec 2018
 *  Authors: Navneet Kaushal, Vithika Joshi
 */

#ifndef StopController_HPP_
#define StopController_HPP_

#include <boost/any.hpp>
#include <boost/simulation/pdevs/atomic.hpp>
#include "commonH.h"
#include "SWO.h"
#include "mbed.h"

namespace boost {
namespace simulation {
namespace pdevs {
namespace basic_models {
/**
 * @brief StopController PDEVS Model
 *
 * SensorController PDEVS Model():
 * - X = {(scontrol_start_in, {START, STOP}); (scontrol_stop1_in, {TOKEN,VALUE}); (scontrol_stop2_in, {TOKEN,VALUE}); (scontrol_stop3_in, {TOKEN,VALUE}); (scontrol_stop4_in, {TOKEN,VALUE}); (scontrol_stop5_in, {TOKEN,VALUE});
 *        (scontrol_ostop1_in, {TOKEN,VALUE}); (scontrol_ostop2_in, {TOKEN,VALUE}); (scontrol_ostop3_in, {TOKEN,VALUE}); (scontrol_ostop4_in, {TOKEN,VALUE}); (scontrol_ostop5_in, {TOKEN,VALUE});}
 * - Y = {(start_out, {START, STOP}); (scontrol_wcontrol_out, {TOKEN,VALUE}); }
 *
 * - S = { “WAIT_DATA”, “IDLE”,“PREP_RX”,“TX_DATA”,“PREP_STOP” }
 *

 */
template<class TIME, class MSG>
class StopController : public atomic<TIME, MSG>
{
	TIME _next;
	std::vector<MSG> _outvalue;
private:
	enum State {IDLE, PREP_RX, WAIT_DATA, TX_DATA, PREP_STOP};
	enum Port {scontrol_start_in, scontrol_stop1_in, scontrol_stop2_in, scontrol_stop3_in, scontrol_stop4_in, scontrol_stop5_in, scontrol_ostop1_in, scontrol_ostop2_in, scontrol_ostop3_in, scontrol_ostop4_in, scontrol_ostop5_in, scontrol_wcontrol_in, scontrol_wcontrol_out, scontrol_start_out};
	std::string portName[14];
	State _state;
	MSG _outputMessageM1,_outputMessageM2;
	//Variables:
	int stop1 = 0, stop2 = 0, stop3 = 0, stop4 = 0, stop5 = 0, ostop1 = 0, ostop2 = 0, ostop3 = 0, ostop4 = 0, ostop5 = 0;
    int stopNum = 0;
	TIME scTxTime = TIME(00,00,00,050);
	TIME scRxPrepTime = TIME(00,00,00,050);
	const TIME infinity=boost::simulation::model<TIME>::infinity;

public:
    /**
     * @brief StopController constructor.
     */
    explicit StopController(const std::string &n = "scontrol") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::IDLE), _outputMessageM1(), _outputMessageM2() {
    	portName[0] = "start_in";
    	portName[1] = "stop1_in";
    	portName[2] = "stop2_in";
    	portName[3] = "stop3_in";
    	portName[4] = "stop4_in";
    	portName[5] = "stop5_in";
    	portName[6] = "ostop1_in";
    	portName[7] = "ostop2_in";
    	portName[8] = "ostop3_in";
    	portName[9] = "ostop4_in";
    	portName[10] = "ostop5_in";
    	portName[11] = "WCONTROL_IN";
    	portName[12] = "SCONTROL_OUT";
    	portName[13] = "START_OUT";
    	/*portName[7] = "WCONTROL_IN";
    	portName[8] = "SCONTROL_OUT";
    	portName[9] = "START_OUT";*/

    }

	/**
	 * @brief internal function.
	 */
	void internal() noexcept {
		switch (_state){
		case PREP_STOP:
			_state = IDLE;
			_next = infinity;
			break;
		case PREP_RX:
		case TX_DATA:
			_state = WAIT_DATA;
			_next = infinity;
			break;
		}
	}

	/**
	 * @brief advance function.
	 * @return Time until next internal event.
	 */
	TIME advance() const noexcept {
		return _next;
	}

	/**
	 * @brief out function.
	 * @return MSG defined in construction.
	 */
	std::vector<MSG> out() const noexcept {
		switch (_state){

		case PREP_STOP:
			_outputMessageM2 = MSG(portName[scontrol_wcontrol_out],TOKEN, STOP_PROC); //Stop Wheel Control
			return std::vector<MSG>{_outputMessageM2};

		case PREP_RX:
			_outputMessageM1 = MSG(portName[scontrol_start_out],TOKEN, START_PROC); //Start All Sensors
			return std::vector<MSG>{_outputMessageM1};

		case TX_DATA: {
			switch(stopNum){
				case 1:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 0); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				case 2:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 1); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				case 3:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 2); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				case 4:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 3); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				case 5:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 4); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				case 6:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 0); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				/*case 7:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 1); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				case 8:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 2); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				case 9:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 3); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;
				case 10:_outputMessageM1 = MSG(portName[scontrol_wcontrol_out],STATION, 4); //Send feedback to Wheel Control
				return std::vector<MSG>{_outputMessageM1};
				break;*/
			}

		}
		};
		return std::vector<MSG>{};
	}

	/**
	 * @brief external function
	 * @param msg external input message.
	 * @param t time the external input is received.
	 */
	void external(const std::vector<MSG>& mb, const TIME& t) noexcept {

		MSG msg = mb.back();

		if (msg.port == portName[scontrol_start_in]){
			if(_state == IDLE && msg.val == START_PROC){
				_state = PREP_RX;
				_next = scRxPrepTime;
			}
			else if (msg.val == STOP_PROC) {
				_state = PREP_STOP;
				_next = Time::Zero;
			}
		}

		else if (msg.port == portName[scontrol_stop1_in]){
			if(_state == WAIT_DATA) {
				stop1 = static_cast<int>(msg.val);
				if(stop1 == 1){
				stopNum = 1;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[scontrol_stop2_in]){
			if(_state == WAIT_DATA) {
				stop2 = static_cast<int>(msg.val);
				if(stop2 == 1){
				stopNum = 2;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[scontrol_stop3_in]){
			if(_state == WAIT_DATA) {
				stop3 = static_cast<int>(msg.val);
				if(stop3 == 1){
				stopNum = 3;
				_state = TX_DATA;
				_next = scTxTime;
				}

			}
		}
		else if (msg.port == portName[scontrol_stop4_in]){
			if(_state == WAIT_DATA) {
				stop4 = static_cast<int>(msg.val);
				if(stop4 == 1){
				stopNum = 4;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[scontrol_stop5_in]){
			if(_state == WAIT_DATA) {
				stop5 = static_cast<int>(msg.val);
				if(stop5 == 1){
				stopNum = 5;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[scontrol_ostop1_in]){
			if(_state == WAIT_DATA) {
				ostop1 = static_cast<int>(msg.val);
				if(ostop1 == 1){
				stopNum = 6;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[scontrol_ostop2_in]){
			if(_state == WAIT_DATA) {
				ostop2 = static_cast<int>(msg.val);
				if(ostop2 == 1){
				stopNum = 7;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[scontrol_ostop3_in]){
			if(_state == WAIT_DATA) {
				ostop3 = static_cast<int>(msg.val);
				if(ostop3 == 1){
				stopNum = 8;
				_state = TX_DATA;
				_next = scTxTime;
				}

			}
		}
		else if (msg.port == portName[scontrol_ostop4_in]){
			if(_state == WAIT_DATA) {
				ostop4 = static_cast<int>(msg.val);
				if(ostop4 == 1){
				stopNum = 9;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
		else if (msg.port == portName[scontrol_ostop5_in]){
			if(_state == WAIT_DATA) {
				ostop5 = static_cast<int>(msg.val);
				if(ostop5 == 1){
				stopNum = 10;
				_state = TX_DATA;
				_next = scTxTime;
				}
			}
		}
	}

	/**
	 * @brief confluence function.
	 * Execute the internal.
	 *
	 * @param msg
	 * @param t time the external input is confluent with an internal transition.
	 */
	void confluence(const std::vector<MSG>& mb, const TIME& t)  noexcept  {
		internal();
		//external(mb,t);
	}

	  void print()  noexcept {SWO_PrintString("scontrol");}

};

}
}
}
}


#endif /* StopController_HPP_ */
