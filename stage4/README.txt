Building
========

The stage3 plugin is built using "cmake" 

Basically, in the stage3 directory, do the following: 

  * mkdir build 
  * cd build
  * cmake ..
  * make 

And this will have built the code, as a plugin for stage3. 


Running
=======

(This is all assuming you have stage3 installed on your system, which is 
 not true on the lab systems)

To run the code, you need to run a world file with stage. I have one made 
in the cfg/ directory. 

Before you run stage, you also have to set the STAGEPATH environment 
variable, so stage knows where to find the plugin.

  * export STAGEPATH='../build'
  * stage autolab-confined.world 

This code will automatically load state.dat if it exists, otherwise it will 
start from scratch. Things like epsilon and if it updates are not both need
to be changed in hoare-Project3-stage.cpp and recompiled. 
