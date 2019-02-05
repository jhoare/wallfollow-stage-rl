Building
========

To build this, you should only need to run "make" 


Running
=======

To run this, once you have built the code, run 

    ./hoare-Project3 epsilon [filename.dat] 

Where filename.dat is an optional paremeter to start the Q matrix.
If no filename is provided the program will create a new Q matrix and start 
from scratch. The Q matrix is always saved to 'state.dat' regardless of the 
filename.dat provided as an argument. 

epsilon is the initial epsilon, that will degrade over time. 

If you want to turn off the Updates, you'll have to comment out the 
Update() lines in the code and rebuild. 
