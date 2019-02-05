John Hoare

CS528 Project 3 
Reinforcment Learning
=====================

In this directory is the common code for both versions, go into the appropriate
directory to build the code. 

There are two directories: 
  * stage2
  * stage3
stage2 is for stage2, which uses the player c++ client libraries. This is for 
working with the verison of stage installed on the lab machines. 

stage3 is for stage version 3, where it is written as a control plugin. This 
can be used in stage3 to train/run the robot at much faster than real time. 
This is what I used to train the robot, so I had to wait much less time to get 
the robot to train. 

Both versions are run differently, look at the README.txt in each directory for
instructions on how to buid them.

The provided learned Q table is in "trained-state.dat" so when you run either
of the two versions (stage#) you can use this trained-state.dat to load a 
learned table.
