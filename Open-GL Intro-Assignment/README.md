# Open-GL-Intro-Assignment

Table of Contents
- [Description](#Description)
- [What is OpenGL?](#OpenGL)
- [Application](#Application)
- [Running](#Running)

## Description

This is a project made using Visual Studio, OpenGL, and C++ to implement a Simple 2d Project. This was assigned to for my Computer Graphics course at Texas Wesleyan University during my last semester. The purpose of this assignment was to practice basic usage of the OpenGL API.

## OpenGL

OpenGL (Open Graphics Library) is a cross-platform and open-source graphics rendering API (Application Programming Interface) that provides developers with a set of functions for rendering 2D and 3D graphics. Additionally, it's a low-level graphics API that gives developers direct control over graphics hardware, but it requires more effort and code compared to higher-level graphics libraries or engines. It is widely used in computer graphics, video games, virtual reality applications, scientific visualization, and other interactive visual applications. Key features of OpenGL include:

   1. Platform Independence - OpenGL is designed to be platform-independent, allowing developers to write code once and run it on various operating systems without significant modifications.
   2. Hardware Acceleration - OpenGL is capable of utilizing hardware acceleration if available, which means it can leverage the capabilities of the GPU (Graphics Processing Unit) to enhance graphics rendering performance.
   3. 3D Graphics Support - OpenGL is specifically designed to handle 3D graphics rendering efficiently. It provides functions for creating 3D objects, applying transformations, setting up cameras, and performing lighting calculations.
   4. Shading Language - OpenGL includes a shading language called GLSL (OpenGL Shading Language), which allows developers to write custom shaders to control how graphics primitives are rendered and shaded.
   5. Primitive Rendering - OpenGL provides functions for rendering basic primitives such as points, lines, and triangles, which can be used to create complex 3D scenes.
   6. Texture Mapping - OpenGL supports texture mapping, allowing developers to apply images to 3D objects for adding details and realism to the rendered scenes.
   7. Double Buffering - OpenGL uses double buffering to avoid visual artifacts such as flickering during rendering. This technique helps provide smoother animation and rendering results.
   8. Wide Adoption - OpenGL is widely supported across various platforms and hardware, making it a popular choice for developers looking to create cross-platform applications.
 
## Application

This program uses the OpenGL library to create a graphical application. The application allows the user to draw various shapes (boxes, polygons, stars, dots, and lines) on the screen using the mouse and keyboard. The program is broken down in the following parts:

### Includes and Namespaces
The code includes necessary libraries, such as:
   * iostream - provides input and output stream classes
   * vector -  standard template container class that represents a dynamic array. 
   * cmath - a set of functions to compute common mathematical operations and transformations
   * GL/glut.h - a header file used in computer graphics programming with OpenGL (Open Graphics Library) and GLUT (OpenGL Utility Toolkit).
The code also implements the following namespace(s):
   * std namespace - a construct that allows you to access the elements (such as classes, functions, and variables) from the C++ Standard Library
   
### Global Variables
Several global variables are defined, including:
   * color components - r1, g1, b1
   * window width and height - winW, winH
   * a vector to store the coordinates of drawn shapes - boxes
   * an enumeration for different graphics types - graphics

### Functions
Several functions are defined for drawing different shapes, such as:
   * drawBox - Renders all graphics contained in boxes as a box
   * drawPolygon - Renders all graphics contained in boxes as a polygon
   * drawStar - Renders all graphics contained in boxes as a Star
   * drawDot - Renders all graphics contained in boxes as a Dot
   * drawLine - Renders all graphics contained in boxes as a Line
   * MyRand - Returns a random decimal value
   * initGL - initialization function that sets the background color (clearing color) for the graphical window.

### Callback Functions
This describes the callback functions for handling display, reshape, keyboard, and mouse events. The covers events such as:
   * display function - responsible for drawing the graphics and shapes on the screen.
   * reshape function - responsible for handling window resize events.
   * keyboard function - handles keyboard input events
   * mouse function - handles mouse input events

### Driver Function
The main function initializes the GLUT library, creates a window, sets up callback functions, and enters the event-processing loop with glutMainLoop.

## Running

To run the program, click on the "Open-GL-Intro-Assignment" under releases. Click on and download the .zip file provided in the release, unzip the .zip file, and double click on "Assignment.exe" to run it.

When running the program, you will be met with your a multi-colored block with a face and a mustache. There you will be able to be spawn different shapes into the environment. By default you will be able to spawn squares into the environment. However, you will be able to change the shapes into various different shapes by pressing:

   * B - Will convert all existing shapes in environment into boxes and allow new boxes to be spawned by left-clicking on a spot in the environment.

   * P - Will convert all existing shapes in environment into polygons and allow new boxes to be spawned by left-clicking on a spot in the environment.

   * D - Will convert all existing shapes in environment into dots and allow new boxes to be spawned by left-clicking on a spot in the environment.

   * L - Will convert all existing shapes in environment into lines and allow new boxes to be spawned by left-clicking on a spot in the environment.

   * S - Will convert all existing shapes in environment into stars and allow new boxes to be spawned by left-clicking on a spot in the environment.

In addition to this functionality, you will be able to press:

   * Q/ESC - to Terminate the application

   * R - To change the color of shapes to a random color

   * C - To clear all shapes that currently exist in the environment from the environment
