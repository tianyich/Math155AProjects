//
//  MySurfaces.cpp
//
//   Sets up and renders 
//     - the ground plane, and
//     - the surface of rotation
//   for the Math 155A project #4.
//
//   Comes supplied with the code for Sam Buss's "X".
//


// Use the static library (so glew32.dll is not needed):
#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "LinearR3.h"		// Adjust path as needed.
#include "LinearR4.h"		// Adjust path as needed.
#include "MathMisc.h"       // Adjust path as needed

#include "MySurfaces.h"
#include "PhongProj.h"


// ************************
// General data helping with setting up VAO (Vertex Array Objects)
//    and Vertex Buffer Objects.
// ***********************
const int NumObjects = 2;
const int iFloor = 0;
const int iCircularSurf = 1;

unsigned int myVBO[NumObjects];  // a Vertex Buffer Object holds an array of data
unsigned int myVAO[NumObjects];  // a Vertex Array Object - holds info about an array of vertex data;
unsigned int myEBO[NumObjects];  // a Element Array Buffer Object - holds an array of elements (vertex indices)

// **********************
// This sets up geometries needed for the "Initial" (the 3-D alphabet letter)
//  It is called only once.
// **********************
void MySetupSurfaces() {
    // Initialize the VAO's, VBO's and EBO's for the ground plane,
    // and the surface of rotation. Give them the "aPos" location,
    // and the "aNormal" location in the shader program.
    // No data is loaded into the VBO's or EBO's until the "Remesh"
    //   routines are called.

    // For the floor:
    // Allocate the needed Vertex Array Objects (VAO's),
    //      Vertex Buffer Objects (VBO's) and Element Array Buffer Objects (EBO's)
    // Since the floor has normal (0,1,0) everywhere, it will be given as
    // generic vertex attribute, not loaded in the VBO as a per-vertex value.
    // The color is also a generic vertex attribute.
    glGenVertexArrays(NumObjects, &myVAO[0]);
    glGenBuffers(NumObjects, &myVBO[0]);
    glGenBuffers(NumObjects, &myEBO[0]);

    glBindVertexArray(myVAO[iFloor]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);

    glVertexAttribPointer(vPos_loc, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);	// Store vertices in the VBO
    glEnableVertexAttribArray(vPos_loc);									// Enable the stored vertices
 
    // For the circular surface:
    // Allocate the needed VAO, VBO< EBO
    // The normal vector is specified separately for each vertex. (It is not a generic attribute.)
    // The color is still a generic vertex attribute.
    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);

    glVertexAttribPointer(vPos_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);	// Store vertices in the VBO
    glEnableVertexAttribArray(vPos_loc);									// Enable the stored vertices
    glVertexAttribPointer(vNormal_loc, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); // Store normals in the VBO
    glEnableVertexAttribArray(vNormal_loc);                                 // Enabled the stored normals (so they are not generic)

    // No data has been loaded into the VBO's yet.
    // This is done next by the "Remesh" routines.

    MyRemeshSurfaces();
    
    check_for_opengl_errors();      // Watch the console window for error messages!
}

// **********************************************
// MODIFY THIS ROUTINE TO CALL YOUR OWN CODE IN
//   MyRemeshFloor AND MyRemeshCircularSurf
// INSTEAD OF THE "DEMO" VERSIONS.
// **********************************************

void MyRemeshSurfaces() 
{
    // WRITE MyRemeshFloor (see below) AND USE IT INSTEAD OF RemeshPlaneDemo
    //RemeshFloorDemo();
    MyRemeshFloor();

    // WRITE MyRemeshCircularSurf (see below) AND USE IT INSTEAD OF RemeshCircularDemo
    //RemeshCircularDemo();
    MyRemeshCircularSurf();

    check_for_opengl_errors();      // Watch the console window for error messages!
}

