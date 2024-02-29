#define GLEW_STATIC
#include <GL/glew.h> 
#include <GLFW/glfw3.h>

#include "LinearR3.h"
#include "MathMisc.h"
#include "assert.h"

#include "GlGeomCube.h"

void GlGeomCube::CalVboAndEbo(float* VBOdataBuffer, unsigned int* EBOdataBuffer,
    int vertPosOffset, int vertNormalOffset, int vertTexCoordsOffset, unsigned int stride)
{

}

void GlGeomCube::InitializeAttribLocations(
    unsigned int pos_loc, unsigned int normal_loc, unsigned int texcoords_loc)
{
    // The call to GlGeomBase::InitializeAttribLocations will further call
    //   GlGeomSphere::CalcVboAndEbo()

    GlGeomBase::InitializeAttribLocations(pos_loc, normal_loc, texcoords_loc);
    VboEboLoaded = true;
}

void GlGeomCube::Render()
{
    GlGeomBase::Render();
}

