// ************************
// PhongData.cpp (Demo)
// ************************

// Use the static library (so glew32.dll is not needed):
#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "PhongData.h"
#include "EduPhong.h"
#include "LinearR4.h"
#include "GlGeomSphere.h"
extern GlGeomSphere unitSphere; // Defined in MyInitial.cpp
extern unsigned int modelviewMatLocation;

extern phGlobal globalPhongData;

extern bool UseHalfwayVector;
extern bool UseSchlickFresnel;

// You should use at least three materis.
// It is suggested to use
//     myMaterial[0] for the ground plane
//     myMaterial[1] for the surface of rotation
//     myMaterial[2], myMaterial[3], etc. for your initial
//     Make the array bigger if you use more than four materials.
phMaterial myMaterials[4];

// There are four lights.
// They are enabled/disabled by PhongProj.cpp code (already written)
// myLights[0], myLights[1], myLights[2] are the three lights above the scene.
// myLights[3] is the spotlight.
phLight myLights[4];

phMaterial myEmissiveMaterials;   // Use for small spheres showing the location of the lights.

// Suggested positions for the lights. It is OK to change them if it fits in your scene better.
// Especially, you may need to move them higher or lower!
VectorR3 myLightPositions[3] = {
    VectorR3(-5.0, 7.0, 0.0),
    VectorR3(0.0, 7.0, 0.0),
    VectorR3(5.0, 7.0, 0.0),
};

// You most likely to do not want to change MySetupGlobalLight
void MySetupGlobalLight()
{
    globalPhongData.NumLights = 4;     // Should be enough lights for the programming project #5

    // FEEL FREE TO CHANGE THIS VALUE IF IT HELPS YOUR SCENE LOOK BETTER (E.G. IN LOW LIGHT)
    globalPhongData.GlobalAmbientColor.Set(0.1, 0.1, 0.1);
    globalPhongData.UseHalfwayVector = UseHalfwayVector;
    globalPhongData.LoadIntoShaders();
}

// Gets called a lot since Position needs updating each time view changes.
void MySetupLights()
{
    // First light (light #0).
    myLights[0].AmbientColor.Set(0.3, 0.3, 0.3);    // Gray color
    myLights[0].DiffuseColor.Set(0.4,0.4,0.4);      // Brighter gray
    myLights[0].SpecularColor.Set(0.4, 0.4, 0.4);   // Very bright gray
    myLights[0].IsEnabled = true;                   // BE SURE TO ENABLE EACH LIGHT

    // SET UP LIGHTS #1 and #2 and #3 BELOW.
    // CODE IS SIMILAR TO ABOVE!
    // LIGHT #3 should be a spotlight.
    myLights[1].AmbientColor.Set(0.1,0.1,0.2);    
    myLights[1].DiffuseColor.Set(0.2, 0.2, 0.4);    
    myLights[1].SpecularColor.Set(0.2, 0.2, 0.2);   
    myLights[1].IsEnabled = true;                  

    myLights[2].AmbientColor.Set(0.1,0.2,0.1);    
    myLights[2].DiffuseColor.Set(0.2, 0.4, 0.2);     
    myLights[2].SpecularColor.Set(0.3, 0.3, 0.3);  
    myLights[2].IsEnabled = true;          
    
    myLights[3].AmbientColor.Set(0.4, 0.4, 0.4);
    myLights[3].DiffuseColor.Set(0.7, 0.7, 0.7);
    myLights[3].SpecularColor.Set(0.8, 0.8, 0.8);
    myLights[3].IsSpotLight = true;
    myLights[3].SpotCosCutoff = 0.95f;
    myLights[3].SpotExponent = 0.0f;
    myLights[3].IsEnabled = true;

}


//  This has to be called every time the view matrix is changed.
//  This is because uses the viewMatrix computed in PhongProj.cpp.
//  It is also called whenever a light is enabled or disabled.
void LoadAllLights() 
{
    myLights[0].SetPosition(viewMatrix, myLightPositions[0]);
    myLights[0].LoadIntoShaders(0); 

    myLights[1].SetPosition(viewMatrix, myLightPositions[1]);
    myLights[1].LoadIntoShaders(1);  

    myLights[2].SetPosition(viewMatrix, myLightPositions[2]);
    myLights[2].LoadIntoShaders(2);  

    // Load myLights[3] with a position and spot direction
    myLights[3].SetPosition(viewMatrix, VectorR3(-2.0, 6.0, -2.0));
    myLights[3].SetSpotlightDirection(viewMatrix, VectorR3(0.0, -1.0, 0.0));
    myLights[3].LoadIntoShaders(3);
}

