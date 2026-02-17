# pipex — UNIX Pipeline Reimplementation in C

## Overview

**pipex** is a systems-level reimplementation of UNIX shell pipelines written in C.
It replicates the behavior of:

```bash
< infile cmd1 | cmd2 > outfile
```

using only low-level system calls (`fork`, `pipe`, `dup2`, `execve`, `waitpid`, etc.), without invoking the shell.

The project emphasizes:

* Accurate process orchestration
* Deterministic file descriptor management
* Precise `errno` handling
* Shell-consistent exit codes
* Memory safety and structured cleanup

Rather than simply “making pipes work,” this implementation focuses on faithfully reproducing real shell semantics under edge conditions.

---

## Repository Structure

```
.
├── include
│   ├── pipex.h
│   └── pipex_types.h
├── libft
├── Makefile
├── README.md
└── srcs
    ├── pipex.c
    ├── pipex_cmd.c
    ├── pipex_error.c
    ├── pipex_exec.c
    ├── pipex_fd.c
    ├── pipex_freeup.c
    ├── pipex_init.c
    ├── pipex_io.c
    ├── pipex_paths.c
    ├── pipex_print.c
    ├── pipex_tokenizer.c
    └── pipex_utils.c
```

### Design Philosophy

The codebase is organized by responsibility:

* **Initialization** — pipeline construction and validation
* **Tokenization** — command argument splitting
* **PATH resolution** — candidate binary discovery
* **Execution** — fork, descriptor duplication, `execve`
* **FD management** — explicit descriptor lifecycle control
* **Error handling** — centralized `errno`-aware reporting
* **Cleanup** — deterministic resource destruction

Each module has a clearly scoped purpose, preventing cross-responsibility coupling.

---

## Functional Scope

The program executes:

```bash
./pipex infile "cmd1 args" "cmd2 args" outfile
```

Equivalent to:

```bash
< infile cmd1 args | cmd2 args > outfile
```

Behavior includes:

* Input redirection
* Output redirection
* Multiple command chaining
* Environment-based binary resolution
* Proper exit status propagation

---

## Execution Model

For each command in the pipeline:

1. A new process is created via `fork`.
2. Standard input/output is redirected using `dup2`.
3. Unused file descriptors are closed.
4. `execve` is invoked with the resolved binary path.
5. If execution fails, exit code is mapped deterministically.

### Descriptor Discipline

* All unnecessary file descriptors are closed **before** calling `execve`.
* No pipe ends are left open unintentionally.
* Deadlocks and hanging reads are prevented by design.

---

## PATH Resolution Strategy

Binary resolution follows shell-like behavior:

* Extract `PATH` from `envp`
* Split into directories
* Construct full candidate paths
* Attempt `execve` sequentially
* Track:

  * `EACCES` (permission denied)
  * `ENOENT` (not found)
  * first non-ENOENT error

Exit behavior mirrors shell semantics:

| Condition          | Exit Code   |
| ------------------ | ----------- |
| Command not found  | 127         |
| Permission denied  | 126         |
| General failure    | 1           |

Special care is taken to preserve `errno` correctly across helper functions.

---

## Error Handling

Error reporting is centralized and deterministic.

Handled cases include:

* Missing input file
* Output file without write permissions
* Invalid or empty command
* Missing `PATH`
* Binary exists but is not executable
* Allocation failure
* Partial initialization failure

All error paths:

* Free allocated memory
* Close open file descriptors
* Exit with correct status

No undefined behavior is tolerated.

---

## Memory Management

* No global variables
* Explicit ownership rules
* Deterministic cleanup ordering
* Verified with Valgrind (no leaks, no invalid access)

Resources are released even in early-failure paths.

---

## Build & Usage

### Build

```bash
make
```

### Example

```bash
./pipex infile "grep error" "wc -l" outfile
```

---

## Key Technical Skills Demonstrated

* UNIX process management (`fork`, `execve`, `waitpid`)
* Inter-process communication (pipes)
* Precise file descriptor lifecycle control
* Shell-consistent exit code modeling
* Accurate `errno` propagation and preservation
* Defensive systems programming in C
* Multi-process orchestration
* Modular architecture with strict separation of concerns
* Deterministic cleanup under failure conditions
* Advanced debugging of race conditions and descriptor states

---
