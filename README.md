# CS225_final_project_Y4GO

#### To run the project, please:
1. put the project folder under course docker container.
2. use terminal to create build folder in project folder by typing `mkdir build` .
3. change directory to build by `cd build`.
4. type `cmake ..` in terminal of build folder to build project.
5. compile the project by typing `make`.
6. to test the project, type `./test` after compiling.
7. to run the project, type `./main` after compiling.
	* to run the project, please type the source of data and names of airport following the instruction in command line.
8. to change data sources, place them in data folder and type the absolute/relative path in command line following instruction.


#### Project code linkage and location description:
* The code derived from course materials are placed in `project/lib/cs225` folder, edge and graph class and their utility functions are placed there. 
Files list:
	* edge.h
	* graph.h
	* graph.cpp
	* random.h
	* random.cpp
*  The code of information container and graph calculator are placed in `project/src` folder. Most of implementation of this project is placed in src folder. 
Files list:
	* graph_constructor.h
	* graph_constructor.cpp 
	* info_constructor.h
	* info_constructor.cpp
*  The main function are placed in `project/entry` folder. 
Files list:
	* main.cpp
*  Data are placed in `project/entry` folder,they are files downloaded from [OpenFlights](https://openflights.org/data.html).
Files list:
	* airlines.txt
	* airports.txt
	* routes.txt
