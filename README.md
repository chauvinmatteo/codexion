*This project has been created as part of the 42 curriculum by mchauvin.*
# Codexion

## Description

Codexion is a concurrency simulation project designed to master multi-threading, resource synchronization, and scheduling in C. The project simulates a team of coders who must compete for shared resources (dongles) to complete compilation tasks while adhering to strict time constraints to avoid burnout.

The simulation handles:

- Concurrency: One POSIX thread per coder and a dedicated monitor thread.
- Resource Management: Fair arbitration between coders to acquire dongles.
- Scheduling: Implementation of FIFO (First-In-First-Out) and EDF (Earliest Deadline First) algorithms to manage the resource queue.
- Liveness: Prevention of deadlocks and starvation in a resource-constrained environment.

## Instructions

### Compilation

Compile this project at the root of the repository.
```sh
make
```

### Execution

To run the simulation, use the following structure:

```sh
./codexion [number_of_coders] [time_to_burnout] [time_to_compile] [time_to_debug] [time_to_refactor] [number_of_compiles_required] [dongle_cooldown] [scheduler]
```
- `number_of_coders`: > 0
- `time_to_burnout`: > 0
- `time_to_compile`: >= 0
- `time_to_debug`: >= 0
- `time_to_refactor`: >= 0
- `number_of_compiles_required`: >= 0
- `dongle_cooldown`: >= 0
- `scheduler`: 'fifo' or 'edf'

### Schedulers
#### FIFO (First In First Out)
Dongles are assigned to the first coder who requested them.

#### EDF (Earliest Deadline First)
Dongles are assigned to the coder with the earliest deadline, calculated as: (last_compile_start + time_to_burnout)

To remove object files and other build artifacts:
```sh
make clean
```

To remove object files, build artifacts, and the executable:
```sh
make fclean
```

To re-build the project:
```sh
make re
```
## Blocking cases handled

This project addresses several critical concurrency challenges:

- Deadlock Prevention: We satisfy Coffman’s conditions by enforcing a strict resource acquisition order in assign_locks (resource hierarchy) and using a centralized queue, preventing circular wait scenarios.

- Starvation Prevention: The scheduler queue ensures that coders are processed in a fair order, preventing any single thread from being indefinitely deprived of dongles.

- Cooldown Handling: Dongle availability is protected by mutexes and timestamp tracking. Coders respect the cooldown period before a dongle can be re-acquired.

- Precise Burnout Detection: The monitor thread continuously verifies timestamps in real-time, ensuring burnout is detected and logged within the required precision window.

- Log Serialization: A global print_lock ensures that output messages are serialized and never interleaved, preserving simulation history integrity.

## Thread synchronization mechanisms

The implementation relies on standard POSIX threads:

- pthread_mutex_t: Used for individual coder locks (state protection), resource locks (dongle access), and global state management (simulation running status, print serialization).

- pthread_cond_t: Used for signaling, allowing coders to wait for state transitions (like resource availability) efficiently without busy-waiting.

- Thread Safety & Race Conditions:

    - Forward Declarations: The architecture uses forward declarations (typedef struct s_codex t_codex) to break circular dependencies while keeping structures modular.

    - Atomic State Checks: Access to the running flag is guarded by state_lock to ensure all threads detect the simulation stop signal simultaneously.

    - Cleanup Handlers: free_codexion is implemented in critical sections to guarantee that mutexes are released even if a thread exits unexpectedly, preventing "held lock" deadlocks.

## Resources

- Documentation: https://man7.org/linux/man-pages/man7/pthreads.7.html

- Concepts: Operating System Concepts (Silberschatz et al.) regarding Deadlocks and Synchronization.

AI Usage: AI was used to assist in the architectural design of the include/ structure, the debugging of synchronization deadlocks via Helgrind trace analysis, and the formalization of the Makefile dependencies to ensure efficient recompilation.