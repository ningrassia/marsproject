marsproject
===========

CS 559 Project 2 Repo!

NOTE: I worked for a long time to implement a new, working specular shader that allowed mars to have a dark side. It was a no go.\
	  I didn't have time to implement texture or better controls.
	  Those are my two big goals.
	  We have a non-specular shader, but it is not implemented yet.
	  But our only bonus at this point is moderate ship control and the toon shader. Maybe stars count.
	  We gotta decide what we want to add and then do it.
	  I am tired.
	  i am going home to die.

TODO:

	- Alternate shader for Mars (too shiny)
	- Set up shader so mars has a dark side 
	- texture Mars
	- Modify ship movement in 3rd person, so awkward
	- Maybe add a spotlight??? perhaps? we'll see.
	- Clean up code
	- CLEAN. UP. CODE.
	
DONE:
	- Speeding up rotation even needed? It looks bad
	- 'NOGGLE'
	- Comment out '[' and ']' polygon functionality
	- Change text color so it doesn't run into the stars
	- Make 1sta dn 3rd person view different perspectives
	- Change camera view / move ship up / pull camera back in ship mode
	- Mouse movement/Mouse wheel FOV

	
	

Structure stuff:
Files/Object
Mars
Ship
Starfield
Mesh - parent class


Bonus ideas:
Ship movement
Collision for ship/mars? - constant distance from planet or super-fancy physics or both?
Utah teapot somewhere?
texture mars?
Starbucks.
Modify mars mesh on-the-fly - environment destruction? shoot mountains away?
Adjust scaling factor of Mars - how jagged can we make it?
Shadow?
Spaceship mounted light?

CODING STANDARDS:
Variables named with underscore, all lowercase
	e.g.: int scooter_count
Functions named in camelcase, uppercase first word
	e.g.: void AddWheel()
Curly brackets: you like to do next line. I like to do same line except for functions.
	...we'll talk about that one.