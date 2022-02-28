// Transform.cpp: implementation of the Transform class.

// Note: when you construct a matrix using mat4() or mat3(), it will be COLUMN-MAJOR
// Keep this in mind in readfile.cpp and display.cpp
// See FAQ for more details or if you're having problems.

#include "Transform.h"

// Helper rotation function.  Please implement this.  
mat3 Transform::rotate(const float degrees, const vec3& axis) 
{
    //mat3 ret;
    // YOUR CODE FOR HW2 HERE
    // Please implement this.  Likely the same as in HW 1. 
    vec3 k = glm::normalize(axis);
    mat3 I = glm::mat3(1, 0, 0, 0, 1, 0, 0, 0, 1);
    //vec3 tranA = glm::transpose(&k);
    //vec3 AtranA = k*tranA;
    mat3 AtranA = glm::mat3(k[0] * k[0], k[0] * k[1], k[0] * k[2],
        k[0] * k[1], k[1] * k[1], k[1] * k[2],
        k[0] * k[2], k[1] * k[2], k[2] * k[2]);

    mat3 Astar = glm::mat3(0, k[2], -k[1],
        -k[2], 0, k[0],
        k[1], -k[0], 0);
    mat3 R = glm::mat3();
    R = float(cos(degrees * pi / 180)) * I + float((1 - cos(degrees * pi / 180))) * AtranA + float(sin(degrees * pi / 180)) * Astar;
    // You will change this return call
    return R;
    //return ret;
}

void Transform::left(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    eye = Transform::rotate(degrees, up) * eye;
}

void Transform::up(float degrees, vec3& eye, vec3& up) 
{
    // YOUR CODE FOR HW2 HERE 
    // Likely the same as in HW 1.  
    vec3 right = glm::cross(eye, up);
    eye = Transform::rotate(degrees, right) * eye;
    up = Transform::rotate(degrees, right) * up;
}

mat4 Transform::lookAt(const vec3 &eye, const vec3 &center, const vec3 &up) 
{
    //mat4 ret;
    // YOUR CODE FOR HW2 HERE
    // Likely the same as in HW 1.  
    //return ret;
    vec3 w = glm::normalize(eye);
    vec3 u = glm::normalize(glm::cross(up, w));
    vec3 v = glm::cross(w, u);
    mat4 camera(1.0f);
    camera[0] = glm::vec4(1, 0, 0, 0);
    camera[1] = glm::vec4(0, 1, 0, 0);
    camera[2] = glm::vec4(0, 0, 1, 0);
    camera[3] = glm::vec4(-eye[0], -eye[1], -eye[2], 1);

    mat4 world(1.0f);
    world[0] = glm::vec4(u[0], v[0], w[0], 0);
    world[1] = glm::vec4(u[1], v[1], w[1], 0);
    world[2] = glm::vec4(u[2], v[2], w[2], 0);
    world[3] = glm::vec4(0, 0, 0, 1);

    // You will change this return call
    return world * camera;
    //return glm::lookAt(eye,center,up);
}

mat4 Transform::perspective(float fovy, float aspect, float zNear, float zFar)
{
    mat4 pers;
    // YOUR CODE FOR HW2 HERE
    // New, to implement the perspective transform as well.  
    float fovyInRad = (fovy * pi) / 180;
    pers[0] = glm::vec4(float(1/(aspect*tan(fovyInRad/2))), 0,0,0);
    pers[1] = glm::vec4(0, float(1/(tan(fovyInRad/2))), 0, 0);
    pers[2] = glm::vec4(0,0,float(-(zFar+zNear)/(zNear-zFar)), -1);
    pers[3] = glm::vec4(0, 0, float(2 * zFar * zNear / (zFar - zNear)), 0);
    return pers;
    //return glm::perspective(fovy, aspect, zNear, zFar);
}

mat4 Transform::scale(const float &sx, const float &sy, const float &sz) 
{
    mat4 sca;
    // YOUR CODE FOR HW2 HERE
    // Implement scaling 
    sca[0] = glm::vec4(sx, 0, 0, 0);
    sca[1] = glm::vec4(0,sy,0,0);
    sca[2] = glm::vec4(0, 0, sz, 0);
    sca[3] = glm::vec4(0,0,0,1);
    return sca;
}

mat4 Transform::translate(const float &tx, const float &ty, const float &tz) 
{
    mat4 tran;
    // YOUR CODE FOR HW2 HERE
    // Implement translation 
    tran[0] = glm::vec4(1,0,0,0);
    tran[1] = glm::vec4(0,1,0,0);
    tran[2] = glm::vec4(0,0,1,0);
    tran[3] = glm::vec4(tx,ty,tz,1);
    return tran;
}

// To normalize the up direction and construct a coordinate frame.  
// As discussed in the lecture.  May be relevant to create a properly 
// orthogonal and normalized up. 
// This function is provided as a helper, in case you want to use it. 
// Using this function (in readfile.cpp or display.cpp) is optional.  

vec3 Transform::upvector(const vec3 &up, const vec3 & zvec) 
{
    vec3 x = glm::cross(up,zvec); 
    vec3 y = glm::cross(zvec,x); 
    vec3 ret = glm::normalize(y); 
    return ret; 
}


Transform::Transform()
{

}

Transform::~Transform()
{

}
