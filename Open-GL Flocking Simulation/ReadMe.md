# Open-GL-Flocking-Implementation

Table of Contents
- [Description](#Description)
- [Application](#Application)
- [What is a Flock?](#Flock)
- [Running](#Running)

## Description

This is a project made using Visual Studio, OpenGL, and C++ to implement a 2-Dimensional Flocking Algorithm. This was assigned to for my Computer Graphics course at Texas Wesleyan Univesrity where, were we instructed to created a Flocking Simulation that would do ### three of the following implementations:

  * Animate the individual flock member to move as either fish or birds
  * Steering a flock member using keyboard or mouse. Allow a user to control a single agent using either keyboard or mouse interaction. This will require having an agent   specified that is considered the agent being controlled.
  * Adversarial agents. Allow a subset of agents to be considered adversarial agents. They will be more interested in attacking other agents rather than the flocking rules.
  * Life or agent status. Allow the agent's life to vary depending on how far it's traveled, if it's surrounded by too many other flock members, it's being attacked, or collides. The status of the agent can reduce or grow depending on rules you set up. Display the status (visually) for each agent.
  * Camera tracking and zoomed in view. Allow an option to have the camera zoomed in to a specific agent (for example the controlled agent). The view should be updated as the agent moves.
  * Collision detection and resolution with the environment blocked areas.
  * Code analysis. Analyze the running time of the code. This should be a detailed description of all aspects of the simulation. What proportion of the time is spent in each of the main components? Does the proportion of the time change as the number of agents increases? It should be done for varying number of agents. What is the maximum number of agents that the simulation can have and still be considered real-time.
  * Integrate this 2D Flocking code with your 3D World program. This should allow you to see a very interesting scene. Objects in the 3D world should correspond to blocked cells in the 2D scene.

### From the provide options to implement for this assignment, the following were implemented:
  * Animate the individual flock member to move as either fish or birds
  * Adversarial agents. Allow a subset of agents to be considered adversarial agents. They will be more interested in attacking other agents rather than the flocking rules.
  * Life or agent status. Allow the agent's life to vary depending on how far it's traveled, if it's surrounded by too many other flock members, it's being attacked, or collides. The status of the agent can reduce or grow depending on rules you set up. Display the status (visually) for each agent.
    
## Application

This project implements the use of boid to represent a Flocking Simulation that animates each member of a flock to move as fish, implements Adversairial Agents (allow agents to become more interested in attacking other agents rather than the flocking rules), and implement a Life Span for Each Agent (Display the status of an agent's life for each agent that is implemented via visual cues).

For the implementation of animating the individual flock members to move as either fish or birds, Fish are implemented to translate and rotate with the bounds of the environment. The way which the fish are rendered are separeated into 3 parts (body, tail, and fins). For the body, a polygon is generated as an ellipses that consists of 360 vertices so that it gives a round look). This body would act as the canvas for both the Tails and the fins of the Fish. This ellipse would translate throught the environment by the position of the agent's X and Y Position and would rotate based on the agent's orientation. The ellipse would be rendered with its length using placed on the x-axis and its width being palced on the y-axis. The ellipse's length is the size of the radisu, and the ellipse's width is half the size of the radius, and its color is depened on if the agent is an adversary or not. 

Upon the body of the fish being rendered, the tail of the fish is rendered. The tail is also rendered using a Polygon. Unlike the Body of the fish (which translates at the X and Y Positions of the agent), the tail translates at the position of (0, -1) of the matrix. The reason for this is to offset tail from the body so that it looks consistent upon the agent rotating and to prevent it from overlapping with the body of the fish. Additionally, the color of the fish’s tail also deviate from the color of the agent. Regardless of the color of the fish’s body, the color of the fish’s tail will remain as a Grayish Color. The same logic regarding the fin of the fish remains consistent as well. With the only exception that the fin’s offset is set at the position of (-11, 2).

For the Implementation of Adversarial Agetns, the implementation implements two things. The first thing being that they would avoid the rules of flocking like other agents, and the second being that they would locate the closest non-adversarial agent. This would allow for the simulation of a prey vs predator behavior. Essentially allow for a set agent to attack another agent as if it were occurring in nature. For visualizations, two separate and distinct colors are designated to distinguish between adversaries and agents. For the agents that were not designated as non-adversaries. They appeared as a blue color, and for agents that appeared as agents, they appeared as a red color. The color of red is purposely chosen for the adversaries as a way indicate these were agents that were purposely made to cause some form of chaos that occurred in the simulation.  The color of blue is purposely chosen for the agents to indicated that these were the agents that were to peacefully flock with other non-adversarial agents that existed within the simulation. Thus, the adversaries doing their jobs as intended for the simulation since they are meant cause some disturbance to flock. 

For the Life Span Implementation, this implementation is designed so that it would  kill both adversarial and non-adversarial agents the longer and longer that they existed with the simulation. For this piece of functionality, functionality is implementated that woudl decremanted a value from the color that was assigned to both the Adversarial and Non-Adversarial Agents that existed within the simulation. For each millisecond that the agent exists in the simulation, the dark and dark it’s color would become. For Adversarial Agents, the color-value that becomes darker and darker is red and for Non-Adversarial Agents, the color-value that becomes darker and darker would be blue. So once either red or blue becomes so dark that it has reached black, then that agent would be “killed” and removed from the simulation. The color black was chosento represent this as it is often associated with death, and as the agent would be essentially dying when reaching a certain point of existing within the simulation for too long.

## Flock

In the Paper, Flocks, Herds, Schools: A Distributed Behavioral Model, it discusses the challenges to be able to allow computer animators to be able to animate animals (such as birds) in such a way that it simulates the same way that they do in nature. The primary challenge here being in formulating a way that would allow for flocks of birds, schools of fish, and other such clusters of agents to be able to move both dynamically and fluidly without having the need for those actors to move in a pre-defined way. The approach to be able to solve this problem was through the implementation and the creation of Boids.

### What are Boids? 
Boids are defined as "...an entire geometrical object consisting of a full local coordinate system and a reference to a geometrical shape model." They are derivative of particles system that have been used to be able to render different effects such as fire, smoke, and clouds. This is where both Boids and particle systems are quite like one another, both implement the use of different objects that each have behaviors such as: which state they are currently in, the color they are, the degree of opacity that they fall under, the location that they currently exist at, and the velocity that they are moving at. However, where particle systems and Boids end up diverging on each is modeled geometrically. While particle systems have historically been modeled using dots, Boids are typically rendered using geometric shapes. Each geometric shape having full control over their local transform. Boids can control: the rotation that they rotate and the size that they are scaled to. This allows for them to be able to exhibit an array of different behaviors based on where they may exist with the environment that they are being rendered in. 

### How do Boids aid in Flocking Simulations?
Through the implementation of Boids, this allows for flocks of birds, schools of fish, and herds of cattle to be simulated more dynamically. Instead of needing to implement several different paths for each object, a data structure is implemented for each object that handles the rules that are necessary for each Boids. This allows for each Boids to behave independently from all other Boids. The only requirements that are needed for each Boids is the location of where each one will spawn at, and the size that it will be scaled to. Upon these conditions being set, the Boids can determine which axis they would need to use to follow for them to be able to move forward, which acceleration they cannot exceed above, the bounds that Boids need to stay within (if any exist), prevent itself from colliding with other Boids that exist in the same environment, and move with other Boids that exist within a certain radius to it. Essentially, Boids are needed to be able to regulate their own velocity so that they do not exceed the velocity of all other Boids that exist within the same cluster as itself. This is to allow for flocking to exist within a rendered environment without needing to calculate pre-existing paths to follow.  	

In addition to this implementation needed to Boids to be able to make it own decisions, it also needed to have a ruleset for Boids that allow for it to avoid obstacles that exist within its environment. While it is important for a given Boid to avoid colliding into other Boids that exist with the same level as itself, it is also crucial that Boids have the functionality to be able to make decisions to allow it avoid obstacles. The reason being obstacles have the potential for a given Boid to broken apart from their flock. If one Boid encounters an obstacle, it must be able to have a means of being able to get around the given obstacle that is in its path and rejoin either its initial flock or a new flock that it happens to be much closer to. The way that this is implemented is using a “force field”. A “force field” (within the context of a Boid) is “...a 3 x 3 matrix operator that transform from a point in space.” Force fields would be used to be able to detect a potential overlap between the Boid and the obstacle that overlaps the forcefield allow the Boid to be able to avoid it. Thus, allowing the Boid to make a decision how it wants to proceed from there without have its decision impact the other Boids.

During its lifetime, Boids are influenced by the forces of Rotation, Velocity, Acceleration, and Gravity. The reason these forces are considered for each step for the duration of the simulation is so that each Boid can decide on how it wants to be able to move throughout the simulation. Within 3D Environments, Boids would need to consider gravity as a major force since it would need to consider if it would need to readjust rotation about its X Axis, Y Axis, or Z Axis. Mainly so that all it could maintain flight throughout the simulation (assuming that this is a need condition for the given Boid). As for the remaining forces of Rotation, Velocity, and Acceleration, those forces are applied to allow for each Boid to have the ability to move through the simulator. Velocity being fast it can move, Acceleration being the change of velocity that a Boid experiences, and Rotation being the direction that the Boid is movin towards. Without taking these forces into consideration throughout its lifetime, each Boid would not be able to do anything. Thus, preventing it from being able to simulate anything. 

## Running
To run the simulation, click on the "Flocking Simulation Release" under releases. Click on and download the .zip file provided in the release, unzip the .zip file, and double click on "Flocking-Algorithm.exe" to run it. 

### How to run the Simulation?

In the simulation, it will initially start as paused. To run the simulation, you will just need to press on the spacebar to activate it. Upon it running, you will see the Flocking Simulation run as intended. As the Simulation runs, you will also see the agents in the simulation change color until they are destroyed. 

Right-clicking on the Simulation will spawn a menu. You will see 5 options displayed.
  * Toggle Adversary - Clicking this will toggle between spawning Adversaries and Agents within the Simulations Environment upon clicking on either Add Group and Individual again
  * Add Attraction Point - Clicking this will mark to spawn an attraction point in the simulation that spawn at the cursor location upon clicking on the left-mouse button
  * Add Group - Clicking this will mark to spawn a group of 5 agents/adversaries that spawn at the cursor location upon clicking on the left-mouse button
  * Add Individual - Clicking this will mark to spawn 1 agent/adversary that spawn at the cursor location upon clicking on the left-mouse button
  * Quit - This will terminate the simulation

### Additionally on your keyboard you can press:
  * Q/ESC - To Terminate Simulation
  * SpaceBar - To Start/Pause Simulation
  * F - To play a single frame of the simulation. NOTE: holding this will allow for the simulation to run in slow-motion
  * 1 - Will render Agents as Fish
  * 2 - Will render Agents as Triangles
  * 3 - Will render Agents as Circles