// **********************************************
// MODIFY THIS ROUTINE TO CALL YOUR OWN CODE IN
//   MyRemeshFloor AND MyRemeshCircularSurf
// INSTEAD OF THE "DEMO" VERSIONS.
// **********************************************

void MyRenderSurfaces() {
    // WRITE MyRemeshFloor (see below) AND USE IT INSTEAD OF RemeshPlaneDemo
    //RenderFloorDemo();
    MyRenderFloor();

    // WRITE MyRemeshCircularSurf (see below) AND USE IT INSTEAD OF RemeshCircularDemo
//RenderCircularDemo();
    MyRenderCircularSurf();

    check_for_opengl_errors();      // Watch the console window for error messages!
}

// *********************************************
// THE CODE FOR THE NEXT FOUR "Demo" ROUIINTES BELOW GIVES SIMPLE FIXED SIZE OBJECTS:
// A plane gridded into 4x4 array of rectangles (triangulated)
// and Circular piece with 4 slices, and 4 rings.
// THIS CODE WILL NOT BE USED IN YOUR PROGRAMMING SOLUTION.
// INSTEAD, FINISH WRITING MyRemeshFloor() and MyRemeshCircularSurf() below.
// *********************************************************

// Make the floor a 4x4 grid of triangulated quads.
// Render it as four triangle strips.
void RemeshFloorDemo()
{
    // Floor vertices.
    float floorVerts[][3] = {
        { -5.0f, 0.0f, -5.0f }, { -2.5f, 0.0f, -5.0f }, { 0.0f, 0.0f, -5.0f }, { 2.5f, 0.0f, -5.0f }, { 5.0f, 0.0f, -5.0f },  // Back row
        { -5.0f, 0.0f, -2.5f }, { -2.5f, 0.0f, -2.5f }, { 0.0f, 0.0f, -2.5f }, { 2.5f, 0.0f, -2.5f }, { 5.0f, 0.0f, -2.5f },  // Fourth row
        { -5.0f, 0.0f,  0.0f }, { -2.5f, 0.0f,  0.0f }, { 0.0f, 0.0f,  0.0f }, { 2.5f, 0.0f,  0.0f }, { 5.0f, 0.0f,  0.0f },  // Third row
        { -5.0f, 0.0f,  2.5f }, { -2.5f, 0.0f,  2.5f }, { 0.0f, 0.0f,  2.5f }, { 2.5f, 0.0f,  2.5f }, { 5.0f, 0.0f,  2.5f },  // Second row
        { -5.0f, 0.0f,  5.0f }, { -2.5f, 0.0f,  5.0f }, { 0.0f, 0.0f,  5.0f }, { 2.5f, 0.0f,  5.0f }, { 5.0f, 0.0f,  5.0f },  // Front row
    };
    // Floor elements (indices to vertices in a triangle strip)
    unsigned int floorElements[] = {
        0,5,1,6,2,7,3,8,4,9,            // Elements for first triangle strip (back strip)
        5,10,6,11,7,12,8,13,9,14,       // Elements for second triangle strip
        10,15,11,16,12,17,13,18,14,19,  // Elements for third triangle strip
        15,20,16,21,17,22,18,23,19,24,  // Elements for fourth triangle strip (front strip)
    };
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(floorVerts), floorVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(floorElements), floorElements, GL_STATIC_DRAW);
}

