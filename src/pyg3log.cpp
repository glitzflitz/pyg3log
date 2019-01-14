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

#include "ConsoleLogSink.h"

#define PYLOG(LEVEL)                                                         \
    std::stringstream out;                                                   \
    using expander = int[];                                                  \
    (void)expander{0, (void(out << ' ' << std::forward<py::args>(arg)), 0)}; \
    LOG(LEVEL) << out.str();

//static auto worker = g3::LogWorker::createLogWorker();

namespace py = pybind11;
//Creates logworker for custom sink
//TODO:
//Find better way to wrap custom sinks with templates
void createConsoleLogWorker()
{
  
 
    static auto worker = g3::LogWorker::createLogWorker();

    static auto handle = worker->addSink(std::make_unique<ConsoleLogSink>(),
                                         &ConsoleLogSink::ReceiveLogMessage);
    g3::initializeLogging(worker.get());
}
//Creates logworker with default sink
void createDefaultLogWorker(std::string log_prefix, std::string path_to_log_file)
{


    static auto worker = g3::LogWorker::createLogWorker();

    static auto handle = worker->addDefaultLogger(log_prefix, path_to_log_file);
    g3::initializeLogging(worker.get());
}

PYBIND11_MODULE(pyg3log, m)
{

    m.def("createDefaultLogWorker", &createDefaultLogWorker, "Creates a new log worker and default handle", py::arg("log_prefix") = "g3log", py::arg("path_to_log_file") = "/tmp");
    m.def("createConsoleLogWorker", &createConsoleLogWorker, "Create a new log worker to display log on console");

    m.def("closeLogger", [] {
        //worker.reset();
        //handle.reset();
        g3::internal::shutDownLogging();
    });
    m.def("debug", [](py::args arg) {
        PYLOG(DEBUG);
    });
    m.def("info", [](py::args arg) {
        PYLOG(INFO);
    });
    m.def("warning", [](py::args arg) {
        PYLOG(WARNING);
    });
    m.def("fatal", [](py::args arg) {
        PYLOG(FATAL);
    });

    m.def("log_if_debug", [](bool condition, py::args arg) {
        if (condition)
        {
            PYLOG(DEBUG);
        }
    });

    m.def("log_if_info", [](bool condition, py::args arg) {
        if (condition)
        {
            PYLOG(INFO);
        }
    });

    m.def("log_if_warning", [](bool condition, py::args arg) {
        if (condition)
        {
            PYLOG(WARNING);
        }
    });

    m.def("log_if_fatal", [](bool condition, py::args arg) {
        if (condition)
        {
            PYLOG(FATAL);
        }
    });
    m.def("check", [](bool condition, py::args arg) {
        std::stringstream out;
        using expander = int[];
        (void)expander{0, (void(out << ' ' << std::forward<py::args>(arg)), 0)};
        CHECK(condition) << out.str();
    });
}
