# Open-GL-Flappy-Bird

Table of Contents
- [Description](#Description)
- [What is Flappy Bird?](#FlappyBird)
- [Application](#Application)
- [Running](#Running)

## Description

Flappy Bird Assignment I made for my Computer Graphics that I took during my last semester at Texas Wesleyan University. This was implemented using C++, Visual Studio, and OpenGL. The purpose of this project is to make create a game and practice the use of functions, and utlized some light OOP (Object-Oriented Programming) to implemented addition functionality.
    
## FlappyBird

Flappy Bird is a popular mobile game that gained immense popularity in early 2014 for iOS and Android platforms. In Flappy Bird, players a bird that must navigate through a series of pipes that have gaps in them. The bird automatically moves forward, and the player's taks is to make the bird fly thought the gaps in the pipes by tapping the screen. Each successful pass through a gap awards the player one point. Despite the simple and easy-to-understand gameplay mechanics, but it is also notoriously difficult. The bird is affected by gravity, and tapping the screen causes the bird to flap its wings and rise briefly. The challenge lies in maintaining the bird's altitude and timing the flaps correctly to pass through the gaps without hitting the pipes or the ground.
   
## Application

The application is designed to run a clone of flappy bird that was designed and implemented from scratch using OpenGL and C++. The program itself using the stand glutInits, glMatrix Modes, and background setting functionality that would be used for implementing a standard project using the OpenGL API. However, in addition to those functionalities, it utilizes callback functions to add with gameplay functionality that would be used for the Flappy Bird Clone. 

### What is a Callback Function?

Callback Functions are functionality that are registered with the OpenGL library to be called at a specific event or state change during the rendering process. Callback functions in OpenGL allow developers to handle various events or perform custom actions when certain conditions are met.

OpenGL is primarily a graphics rendering API that provides a set of functions for rendering 2D and 3D graphics. Callback functions enhance the flexibility of the API by enabling developers to customize behavior in response to specific events or rendering stages. Some common callback functions in OpenGL include:

   * Display Callback - This function is responsible for drawing the scene and is typically registered to be called when the application's window needs to be redrawn. It is commonly used to draw the objects and geometry of the scene.
   * Reshape Callback - This function is called when the window is resized, allowing developers to adjust the viewport and projection matrix accordingly to maintain the correct aspect ratio and projection.
   * Mouse Callback - These functions handle mouse-related events such as mouse button presses, releases, and mouse movement. They are used to interact with the scene, e.g., rotating, zooming, or selecting objects.
   * Keyboard Callback - These functions handle keyboard-related events, such as key presses and releases. They are used to implement keyboard controls for the application.
   * Timer Callback - Some OpenGL frameworks allow developers to set up a timer callback that triggers at regular intervals, enabling time-based animations or updates.

### Which callback functions are used for the project?

For the functionality for this program, the GLUT Callback functions are used for the background functionality. Of the GLUT Callback Functions, the functions used are:

   * glutMouseFunc - used to register a callback function that will be called whenever a mouse button is pressed or released within the application's window.
   * glutKeyboardFunc - used to register a callback function that will be called whenever a keyboard key is pressed while the window associated with GLUT is in focus.
   * glutDisplayFunc - used to register a callback function that is responsible for rendering or displaying the contents of the OpenGL window.
   * glutReshapeFunc - when the window is resized, GLUT will call the registered callback function to inform your program about the new window size, allowing you to adjust the OpenGL viewport and projection accordingly.
   * glutIdleFunc - used to create animations or perform continuous updates in your OpenGL application.

### Which implemented functions are used in the Callback functions?

The following functions are paired with one of the previously mentioned GLUT Functions:

   ### mouseCallBack
   * This function handles mouse button clicks and starts the bird's motion or simulation.
   * When the left mouse button is clicked (btn == GLUT_LEFT_BUTTON) and the mouse state is "down" (state == GLUT_DOWN), the following actions are performed:
       * It sets the hasStarted flag to true, indicating that the game has started.
       * It sets the isSimulating flag to true, indicating that the simulation is running.
       * It calls the bounce() function
         
   ### keyboardCallBack
   * This function is responsible for handling keyboard input events.
   * It takes three parameters: key (the pressed key), x and y (mouse coordinates at the time of the key press).
   * The function uses a switch-case statement to handle different keys.
       * 'i' or 'I' key:
           * If the simulation is not running (isSimulating is false), it starts the simulation by setting isSimulating to true.
           * If the simulation is already running (isSimulating is true), it stops the simulation by setting isSimulating to false and disables the idle function (removes the idle callback using glutIdleFunc(NULL)).
       * ' ' (space) key:
           * It sets the hasStarted flag to true, indicating that the simulation or game has started.
           * It sets the isSimulating flag to true, indicating that the simulation is running.
           * It calls the bounce() function, which means the bird will experience a "bounce" or rebound effect when the space key is pressed.
       * 'q' or ESC (Escape) key:
           * It exits the program by calling exit(-1).
       * Any other key:
           * It does nothing (default case).

   ### displayCallBack
   * This is the display callback function that renders the entire game scene. It is called by GLUT to redraw the screen after a change in the game state or after the glutPostRedisplay() function is called.
       * The camera follows the player character when it moves to the right (bird_x > w_width / 2), ensuring that the player remains in view.
       * The background is cleared (glClear(GL_COLOR_BUFFER_BIT)) and set to black (glClearColor(0.0f, 0.0f, 0.0f, 1.0f)).
       * The player character (DrawMissile), the two stripes (DrawStripeA and DrawStripeB), and the pipes (pipe.Draw()) are drawn.

   ### reshapeCallback
   * This function is called whenever the window is resized.
   * It takes two parameters, width and height, which represent the new dimensions of the window after resizing.
   * The purpose of this function is to update the global variables w_width and w_height to reflect the new window dimensions.
   * w_width and w_height (Globals):
       * These are global variables used to store the width and height of the window.
       * These variables are likely defined outside the scope of the reshapeCallback function, allowing them to be accessed and modified from other parts of the program.

   ### update
   * This function is called periodically and handles the game's main update logic.
   * It updates the bird's acceleration, velocity, and position based on the simulation rules.
   * The bird's bird_ay (acceleration in the y-direction) is influenced by the impulse, which is reduced gradually over time (impulse *= 0.98).
   * It calls the boundVelocityAcceleration function to ensure the bird's velocity and acceleration are within certain limits.
   * It also checks for collisions with the top and bottom window boundaries and sets the bird's position and velocities accordingly.
   * The function updates the position of the pipes and checks for collisions between the bird and the pipes. If there is a collision, the killPlayer flag is set to true.
   * After updating the bird's state and the pipes, it calls glutPostRedisplay() to request a redraw of the scene.
  
### Additionaly Functions and Class

In addition to the previously mentioned function, these additional bits of functionality are also implemented:

   ### Class
   * ### Pipe - The class appears to represent a pipe-like object in a 2D game or simulation. The Pipe class has a constructor, a method to check for overlap with another object, and a Draw() method for rendering the pipe.
       * Constructor
           * The constructor initializes the Pipe object with default values for its position and dimensions.
           * It sets the initial values of x to 1400 (horizontal position), y to 200 (vertical position), and w to 50 (width).    
       * isOverlapping(double x, double y, int r)
           * This method checks if a point (x, y) with a given radius r overlaps with the pipe.
           * The method calculates the distance between the point (x, y) and the center of the pipe using the distance formula.
           * If the calculated distance is less than the given radius r, it means there is an overlap, and the method returns true. Otherwise, it returns false.
       * Draw()
           * This method is responsible for rendering the pipe on the screen using OpenGL graphics commands (GL_QUADS).
           * The pipe is drawn using three sets of quadrilaterals (GL_QUADS) to create a pipe-like structure with three sections, one on top of the other.
           * The bottom section of the pipe has a height equal to y, which sets the vertical position of the pipe.
           * The width of the pipe is set by the value of w.
           * The pipe's color is set to green (glColor3f(0, 195, 0)).
   
   ### Functions
   * DrawMissile(float r, int num_segments)
       * This function is responsible for drawing the missile-like object.
       * It takes two parameters: r (radius) and num_segments (number of segments for the circle approximation).
       * The function divides a circle into segments and approximates the missile's shape using filled polygons (GL_POLYGON) to represent its front, middle, and back parts.
       * The missile is drawn using a combination of vertices calculated using trigonometric functions (cos and sin) to achieve the desired shape.
   * DrawStripeA(float r)
       * This function is responsible for drawing a stripe on the missile-like object.
       * It takes one parameter: r (radius of the missile).
       * The stripe is drawn using filled quadrilaterals (GL_QUADS) with a random color (generated by randomColorValue()).
       * The stripe is positioned on the missile's middle part, making it appear as part of the missile's design.
   * DrawStripeB(float r)
       * This function is similar to DrawStripeA but draws another stripe in a different position on the missile.
       * The stripe is also drawn using filled quadrilaterals (GL_QUADS) with a random color (generated by randomColorValue()).
       * The position of this stripe is different from the first stripe, providing additional details to the missile's appearance.
   * bounce()
       * This function appears to handle some form of "bounce" behavior for the bird.
       * It increases the value of the variable impulse by the value of impulseMax
       * It increases the value of the variable bird_ax by 2.
   * boundVelocityAcceleration(double& vx, double& vy, double& ax, double& ay)
       * This function is used to bound the velocity and acceleration values of the bird.
       * It takes four parameters by reference: vx (velocity in the x-direction), vy (velocity in the y-direction), ax (acceleration in the x-direction), and ay (acceleration in the y-direction).
       * If the vx exceeds the maximum allowed velocity (vxMax), it sets vx to vxMax.
       * If the vy exceeds the maximum allowed velocity (vyMax), it sets vy to vyMax.
       * If the ax exceeds 20, it sets ax to 20.
       * If the ay is less than -10, it sets ay to -9.
   * boundImpulse()
       * This function is used to bound the impulse value (likely related to some kind of force applied to the bird).
       * If the impulse exceeds the maximum allowed impulse (impulseMax), it sets impulse to 33.
       * If the impulse falls below 0.5, it sets impulse to 0.    

## Running
To run the simulation, click on the "FlappyBird-OpenGL" under releases. Click on and download the .zip file provided in the release, unzip the .zip file, and double click on "FlappyBird-OpenGL.exe" to run it.

### How to run the Game?

In the Game, you will be met with a missle that will be the stand-in for the "bird" for the flappy-bird clone. Upon either left-clicking or pressing the spacebar, the game will start. You will be meet with a cluster of different heighted rectangles that will be the stand-in for the "pipes". The game will continue to run until the bird hits one of the pipes. Once the bird is dead, you can kill the game with either "Q" or "Escape" keys, and relaunch the game to play again. 