void RemeshCircularDemo()
{
    // Circular surface as four triangle strips (low resolution)
    // Both vertex positions AND normal vectors
    // Note how this corresponds to the call to glVertexAttribPointer and glEnableVertexAttribArray
    //      in MySetupSurfaces() above.
    float circularVerts[] = {
        // Vertex positions     Normals (please make them *unit* vectors)
        0.0f, 1.0f, 0.0f,       0.0f, 1.0f, 0.0f,        // Central vertex
        0.0f, 0.866f, 0.5f,     0.0f, 0.866f, 0.5f,     // Over positive z axis
        0.0f, 0.5f, 0.866f,     0.0f, 0.5f, 0.866f,     
        0.5f, 0.866f, 0.0f,     0.5f, 0.866f, 0.0f,     // Over positive x-axis
        0.866f, 0.5f, 0.0f,     0.866f, 0.5f, 0.0f,
        0.0f, 0.866f, -0.5f,    0.0f, 0.866f, -0.5f,    // Over negative z axis
        0.0f, 0.5f, -0.866f,    0.0f, 0.5f, -0.866f,
        -0.5f, 0.866f, 0.0f,    -0.5f, 0.866f, 0.0f,    // Over negative x-axis
        -0.866f, 0.5f, 0.0f,    -0.866f, 0.5f, 0.0f,
    };
    // Circular elements (indices to vertices in triangle strips)
    unsigned int circularElements[] = {
        0, 1, 3, 2, 4,            // Elements for first triangle strip 
        0, 3, 5, 4, 6,            // Elements for second triangle strip
        0, 5, 7, 6, 8,            // Elements for third triangle strip
        0, 7, 1, 8, 2            // Elements for fourth triangle strip 
    };
    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(circularVerts), circularVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(circularElements), circularElements, GL_STATIC_DRAW);
}

void RenderFloorDemo()
{
    glBindVertexArray(myVAO[iFloor]);

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    glVertexAttrib3f(vNormal_loc, 0.0, 1.0, 0.0);    // Generic vertex attribute: Normal is (0,1,0) for the floor.
    //glVertexAttrib3f(vColor_loc, 1.0f, 0.4f, 0.4f);	 // Generic vertex attribute: Color (light red) for the floor. 
    myMaterials[0].LoadIntoShaders();
    viewMatrix.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)0);                              // Draw first triangle strip (back strip)
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(20 * sizeof(unsigned int)));    // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 10, GL_UNSIGNED_INT, (void*)(30 * sizeof(unsigned int)));    // Draw fourth triangle strip (front strip)
}

void RenderCircularDemo()
{
    glBindVertexArray(myVAO[iCircularSurf]);

    // Calculute the model view matrix for the circular surface
    LinearMapR4 matDemo = viewMatrix;
    matDemo.Mult_glTranslate(2.5, 1.0, 2.5);     // Center in the front right quadrant & raise up
    matDemo.Mult_glScale(3.0, 1.0, 3.0);         // Increase the circular diameter

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    //glVertexAttrib3f(vColor_loc, 1.0f, 0.8f, 0.4f);	 // Generic vertex attribute: Color (yellow-ish) for the circular surface. 
    myMaterials[0].LoadIntoShaders();
    matDemo.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    // Draw the four triangle strips
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)0);                             // Draw first triangle strip 
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(5 * sizeof(unsigned int)));    // Draw second triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(10 * sizeof(unsigned int)));   // Draw third triangle strip
    glDrawElements(GL_TRIANGLE_STRIP, 5, GL_UNSIGNED_INT, (void*)(15 * sizeof(unsigned int)));   // Draw fourth triangle strip 

}


// *********************************************
// THE CODE BELOW MUST BE WRITTEN FOR PROJECT 4.
// *********************************************

