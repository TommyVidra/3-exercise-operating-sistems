# 3-exercise-operating-sistems
My solutions in C, for OS third exercise.

There are 2 files in this repository. Vrtuljak.c (carousel), in which I made an C simulation using printfs, processes (forks) 
and sincing them with semaphores. The ride went like this:
  -all of the visitors enter the carousel and take their spot
  -if all of the spots are taken, carousel starts the ride
  -when the ride is over, carousel waits for all the visitors to get of, before going for another ride
All inputs are fetched through the comand line. //No. visitors, rides, seats

The second file is Nfilozofa.c (Nphilosophers). In this file the goal was to make an C simulation using printfs, monitors and threads.
Exeicise: 
  -there are N philosophers sitting at the table
  -they have 2 or more arms
  -their life is composed of eating and thinking. To eat rice thats in front of them, they need to have chopsticks in all of their arms
  -M numbere of chopsticks are placed at the center of the table
  -Once the philosopher is done eating he returns the chopsticks ack to the center fo another philosopher to use
  -when the philosopher is done eating, he thinks, then dies (leaves the table)
All inputs are fetched through a txt file named filozofi.txt. In next order:  
  No. of sticks + " " +  No. of philosophers, and every next line contains No. of arms for that philosopher
