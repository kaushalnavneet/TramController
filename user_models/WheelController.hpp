/*
 * WheelController.hpp
 *
 *  Dated: Dec 2018
 *  Authors: Navneet Kaushal, Vithika Joshi
 */

#ifndef WheelController_HPP_
#define WheelController_HPP_

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
 * @brief WheelController PDEVS Model
 *
 * WheelController PDEVS Model():
 * - X = {(wcontrol_scontrol_in, {1,2,3,4,5}); {(Tram_StopNum, {1,2,3,4,5})}
 * - Y = {(wcontrol_wheel1_out, {NEXT, PREVIOUS, STOP}); (wcontrol_wheel2_out, {NEXT, PREVIOUS, STOP}); }
 * - S = {"PREP_START," "WAIT_DATA," “PREP_MOVE_FWD,” “MOVE_FWD,”  “PREP_MOVE_BWD,” “MOVE_BWD,” “PREP_STOP,” "IDLE"}
 * - internal -> See DEVS Spec Doc
 * - external -> See DEVS Spec Doc
 * - out      -> See DEVS Spec Doc
 * - advance  -> See DEVS Spec Doc
*/

template<class TIME, class MSG>
class WheelController : public atomic<TIME, MSG>
{
    //initialize time for next state and message that will be outputted
    TIME _next;
    std::vector<MSG> _outvalue;
private:
    //initialize states, ports,
    enum State {PREP_START, WAIT_DATA, PREP_MOVE_FWD, PREP_MOVE_BWD, MOVE_FWD, MOVE_BWD, PREP_STOP, IDLE};
    enum Port {wcontrol_scontrol_in, wcontrol_scontrol_out, wcontrol_wheel1_out, wcontrol_wheel2_out, Tram_StopNum, Tram_LastStop};
    std::string portName[6];
    const TIME infinity = boost::simulation::model<TIME>::infinity;

    State _state;
    MSG _outputMessage1,_outputMessage2;// Variables
    int scontrol_input = 0;
    int stn = 0;
	// Prep time
    TIME startPrepTime = TIME(00,00,00,50);
    TIME startTime = TIME(00,00,01,0);


public:
    /**
     * @brief WheelController constructor.
     *
     */
    explicit WheelController(const std::string &n = "wcontrol") noexcept : _next(infinity), _outvalue(std::vector<MSG>{}),_state(State::WAIT_DATA), _outputMessage1(), _outputMessage2() {
    	portName[0] = "SCONTROL_OUT";
    	portName[1] = "WCONTROL_OUT";
    	portName[2] = "wheel1";
    	portName[3] = "wheel2";
    	portName[4] = "StopNumber";
    	portName[5] = "LastStop";
    	printf("WCONTROL CREATED \n");
    }

    /**
     * @brief internal function.
     */
    void internal() noexcept {
    	switch (_state){
			case IDLE:
				_state = WAIT_DATA;
				_next = infinity;
				break;

			case MOVE_FWD:
				stn=stn+1;
				if(stn< scontrol_input){
					_state = PREP_MOVE_FWD;
					_next = startPrepTime;
				}
				else{
					_state = WAIT_DATA;
					_next = infinity;
				}
				break;

			case PREP_MOVE_FWD:
				_state = MOVE_FWD;
				_next = startTime;
				break;

			case MOVE_BWD:
				stn=stn-1;
				if(stn > scontrol_input){
					_state = PREP_MOVE_BWD;
					_next = startPrepTime;
				}
				else{
				_state = WAIT_DATA;
				_next = infinity;
				}
				break;

			case PREP_MOVE_BWD:
				_state = MOVE_BWD;
				_next = startTime;
				break;

			case PREP_STOP:
				_state = WAIT_DATA;
				_next = infinity;
				break;

			default:
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
     * @return MSG defined below.
     */
    std::vector<MSG> out() const noexcept {
    	if (_state==PREP_MOVE_FWD)
    	{
			_outputMessage1 = MSG(portName[wcontrol_wheel2_out],TOKEN,NEXT);
			_outputMessage2 = MSG(portName[wcontrol_wheel1_out],TOKEN,NEXT);
			return std::vector<MSG>{_outputMessage1, _outputMessage2};
    	}
    	else if (_state== PREP_MOVE_BWD)
    	{
			_outputMessage1 = MSG(portName[wcontrol_wheel2_out],TOKEN,PREVIOUS);
			_outputMessage2 = MSG(portName[wcontrol_wheel1_out],TOKEN,PREVIOUS);
			return std::vector<MSG>{_outputMessage1, _outputMessage2};
    	}
    	else if(_state== PREP_STOP || _state== MOVE_FWD || _state== MOVE_BWD )
    	{
			_outputMessage1 = MSG(portName[wcontrol_wheel2_out],TOKEN,STOP);
			_outputMessage2 = MSG(portName[wcontrol_wheel1_out],TOKEN,STOP);
			return std::vector<MSG>{_outputMessage1,_outputMessage2};
    	}

    	return std::vector<MSG>{};
    }

    /**
     * @brief external function will set the new state depending on the value of the input.
     * @param msg external input message.
     * @param t time the external input is received.
     */
    void external(const std::vector<MSG>& mb, const TIME& t) noexcept {

    	MSG msg = mb.back();
    	if (msg.port == portName[wcontrol_scontrol_in]) {
			if(_state == WAIT_DATA ) {
				scontrol_input = static_cast<int>(msg.val);
				if (scontrol_input - stn > 0) {
					_state = PREP_MOVE_FWD;
					_next = startPrepTime;

				}
				else if (scontrol_input - stn < 0) {
					_state = PREP_MOVE_BWD;
					_next = startPrepTime;

				}
				  else {
					//print invalid
				}
			}
			if(msg.val == STOP_PROC){
				_state = PREP_STOP;
				_next = Time::Zero;
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
    }

    void print()  noexcept {
    	SWO_PrintString("wcontrol");
    }

};

}
}
}
}


#endif /* WheelController_HPP_ */