void MyRemeshFloor()
{
    // Sample code for allocating arrays of floats and unsigned int's with new[] and delete[]
	// The code fragment for allocating/deleting arrays uses C++ new and delete[].
	// You may optionally instead use the Standard Template Library std::vector<float> if you wish.
	
    // Floor vertices.
    int numFloorVerts = (meshRes + 1)*(meshRes + 1);
    float* floorVerts = new float[3 * numFloorVerts];
    // Floor elements (indices to vertices in a triangle strip)
    int numFloorElts = meshRes * 2 * (meshRes + 1);    
    unsigned int* floorElements = new unsigned int[numFloorElts];

    // YOU CAN NOW ACCESS floorVerts AND floorElements WITH THE SAME
    // SYNTAX AS ARRAYS.  FOR EXAMPLE,
    // floorVerts[0], floorVerts[1], floorVerts[2] ARE THE x,y,z
    // COMPONENTS OF THE FIRST VERTEX.

    float increment = 10.0f / meshRes ;
    for (int i = 0; i < meshRes+1; i ++) {
        for (int j = 0; j < 3*(meshRes + 1); j+=3) {
            floorVerts[i * (meshRes + 1) * 3 + j] = -5.0f + increment * (j / 3.0f);
            floorVerts[i * (meshRes + 1) * 3 + j + 1] = 0.0f;
            floorVerts[i * (meshRes + 1) * 3 + j + 2] = -5.0f + increment * i;
        }

    }
    for (int i = 0; i < numFloorElts; i++) {
        if (i % 2 == 0) {
            floorElements[i] = i / 2;
        }
        else {
            floorElements[i] = i / 2 + meshRes + 1;
        }
    }

    


#if 0
    // SOME SUGGESTED TEST CODE: Can be used to examine contents of your arrays
    printf("floorVerts:\n");
    for (int k = 0; k < numFloorVerts; k++) {
        printf("k =%3d:  pos = %7.4f, %7.4f, %7.4f. \n", k, floorVerts[3 * k], floorVerts[3 * k + 1], floorVerts[3 * k + 2]);
    }
    printf("floorElements:\n");
    for (int k = 0; k < numFloorElts; k++) {
        printf("%d, ", floorElements[k]);
    }
    printf("\n");
#endif

    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iFloor]);
    glBufferData(GL_ARRAY_BUFFER, numFloorVerts * 3 * sizeof(float), floorVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iFloor]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numFloorElts * 3 * sizeof(float), floorElements, GL_STATIC_DRAW);
    // The array should have been copied into the GPU buffers now.
    // If you use "new" above, you MUST delete the arrays here to avoid a memory leak.
    delete[] floorVerts;
    delete[] floorElements;
}

// ****
// MyRemeshCircularSurf: To be written for Project 4.
// ****
void MyRemeshCircularSurf()
{
    // WRITE THIS ENTIRE ROUTINE FOR THE CIRCULAR SURFACE
    // ALLOCATE MEMORY FOR ARRAYS, AND 
    // CALCULATE THE VERTEX DATA NEEDED FOR THE CIRCULAR SURFACE
    // THIS INCLUDES VERTEX POSITIONS AND NORMALS.
    // THEN LOAD THE DATA INTO THE VBO AND EBO BUFFERS
    // AND DELETE ANY TEMPORARILY ALLOCATED MEMORY.
    int numCircularVerts = (1 + meshRes * meshRes)*2;
    float* circularVerts = new float[3 * numCircularVerts];
    circularVerts[0] = 0.0f;
    circularVerts[1] = 1.0f;
    circularVerts[2] = 0.0f;
    circularVerts[3] = 0.0f;
    circularVerts[4] = 1.0f;
    circularVerts[5] = 0.0f;
  
    float rotation = PI2 / (float)meshRes;
    float dist =( 4.0f * PI) / (float)meshRes;
    float r = 0;
    for (int d = 0; d < meshRes; d++) {
        for (int i = 0; i < meshRes*6; i+=6) {
            r = dist * (i/6+1);
            circularVerts[d * meshRes * 6 + i + 6] =  r * (float)cos(d * rotation);
            circularVerts[d * meshRes * 6 + i + 7] = (1 + 0.08 * (r * r)) * sin(r) / r;
            circularVerts[d * meshRes * 6 + i + 8] = -r * (float)sin(d * rotation);
            circularVerts[d * meshRes * 6 + i + 9] = -(0.16 * sin(r) + ((r * cos(r) - sin(r)) * (1 + 0.08 * r * r)) / r / r)* (float)cos(d * rotation);
            circularVerts[d * meshRes * 6 + i + 10] = 1.0f;
            circularVerts[d * meshRes * 6 + i + 11] = (0.16 * sin(r) + ((r * cos(r) - sin(r)) * (1 + 0.08 * r * r)) / r / r) * (float)sin(d * rotation);
        }
    }

    int numCircularElms = meshRes * (2 * meshRes + 1);
    unsigned int* circularElements = new  unsigned int[3 * numCircularElms];
    int row, col;
    for (int i = 0; i < numCircularElms; i++) {
        if (i % (meshRes*2+1)==0) {
            circularElements[i] = 0;
        }else{
            row = i / (meshRes * 2 + 1);
            col = i % (meshRes * 2 + 1);
            if (col % 2 == 1) {
                circularElements[i] = (col+1)/2 + row * meshRes;
            }
            else {
                circularElements[i] = (col+1)/2 + ((row+1)%meshRes) * meshRes;
            }
        }
    }


#if 0
    // SOME SUGGESTED TEST CODE: Can be used to examine contents of your arrays
    printf("circularVerts:\n");
    for (int k = 0; k < numCircularVerts; k++) {
        printf("k =%3d:  pos = %7.4f, %7.4f, %7.4f. \n", k, circularVerts[3 * k], circularVerts[3 * k + 1], circularVerts[3 * k + 2]);
    }
    printf("circularElements:\n");
    for (int k = 0; k < numCircularElms; k++) {
        printf("%d, ", circularElements[k]);
    }
    printf("\n");
#endif

    glBindVertexArray(myVAO[iCircularSurf]);
    glBindBuffer(GL_ARRAY_BUFFER, myVBO[iCircularSurf]);
    glBufferData(GL_ARRAY_BUFFER, numCircularVerts*sizeof(float)*3, circularVerts, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, myEBO[iCircularSurf]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numCircularElms*sizeof(float)*3, circularElements, GL_STATIC_DRAW);

    delete[] circularVerts;
    delete[] circularElements;
}

