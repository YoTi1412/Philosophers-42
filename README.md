# Philosophers

A solution to the dining philosophers problem implemented in C, demonstrating process synchronization and thread management.

## Description

This project is an implementation of the classic dining philosophers problem, where philosophers sit at a round table doing one of three things: eating, thinking, or sleeping. While eating, they need two forks (one for each hand), and there are as many forks as philosophers on the table. The challenge is to prevent deadlocks and ensure fair resource allocation.

## Features

- Two versions of implementation:
  - Mandatory part using threads and mutexes
  - Bonus part using processes and semaphores
- Real-time monitoring of philosophers' states
- Configurable number of philosophers and timing parameters
- Death detection system
- Optional meals counter

## Requirements

- GCC compiler
- Make
- UNIX-based operating system (Linux/Mac)
- pthread library
- semaphore library (for bonus part)

## Usage

### Compilation

For mandatory part (threads and mutexes):
```bash
make
```

For bonus part (processes and semaphores):
```bash
make bonus
```

### Running the Program

```bash
./philo [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] [number_of_times_each_philosopher_must_eat]
```

#### Parameters

1. `number_of_philosophers`: The number of philosophers and forks
2. `time_to_die`: Time in milliseconds after which a philosopher dies if they haven't started eating
3. `time_to_eat`: Time in milliseconds that it takes for a philosopher to eat
4. `time_to_sleep`: Time in milliseconds that a philosopher spends sleeping
5. `number_of_times_each_philosopher_must_eat` (optional): Program stops when all philosophers eat this many times

#### Example

```bash
./philo 5 800 200 200 5
```
This will start the simulation with:
- 5 philosophers
- Death timer of 800ms
- Eating duration of 200ms
- Sleeping duration of 200ms
- Program stops when each philosopher has eaten 5 times

## Implementation Details

### Mandatory Part (Threads)
- Uses pthread library for thread management
- Uses mutex locks for fork handling and synchronization
- Each philosopher is a thread
- Shared resources (forks) are protected by mutexes

### Bonus Part (Processes)
- Uses fork() for process creation
- Uses semaphores for synchronization
- Each philosopher is a separate process
- Shared resources are managed using semaphores

### Learning Resources

#### Books
- The Linux Programming Interface by Michael Kerrisk
  - Chapters 29-33: Comprehensive coverage of POSIX threads programming
  - Chapters 52-54: Deep dive into POSIX semaphores and their implementation

#### Video Tutorials

- CodeVault's "UNIX Threads in C" Playlist
  - URL: https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2
