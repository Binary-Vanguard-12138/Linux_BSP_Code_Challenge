# 1. Synchronization

## Project requirements description

Attached in the `src` folder you will find a sample project written in `C`.

Parts of the code are missing, indicated by `<... fill in ...>`, and need to be filled.

The application is a simple client server system. The client will connect to the server and print the difference between its own time and that of the server. For the solution UDP sockets neeed to be used.

Please add the missing parts to the source files and provide a compilable and working solution.
Also, create the instructions how the code should be compiled.

## Compilation and running of the project

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

### Running examples

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

# 2. Remote software update

## Question

Given you have an enterprise grade Linux system with a large number of devices used by customers. The devices can only be reached remotely. If you would have the freedom to setup a remote update system from scratch, how would you set it up?

Please provide a short, high-level description of your design.

## Answer

### Consideration

To set up a remote update system for a large number of devices used by customers, I should build a high-performance, distributed, scalable and reliable system probably using microservice architecture.

And for this purpose, I would consider using the following techiniques.

- Distribution network: The update system should include a content distribution network (CDN) that can store the firmware updates and distribute the updates efficiently to remote locations. The CDN should offer redundancy, caching updates that are frequently used, and load balancing.

- Security: The remote update system should be secure with end-to-end encryption and secure communication protocols. The distributed system should incorporate security by design where the system checks the authenticity of the update and the device.

- Monitoring: The system should be designed to monitor events and automatically notify administrators when a device is out of compliance or when an update fails.

- Scalability: The system should be built with scalability in mind, to allow it to scale to thousands or even millions of devices easily. To support this, the system should use microservices architecture, load balancers, and containerization technologies like Kubernetes.

### Design

In terms of updating system, we can normally use 2 kind of methods: Pull and Push.

- Push method means that there is a central server, and it pushes the change of product to the customers' devices when the update is made.
- Pull method means that there is a central server on the cloud, and each client i.e. customers' devices will poll the changes of product from the server and update itself when the new update is found on the server.

For our updating system for large-scale customer devices, I prefer the Pull method.
Beause in most cases, the customers divices such IoT devices will not have public IP address and the central server can not connect to them directly. So in order to use Push method, the server should keep the connections to all of the client devices, and it will cause overhead for the server.

So I think we would better to use Pull method.
In this architecture, the central server will keep information about the version of the product including version number and product packages.
And the client devices will pull the current version information from the central server periodically (maybe once per day or any period we need) and update itself when the newer version is found on the server.

And the server needs to have seperated components to provide the brief version information and product packages, so the product packages can be delivered by CDN.

The diagram entire architecture can be given as follows.
![Update System](/img/Update%20System.drawio.png)