// ****
// MyRenderFloor: To be written for Project 4. Renders the square ground plane.
//    This will loop, giving glDrawElements(...) commands. (Compare to RenderFloorDemo above.)
// ****
void MyRenderFloor()
{
    glBindVertexArray(myVAO[iFloor]);

    glVertexAttrib3f(vNormal_loc, 0.0, 1.0, 0.0);
    //glVertexAttrib3f(vColor_loc, 1.0f, 0.4f, 0.4f);
    myMaterials[0].LoadIntoShaders();
    viewMatrix.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    for (int i = 0; i < meshRes; i++) {
        glDrawElements(GL_TRIANGLE_STRIP, 2*(meshRes+1), GL_UNSIGNED_INT, (void*)(i*2*(meshRes+1)*sizeof(unsigned int)));                              
    }
    
 
}

// ****
// MyRenderCircularSurf: To be written for Project 4. Renders the circular surface.
//    This will loop, giving glDrawElements(...) commands. (Compare to RenderCircularDemo above.)
// ****
void MyRenderCircularSurf()
{
    glBindVertexArray(myVAO[iCircularSurf]);

    // Calculute the model view matrix for the circular surface
    LinearMapR4 matDemo = viewMatrix;
    matDemo.Mult_glTranslate(2.5, 1.0, 2.5);     // Center in the front right quadrant & raise up
    matDemo.Mult_glScale(0.3, 0.8, 0.3);         // Increase the circular diameter

    // Set the uniform values (they are not stored with the VAO and thus must be set again everytime
    //glVertexAttrib3f(vColor_loc, 1.0f, 0.8f, 0.4f);	 // Generic vertex attribute: Color (yellow-ish) for the circular surface. 
    myMaterials[1].LoadIntoShaders();
    matDemo.DumpByColumns(matEntries);
    glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);

    for (int i = 0; i < meshRes; i++) {
        glDrawElements(GL_TRIANGLE_STRIP, meshRes*2+1, GL_UNSIGNED_INT, (void*)((i*(meshRes*2+1))*sizeof(unsigned int)));
    }
}

