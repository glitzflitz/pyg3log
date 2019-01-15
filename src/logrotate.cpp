#include <pybind11/complex.h>
#include <pybind11/embed.h>
#include <pybind11/functional.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <g3log/g3log.hpp>
#include <g3log/logworker.hpp>
#include <memory>
#include <string>
#include <utility>

#include "g3sinks/LogRotate.h"

namespace py = pybind11;


py::class_<LogRotate>(m,"LogRotate")
    .def(py::init<const std::string&, const std::string&>())
	.def("save", &LogRotate::save)
	.def("changeLogFile",&LogRotate::changeLogFile)
	.def("logFileName",&LogRotate::logFileName)
	.def("setMaxArchiveLogCount",&LogRotate::setMaxArchiveLogCount)
	.def("getMaxArchiveLogCount",&LogRotate::getMaxArchiveLogCount)
	.def("setFlushPolicy",&LogRotate::setFlushPolicy)
	.def("flush",&LogRotate::flush)
	.def("setMaxLogSize",&LogRotate::setMaxLogSize)
	.def("getMaxLogSize",&LogRotate::getMaxLogSize);
