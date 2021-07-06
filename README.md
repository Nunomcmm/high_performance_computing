# What is this?
This repository is for save homeworks of course unit "High Performance Computing".

# Project 
It is intended that a solution be proposed with the following characteristics:
1. There can be no buffer overflow: An entity of type A can only create items only when
the buffer is not full (that is, entity A waits if the buffer is full);
2. There can be no buffer underflow: An entity B can only check out an item when the buffer does not
is empty;
3. No waiting because the buffer is busy;
4. No Entity A Starvation: An A entity does not wait forever to ship an item;
5. No Entity B Starvation: Entity B does not wait forever to encode an item.
Note that conditions 1, 2, 3, and 4 are security requirements (which an entity must not do)
and conditions 5 and 6 are progress requirements (what an entity must eventually do).

# Getting Started

The C code is in [Project_Ciphers.c](https://github.com/Nunomcmm/high_performance_computing/blob/master/Project_Ciphers.c).