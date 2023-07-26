PROJECT_NAME 	= 	s21_MonitoringSystem
DIRS			=	agents
gcc				= 	gcc $(flags)
flags			=   -lstdc++ -std=c++17 -g -Werror -Wall -Wextra
SOURCES		   :=	$(shell find $(DIRS)/sources -name '*.cc')
SOURCES		   +=   $(shell find core -name '*.cc')
LIBS			= 	libs/agents_lib
FIND_OBJECT		=	$(shell find objects/*.dylib)
OBJECT 		    =   $(patsubst %*.cc, %*.dylib, $(FIND_OBJECT))


all: clean build

clean:
	@rm -rf s21_MonitoringSystem objects/*.o objects/*.dylib objects/*.dSYM

clean_dll:
	rm -rf objects/*.dylib

build: utils.a config.a agent_core.a
	$(gcc) main.cc $(shell find objects -name '*.o') -o $(PROJECT_NAME)
	clear
	./$(PROJECT_NAME)

agent_core.a:
	$(gcc) -c core/agent_core.cc -o objects/agent_core.o

cpu_agent.a:
	$(gcc) -shared -o objects/cpu_agent.dylib objects/sub_functions.o objects/config.o $(shell find $(DIRS)/sources -name 'cpu_agent.cc')
	
cpu_special_agent.a:
	$(gcc) -shared -o objects/cpu_special_agent.dylib objects/sub_functions.o $(shell find $(DIRS)/sources -name 'cpu_special_agent.cc')

memory_agent.a:
	$(gcc) -shared -o objects/memory_agent.dylib objects/sub_functions.o objects/config.o $(shell find $(DIRS)/sources -name 'memory_agent.cc')

vmemory_agent.a:
	$(gcc) -shared -o objects/vmemory_agent.dylib objects/sub_functions.o $(shell find $(DIRS)/sources -name 'vmemory_agent.cc')

swap_agent.a:
	$(gcc) -shared -o objects/swap_agent.dylib objects/sub_functions.o $(shell find $(DIRS)/sources -name 'swap_agent.cc')

system_agent.a:
	$(gcc) -shared -o objects/system_agent.dylib objects/sub_functions.o $(shell find $(DIRS)/sources -name 'system_agent.cc')

utils.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'sub_functions.cc') -o objects/sub_functions.o

network_agent.a:
	$(gcc) -shared -o objects/network_agent.dylib objects/sub_functions.o $(shell find $(DIRS)/sources -name 'network_agent.cc')

config.a:
	$(gcc) -c configs/config_parser.cc -o objects/config.o

clang-replace:
	clang-format --style=Google -i $(SOURCES)

clang:
	clang-format --style=Google -n $(SOURCES)