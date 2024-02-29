//
//  MyInitial.cpp   - Version 0.4 - October 24, 2020
//
//   Sets up and renders the initial (alphabet letter)
//   for the Math 155A project.
//
//   Comes supplied with some code for a cylinders, a torus,
//      and a revolving ellipsoid.
//
//  THIS FILE IS WHAT YOU WILL MODIFY FOR PROJECT #3.
//  IT WILL ALSO BE USED FOR PROJECTS #4 and #5.
//


// Use the static library (so glew32.dll is not needed):
#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "LinearR3.h"		// Adjust paths as needed.
#include "LinearR4.h"		
#include "GlGeomSphere.h"
#include "GlGeomCylinder.h"
#include "GlGeomTorus.h"

// Enable standard input and output via printf(), etc.
// Put this include *after* the includes for glew and GLFW!
#include <stdio.h>

#include "MyInitial.h"
#include "InitialProj.h"
//#include "SurfaceProj.h"      // Replace previous line with this line for Project #4

// ***********
// Animation Controls.  
//     Optional: you may customize these for Project #3.
// ***********

// YOU MAY WISH TO RE-DO THIS FOR YOUR CUSTOM ANIMATION.  
double animateIncrement = 0.01;   // Make bigger to speed up animation, smaller to slow it down.
double currentTime = 0.0;         // Current "time" for the animation.
double maxTime = 1.0;             // Time cycles back to 0 after reaching maxTime.
int dir = 1;
// These two variables control whether running or paused.
//  IT IS OPTIONAL TO INCLUDE THIS FUNCTIONALITY IN YOUR PROGRAMMING ASSIGNMENT
bool spinMode = true;
bool singleStep = false;


// These objects take care of generating and loading VAO's, VBO's and EBO's,
//    rendering ellipsoids and cylinders
// IF YOU ADDED EXTRA TORII, THEY SHOULD BE DECLARED HERE
GlGeomSphere unitSphere;
GlGeomCylinder unitCylinder;
GlGeomTorus torus1(6, 6, 0.1f);   // Set default mesh resolutions and inner radius
                                  // Initialize multiple tori if they have different inder radii.

// **********************
// This sets up a sphere and a cylinder and a torus needed for the "Initial" (the 3-D alphabet letter)
//  This routine is called only once, for the first initialization.
//  IF YOU ADD EXTRA TORII, THEY NEED TO HANDLED HERE.
// **********************
void MySetupInitialGeometries() {
    // Initialize the sphere and cylinder, and give them the vertPos, vertNormal, and vertTexCoords locations.
    MyRemeshGeometries();
    unitSphere.InitializeAttribLocations(vPos_loc,vNormal_loc,vTexcoords_loc);
    unitCylinder.InitializeAttribLocations(vPos_loc, vNormal_loc, vTexcoords_loc);
    torus1.InitializeAttribLocations(vPos_loc, vNormal_loc, vTexcoords_loc);

    check_for_opengl_errors();
}

// *********************
// This is called when geometric shapes are initialized.
// And is called again whenever the mesh resolution changes.
// IF YOU ADD EXTRA TORII, THEY NEED TO BE HANDLED HERE
// ********************
void MyRemeshGeometries() {
    unitSphere.Remesh(meshRes, meshRes);              // Number of slices and stacks both set to meshRes
    unitCylinder.Remesh(meshRes, meshRes, meshRes);   // Number of slices, stacks and rings all set to meshRes
    torus1.Remesh(meshRes, meshRes);                  // Number of rings and number of sides per ring.
}

