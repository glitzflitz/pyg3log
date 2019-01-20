# pyg3log
Python wrapper for G3Log a C++ logging library

## Introduction 
pyg3log is python wraapper around [G3log](https://github.com/KjellKod/g3log) an asynchronous, "crash safe" C++ logging library.

## Installation
```pip install pybind11```

```pip install pyg3log```
# From github:
```
git clone https://github.com/GreyDireWolf/pyg3log.git
cd pyg3log
git submodule update --init --recursive
python setup.py install
```
## Usage
```
import pyg3log as log
#Create log worker for displaying log messages on terminal/console
log.createConsoleLogWorker()
>>> import pyg3log as log
>>> log.createConsoleLogWorker()
>>> log.info("Some information", "random amount of parameters")
    2019/01/20 23:42:30 058417	INFO [pyg3log.cpp->operator():81]
    ('Some information', 'random amount of parameters')
>>> log.debug("Hello World" , 123, 656.736)
    2019/01/20 23:40:33 312192	DEBUG [pyg3log.cpp->operator():78]
    ('Hello World', 123, 656.736)
>>> log.closeLogWorker()
>>> log.createDefaultLogWorker("pyg3log", "/tmp") #OR just log.createDeafultLogWorker()
>>> log.warning("WARNING",2355,34.54)
>>> logArchive = log.LogRotate("archiveName", "/tmp ")
>>> logArchive.save()
