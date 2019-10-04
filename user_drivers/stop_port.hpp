/*

 * stop_port.hpp
 *
 *  Dated: Dec, 2018
 *  Authors: Navneet Kaushal, Vithika Joshi
 */

#ifndef stop_port_HPP_
#define stop_port_HPP_

using namespace std;
using namespace boost::simulation;
using namespace boost::simulation::pdevs;
using namespace boost::simulation::pdevs::basic_models;

template<class TIME, class MSG>
class START_IN : public port<TIME, MSG>
{
public:
    /**
     * @brief startbtn constructor.
     */
     explicit START_IN(const std::string &n = "start_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};


template<class TIME, class MSG>
class STOP1_IN : public port<TIME, MSG>
{
public:
    /**
     * @brief Stop-IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit STOP1_IN(const std::string &n = "stop1_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class STOP2_IN : public port<TIME, MSG>
{
public:
    /**
     * @brief Stop-IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit STOP2_IN(const std::string &n = "stop2_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class STOP3_IN : public port<TIME, MSG>
{
public:
    /**
     * @brief Stop-IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit STOP3_IN(const std::string &n = "stop3_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class STOP4_IN : public port<TIME, MSG>
{
public:
    /**
     * @brief Stop-IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit STOP4_IN(const std::string &n = "stop4_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class STOP5_IN : public port<TIME, MSG>
{
public:
    /**
     * @brief Stop-IR sensor constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit STOP5_IN(const std::string &n = "stop5_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class OSTOP1_IN : public port<TIME, MSG>
{
public:
    /**
     * @brief Out-Stop button constructor.
     *
     * @param n Name assigned to the port.
     * @param polling Polling period associated with the port.
     */
     explicit OSTOP1_IN(const std::string &n = "ostop1_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class OSTOP2_IN : public port<TIME, MSG>
{
public:
     explicit OSTOP2_IN(const std::string &n = "ostop2_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;

};

template<class TIME, class MSG>
class OSTOP3_IN : public port<TIME, MSG>
{
public:
     explicit OSTOP3_IN(const std::string &n = "ostop3_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class OSTOP4_IN : public port<TIME, MSG>
{
public:
     explicit OSTOP4_IN(const std::string &n = "ostop4_in", const TIME &polling = TIME(0,0,0,200)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class OSTOP5_IN : public port<TIME, MSG>
{
public:
     explicit OSTOP5_IN(const std::string &n = "ostop5_in", const TIME &polling = TIME(0,0,1,0)) noexcept : port<TIME, MSG>(n,polling) {}
     void print()  noexcept {}
     bool pDriver(int &cmd,int &v) const noexcept;
};

template<class TIME, class MSG>
class START_OUT : public port<TIME, MSG>
{
public:
    /**
     * @brief motor1_port constructor.
     *
     * @param n name assigned to the port
     */
     explicit START_OUT(const std::string &n = "START_OUT") noexcept : port<TIME, MSG>(n) {}//printf("M1 CREATED \n");
     void print() noexcept{}//printf("WHEEL 1 \n");
     bool pDriver(int &cmd, int &v) const noexcept;

};
#endif /* stop_port_HPP_ */
