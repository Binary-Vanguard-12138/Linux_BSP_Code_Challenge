# Project requirements description

## 1. Synchronization

Attached in the `src` folder you will find a sample project written in `C`.

Parts of the code are missing, indicated by `<... fill in ...>`, and need to be filled.

The application is a simple client server system. The client will connect to the server and print the difference between its own time and that of the server. For the solution UDP sockets neeed to be used.

Please add the missing parts to the source files and provide a compilable and working solution.
Also, create the instructions how the code should be compiled.

## 2. Remote software update

Given you have an enterprise grade Linux system with a large number of devices used by customers. The devices can only be reached remotely. If you would have the freedom to setup a remote update system from scratch, how would you set it up?

Please provide a short, high-level description of your design.

# Compilation and running of the project

## Compilation

### Prerequisites

You should have `make` and `gcc` installed on your Linux development machine.

### Compilation

In the `bash` terminal, change directory(`cd`) to the root directory of the project and run `make`.

```bash
cd ~/Linux_BSP_Code_Challenge/
make
```

It will generate two executable binary files named `server` and `client`.

You can also clean up binary files by running `make clean`.

## Running examples

First, open bash terminal and run the server.

```bash
cd ~/Linux_BSP_Code_Challenge/bin/
./server -p 55555
```

Next, open another bash terminal and run the client.

```bash
cd ~/Linux_BSP_Code_Challenge/bin/
./client -h localhost -p 55555
```
