PROJECT_NAME 	= 	s21_MonitoringSystem
DIRS			=	agents
gcc				= 	gcc $(flags)
flags			= 	-lstdc++ -Werror -Wall -Wextra
SOURCES		   :=	$(shell find $(DIRS)/sources -name '*.cc')
SOURCES		   +=   $(shell find core -name '*.cc')
LIBS			= 	libs/agents_lib
FIND_OBJECT		=	$(shell find objects/*.o)
OBJECT 		    =   $(patsubst %*.cc, %*.o, $(FIND_OBJECT))


all: clean build

clean:
	rm -rf s21_MonitoringSystem

build: cpu_agent.a cpu_special_agent.a memory_agent.a network.a swap_agent.a vmemory_agent.a system_agent.a utils.a agent_core.a
	ar rc agents_lib $(OBJECT)
	mv agents_lib libs/agents_lib
	$(gcc) main.cc $(LIBS) -o $(PROJECT_NAME)
	clear
	./$(PROJECT_NAME)

agent_core.a:
	$(gcc) -c core/agent_core.cc -o objects/agent_core.o

cpu_agent.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'cpu_agent.cc') -o objects/cpu_agent.o
	
cpu_special_agent.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'cpu_special_agent.cc') -o objects/cpu_special_agent.o

memory_agent.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'memory_agent.cc') -o objects/memory_agent.o

vmemory_agent.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'vmemory_agent.cc') -o objects/vmemory_agent.o

swap_agent.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'swap_agent.cc') -o objects/swap_agent.o

system_agent.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'system_agent.cc') -o objects/system_agent.o

utils.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'sub_functions.cc') -o objects/sub_functions.o

network.a:
	$(gcc) -c $(shell find $(DIRS)/sources -name 'network_agent.cc') -o objects/network_agent.o

clang-replace:
	clang-format --style=Google -i $(SOURCES)

clang:
	clang-format --style=Google -n $(SOURCES)