# System Monitoring

### Project not finished yet.

### This project implements a program that collects operating system metrics and writes them to a log file, and then displays them in an interface.

# Building

`make` - Build and run program.

### To run the agents that collect information it is necessary to compile them into dynamic libraries

`make <agent_type>`

### Agent types: 

- `cpu_agent`
- `memory_agent`
- `network_agent`
- `special_agent`
- `vmemory_agent`
- `swap_agent`
- `system_agent`

### The agent will send you a telegram notification in case one of the metrics exceeds the configured limit. In order to change the limit, you need to configure the .ini file in the configs folder.
