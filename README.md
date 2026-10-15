# SystemMonitor

A lightweight Linux system monitor built with C++ and ROS 2.

## Overview

SystemMonitor collects and processes system metrics to monitor
the performance and resource usage of a Linux machine.

The project uses ROS 2 to distribute monitoring tasks across
independent nodes, exploring concurrency, multithreading,
and inter-process communication in C++.

## Features

Planned features:

- Real-time CPU and memory monitoring.
- Disk and network usage monitoring.
- Detection of resource-intensive processes.
- Configurable alerts for excessive resource consumption.
- Terminal-based monitoring interface.

## Tech Stack

- **Language:** C++17
- **Framework:** ROS 2
- **Build System:** CMake
- **Platform:** Ubuntu 24.04
- **Version Control:** Git

## Architecture

The application will consist of independent ROS 2 nodes
responsible for collecting, processing, and displaying
system metrics.

Concurrency will be handled using C++ threading primitives
and ROS 2 executors.

## Requirements

- Ubuntu 24.04
- ROS 2 Jazzy
- GCC 13 or later
- CMake 3.28 or later

## Build and Installation

Instructions will be added once the initial ROS 2
workspace and build system are configured.

## Project Status

Early development.

This project is being developed incrementally as a
practical exercise in modern C++ and ROS 2.