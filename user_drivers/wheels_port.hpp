/*
 * wheels_port.hpp
 *
 *  Dated: Dec, 2018
 *  Authors: Navneet Kaushal, Vithika Joshi
 */

#ifndef wheels_port_HPP_
#define wheels_port_HPP_

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

template<class TIME, class MSG>
class WHEEL1_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief wheel1_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit WHEEL1_OUT(const std::string &n = "wheel1") noexcept : port<TIME, MSG>(n) {}
     void print() noexcept{}
     bool pDriver(int &cmd, int &v) const noexcept;

};
template<class TIME, class MSG>
class WHEEL2_OUT : public port<TIME, MSG>
{

public:
    /**
     * @brief wheel2_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit WHEEL2_OUT(const std::string &n = "wheel2") noexcept : port<TIME, MSG>(n) {}
     void print() noexcept{}
     bool pDriver(int &cmd, int &v) const noexcept;

};

template<class TIME, class MSG>
class REQUEST_STOP : public port<TIME, MSG>
{
public:
     explicit REQUEST_STOP(const std::string &n = "StopNumber", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd, int &v) const noexcept;
};

template<class TIME, class MSG>
class LAST_STOP : public port<TIME, MSG>
{
public:
     explicit LAST_STOP(const std::string &n = "LastStop") noexcept : port<TIME, MSG>(n) {}
     void print() noexcept{}
     bool pDriver(int &cmd, int &v) const noexcept;

};

#endif /* wheels_port_HPP_ */
