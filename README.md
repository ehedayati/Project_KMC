# Project_KMC
The project defined by my adviser so as to learn crystal growth and KMC

## Requirements
gnuplot should be pre-installed on the system.
VMD should be pre-installed on the system

## Compiling
```
mkdir build
cmake ..
make -j 8
```
## Running
`./runme`

One small window will open and there will be opportunity to change the molecule 
size and Bond energy and Chemical Energy and the KMC Sweeps. 

*Start Simulation* button will run the simulation with the given data and in the
terminal one can see the number of layer growth, if its more than 0, continue,
otherwise change the initial conditions.

*Plot generation* button will generate plot using GNUPLOT software and shows the
average height change in every sweeps.

*Video generation* button. **Be ware**, this one takes a lot of time. The process
is shown in the terminal, the video will be opened once the generating part ends. 
Typically one should generate video if he is satisfied with the initial conditions
and wants to see the proof.