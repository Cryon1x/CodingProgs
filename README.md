# CodingProgs 
This repo consists of a sample program written in C: 

- A vacuum bot simulator with built-in location APIs.

The following describes how the source material is written.

# Main

Main contains calls to each API, which in turn regulates each line that the user inputs. Each function has built-in error checking, though thorough tests haven't been performed. The functions loop for as many voombots as needed. 

A "VOOMBOT" struct stores information about the vacuumbot's direction and location.

# roomsize API

The roomsize function accepts two pointers and assigns them values corresponding to the room's size as prompted on the cmd line. 

# botlocator API 

The botlocator function prompts the user for the initial cartesian coordinates of the vacuum bot as well as a direction. The function checks if the values are within the room, and assigns directions to integers mod 4. Subsequent functions will use the same direction modulo 4 system to parse through voombot movements. The location is stored in the voombot struct.  

# botparser API

The botparser function prompts the user for the movements of the voombot. The voombot is not allowed to leave the room at any point in the instruction set. The new location is stored in the voombot struct. 

# trav API

The trav function traverses the voombot struct and prints the location and direction of all voombots.



 
