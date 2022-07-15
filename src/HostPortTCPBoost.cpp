/*
 * Boost.Python definition for the Python binding
 */

#include "HostPortTCP.h"

#include <boost/python.hpp>
#include <boost/python/list.hpp>
#include <boost/python/extract.hpp>

using namespace boost::python;

//begin wrappers
bool (HostPortTCP::*begin2args)(std::string, unsigned short) = &HostPortTCP::begin;
bool (HostPortTCP::*begin4args)(std::string, unsigned short, unsigned int, unsigned int) = &HostPortTCP::begin;
bool (HostPortTCP::*begin5args)(std::string, unsigned short, unsigned int, unsigned int, unsigned int) = &HostPortTCP::begin;

// python module
BOOST_PYTHON_MODULE(hostporttcp)
{   
    
    sockpp::socket_initializer sockInit;

    //HostPortTCP class
    class_<HostPortTCP>("HostPortTCP")
        .def("begin", begin2args)
        .def("begin", begin4args)
        .def("begin", begin5args)
        .def("restart", &HostPortTCP::restart)
        .def("flush", &HostPortTCP::flush)
        .def("close", &HostPortTCP::close)
        .def("read", &HostPortTCP::readpy)
        .def("write", &HostPortTCP::writepy)
        .def("isInit", &HostPortTCP::isInit)
        .def("getPort", &HostPortTCP::getPort)
        .def("getIP", &HostPortTCP::getIP)
        .def("getHeader", &HostPortTCP::getHeader)
        .def("getTerminator", &HostPortTCP::getTerminator)
        .def("getTimeout", &HostPortTCP::getTimeout)
        .def("setPort", &HostPortTCP::setPort)
        .def("setIP", &HostPortTCP::setIP)
        .def("setHeader", &HostPortTCP::setHeader)
        .def("setTerminator", &HostPortTCP::setTerminator)
        .def("setTimeout", &HostPortTCP::setTimeout)
        .def(self_ns::str(self)) //operator <<
        .def_readonly("header", &HostPortTCP::HEADER)
        .def_readonly("terminator", &HostPortTCP::TERMINATOR)
        .def_readonly("timeout", &HostPortTCP::TIMEOUT)
        ;
    ;
};