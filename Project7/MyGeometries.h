#pragma once

// 
// MyGeometries.h   ---  Header file for MyGeometries.cpp.
// 
//   Sets up and renders 
//     - the ground plane, and
//     - the surface of rotation
//   for the Math 155A project #4.
//
//

//
// Function Prototypes
//
void MySetupSurfaces();                // Called once, before rendering begins.
void SetupForTextures();               // Loads textures, sets Phong material
void MyRemeshGeometries();             // Called when mesh changes, must update resolutions.

void MyRenderGeometries();            // Called to render the two surfaces

void setupCube();
void renderCube(LinearMapR4 cubematrix, float* matEntries);
LinearMapR4 axisRotation(LinearMapR4 mat, float x, float y, float z, float r,char axis);

