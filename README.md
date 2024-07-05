Lid Driven Cavity Solver Parallelized with MPI
Project Overview
This project was developed as part of the EPCC HPC Summer School 2024. The focus is on solving the Lid Driven Cavity problem using a parallel approach with MPI (Message Passing Interface).

Introduction
The Lid Driven Cavity problem is a classic benchmark problem in computational fluid dynamics (CFD). It involves a square cavity with a lid that moves at a constant velocity, inducing a flow within the cavity. The goal is to simulate the fluid motion and analyze the resulting velocity and pressure fields.

Features
Parallel Computation: Utilizes MPI to parallelize the computation, improving performance on multi-core and distributed memory systems.
Scalability: Designed to efficiently scale with the number of processors.
Accuracy: Implements numerical methods to ensure accurate results.
Requirements
MPI Library (e.g., MPICH, OpenMPI)
C/C++ Compiler
Make