// *******************************************
// In this routine, you must set the material properties for your three or four or more surfaces.
// Make the Emissive Color values ALL EQUAL TO ZERO.
// It is suggested that Ambient and Diffuse colors for a material are equal to each other, 
//         or at least are scalar multiples of each other.
// It is suggested that the Specular Color is a white or gray.
//
// This routine is setup during initialization
// It is also called when the Schlick-Fresnel mode is enabled or disabled (Variable name: UseSchlickFresel)
// Completely optional: If you program animates material colors, call this every render cycle
//     to update the material colors.
// *******************************************

void MySetupMaterials()
{
    
    // myMaterials[0]: Material for the ground plane
    myMaterials[0].EmissiveColor.Set(0.0,0.0,0.0);   // THIS SHOULD CHANGE TO 0,0,0 SO IT HAS NO EMISSION
    myMaterials[0].AmbientColor.Set(0.4f, 0.1f, 0.1f);
    myMaterials[0].DiffuseColor.Set(0.8f, 0.2f, 0.2f);
    myMaterials[0].SpecularColor.Set(0.3f, 0.3f, 0.3f);
    myMaterials[0].SpecularExponent = 10.0;

    // myMaterials[1]: Material for the surface of rotation
    myMaterials[1].EmissiveColor.Set(0.0, 0.0, 0.0);;  // THIS SHOULD CHANGE TO 0,0,0  SO IT HAS NO EMISSION
    myMaterials[1].AmbientColor.Set(0.5f, 0.4f, 0.2f);
    myMaterials[1].DiffuseColor.Set(1.0f, 0.8f, 0.4f);
    myMaterials[1].SpecularColor.Set(0.2, 0.2, 0.2);
    myMaterials[1].SpecularExponent = 30.0;
    myMaterials[1].UseFresnel = UseSchlickFresnel;      // Use Schlick-Fresnel (when enabled on the surface of rotation.

    // myMaterials[2]: First Material for the initial
    myMaterials[2].EmissiveColor.Set(0.0, 0.0, 0.0);;  // THIS SHOULD CHANGE TO 0,0,0 SO IT HAS NO EMISSION
    myMaterials[2].AmbientColor.Set(0.25f, 0.10f, 0.07f);
    myMaterials[2].DiffuseColor.Set(0.75f, 0.60f, 0.21f);
    myMaterials[2].SpecularColor.Set(0.55f, 0.55f, 0.55f);
    myMaterials[2].SpecularExponent = 20.0;

    // myMaterials[3]: Second Material for the initial
    myMaterials[3].EmissiveColor.Set(0.0, 0.0, 0.0); ;// THIS SHOULD CHANGE TO 0,0,0 SO IT HAS NO EMISSION
    myMaterials[3].AmbientColor.Set(0.1f, 0.18f, 0.17f);
    myMaterials[3].DiffuseColor.Set(0.4f, 0.75f, 0.7f);
    myMaterials[3].SpecularColor.Set(0.3, 0.3, 0.3);
    myMaterials[3].SpecularExponent = 0.0;

}

// Purely emissive spheres showing placement of the light[0]
// Use the light's diffuse color as the emissive color
// Use the light's position as the sphere's position
void MyRenderSpheresForLights() {
   float matEntries[16];	// Holds 16 floats (since cannot load doubles into a shader that uses floats)
   phMaterial myEmissiveMaterial;

   for (int i = 0; i < 3; i++) {
        if (myLights[i].IsEnabled) {
            LinearMapR4 modelviewMat = viewMatrix;
            modelviewMat.Mult_glTranslate(myLightPositions[i]);
            modelviewMat.Mult_glScale(0.2);
            modelviewMat.DumpByColumns(matEntries);
            glUniformMatrix4fv(modelviewMatLocation, 1, false, matEntries);
            myEmissiveMaterial.EmissiveColor = myLights[i].DiffuseColor;
            myEmissiveMaterial.LoadIntoShaders();
            unitSphere.Render();
        }
    }
}