// *************************************
// Render the initial (3D alphabet letter)
// THIS CODE IS THE CORE PART TO RE_WRITE FOR YOUR 155A PROJECT  ****************************
// ************
void MyRenderInitial() {
    // Compute the "currentTime" for the animation.
    //    As initially implemented, CurrentTime goes from 0.0 to 1.0, and then back to 0.0
    //    THIS IS SPECIFIC TO THE ANIMATION IN THE DEMO.
    //    FOR PROJECT 3 YOU MAY DO SOMETHING DIFFERENT, FOR INSTANCE, SIMILAR TO WHAT 
	//       THE SOLAR SYSTEM PROJECT DID.
    //  

    if (spinMode) {
        currentTime += animateIncrement;
        if (currentTime >= maxTime) {
            currentTime = currentTime - floor(currentTime/maxTime);  // Floor function = round down to nearest integer
            dir = -1 * dir;
        }
        if (singleStep) {
            spinMode = false;       // If in single step mode, turn off future animation
        }
    }
   
    // Render the letter "X" (Sam's initial) with two cylinders,
    //    Plus a revolving ellipsoid.
   
    // Setup the main Model view matrix
    LinearMapR4 mat1 = viewMatrix;              // Base off of viewMatrix
    mat1.Mult_glTranslate(-2.5,2.0, -2.5);     // Center of the letter

    glVertexAttrib3f(vColor_loc, 0.9f, 0.6f, 0.2f);

    LinearMapR4 mat2 = mat1;
    if (dir == 1)
        mat2.Mult_glScale(currentTime);
    else
        mat2.Mult_glScale(1.0 - currentTime);

    mat2.Mult_glScale(0.4, 2.0, 0.3);
    mat2.Mult_glTranslate(-3.0, 0.0, 0.0);
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitCylinder.Render();

    glVertexAttrib3f(vColor_loc, 0.7f, 0.2f, 0.9f);

    mat2.Mult_glTranslate(6, 0.0, 0.0);
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitCylinder.Render();

    
    glVertexAttrib3f(vColor_loc, 0.4f, 0.9f, 0.4f);
    mat2 = mat1;
    mat2.Mult_glRotate(35.0/180.0*PI,0.0,0.0,1.0);
    if (dir == 1)
        mat2.Mult_glScale(currentTime);
    else
        mat2.Mult_glScale(1.0 - currentTime);
    mat2.Mult_glScale(0.4, 2.2, 0.2);
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitCylinder.Render();

    glVertexAttrib3f(vColor_loc, 0.1f, 0.9f, 0.9f); 
    mat2 = mat1;                             
    mat2.Mult_glScale(2.0, 1.0, 2.0); 
    //mat2.Mult_glTranslate(0.0, dir*-2.0, 0.0);
    mat2.Mult_glTranslate(0.0, dir*(currentTime*4-2.0), 0.0);
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    torus1.Render();

    glVertexAttrib3f(vColor_loc, 0.8f, 0.0f, 0.0f);
    mat2 = mat1;
   
    mat2.Mult_glRotate(1*currentTime * PI2, 0.0, 1.0, 0.0);
    mat2.Mult_glTranslate(0.0, -dir * (currentTime * 4 - 2.0), 2.0);
    
    mat2.Mult_glScale(0.2);

    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitSphere.Render();

    glVertexAttrib3f(vColor_loc, 0.1f, 0.1f, 1.0f);
    mat2 = mat1;

    mat2.Mult_glRotate(-1 * currentTime * PI2, 0.0, 1.0, 0.0);
    mat2.Mult_glTranslate(0.0, -dir * (currentTime * 4 - 2.0), 2.0);

    mat2.Mult_glScale(0.2);

    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitSphere.Render();
    /*
    // Make the X partgreen-ish (YOU ARE ENCOURAGED TO ALTER COLORS)
    glVertexAttrib3f(vColor_loc, 0.4f, 0.9f, 0.4f); 
    
    // Draw first cylinder of the X
    LinearMapR4 mat2 = mat1;                   // Modelview matrix for cylinders & sphere
    mat2.Mult_glTranslate(0.0, 0.0, 0.3);         // Translate slightly towards the viewer  
    mat2.Mult_glRotate(-PIsixths, 0.0, 0.0, 1.0); // Rotate -30 degrees
    mat2.Mult_glScale(0.4, 2.0, 0.2);          // Scale the cylinder, to thiner, flater and taller 
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitCylinder.Render();

    // Draw the second cylinder of the X
    mat2 = mat1;                               // Back to the main Modelview matrix
    mat2.Mult_glTranslate(0.0, 0.0, -0.3);        // Translate slightly away from the viewer
    mat2.Mult_glRotate(PIsixths, 0.0, 0.0, 1.0);  // Rotate 30 degrees
    mat2.Mult_glScale(0.4, 2.0, 0.2);          // Scale the cylinder, to thiner, flater and taller 
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitCylinder.Render();

    // Render the torus
    glVertexAttrib3f(vColor_loc, 0.8f, 0.0f, 0.0f);  // Red color (slightly darkened)
    mat2 = mat1;                              // Back to the main Modelview matrix
    mat2.Mult_glScale(0.8);                   // Uniform scaling
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    torus1.Render();

    // Render the revolving ellipsoid
    glVertexAttrib3f(vColor_loc, 0.6f, 0.4f, 1.0f);  // Blue/Magenta-ish color
    mat2 = mat1;                              // Back to the main Modelview matrix
    mat2.Mult_glRotate(currentTime*PI2, 0.0, 1.0, 0.0);   // PI2 is 2*pi (defined in MathMisc.h)
    mat2.Mult_glTranslate(0.0, 0.0, 1.8);     // Pull towards the viewer (for revolution)
    mat2.Mult_glScale(0.5, 0.2, 1.0);         // Nonuniform scaling  
    mat2.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
    unitSphere.Render();

    */




    
}








