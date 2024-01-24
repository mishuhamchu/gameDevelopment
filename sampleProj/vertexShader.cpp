
#include "glad.h"
#include <GLFW/glfw3.h>
#include <iostream>


//VERTEX SHADERS PROVIDE US A 1::1 mapping such that the the verticies are translated
// to verticies the computer will be using

//fragments are the data that will be put onto the rendered pixels
//fragments can have multiple attributes to describe the rendered data
using namespace std;

// vertex shader source code
char *vsSrc =
    "#version 330 core\n                                    \
 layout (location = 0) in vec3 inPosition;              \
 void main()                                            \    
 {                                                      \
    gl_Position = vec4(inPosition, 1.0);                \
 }";
// fragment shader source code
char *fsSrc =
    "#version 330 core\n                                    \
 out vec4 fragColor;                                    \
 void main()                                            \    
 {                                                      \
    fragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);           \
 }";

// object id variables
unsigned int pId;
unsigned int vertexShaderId;
unsigned int fragmentShaderId;
unsigned int vertexBuffer;
unsigned int vertexArray;

// vertex of points

float vertices[] = {
    -0.8f, -0.6f, 0.0f,
    0.3f, -0.4f, 0.0f,
    0.0f, 0.2f, 0.0f};

int main(int argc, char **argv)
{
    // initialize GLFW
    if (!glfwInit())
    {
        return -1;
    }

    // create a window pointer
    GLFWwindow *window = glfwCreateWindow(800, 600, "Hello Triangle", NULL, NULL);
    // error check
    if (window == NULL)
    {
        cout << "Error. I could not create a window at all!" << endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    // create program object
    pId = glCreateProgram();

    // create shaders
   
   //provide the type of shader we want to create as an arugment to glCreateShader;
    //a new vertex shader will be assigned GL_VERTEX_SHADER

   vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
    
    //takes the sahder object to compile as first argument, second argument specifies how many strings
    //the third is the actual soruce code of the vertex ahder

    glShaderSource(vertexShaderId, 1, &vsSrc, NULL);
    glCompileShader(vertexShaderId);

    //HERE WE HAVE TRANSLATED THE SHADER CODE | the coordinates map to coordinates we can use

    fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShaderId, 1, &fsSrc, NULL);
    glCompileShader(fragmentShaderId);

    // attachment of shaders to program object
    glAttachShader(pId, vertexShaderId);
    glAttachShader(pId, fragmentShaderId);
    
    //here we are linking the data together
    glLinkProgram(pId);

    // buffer
    glGenVertexArrays(1, &vertexArray);
    glGenBuffers(1, &vertexBuffer);
    
    //array
    //all subsequent calls will be stored inside the VAO

    /*go vver page 35*/
    glBindVertexArray(vertexArray);

    /*vertex array stores the folllowing:
    1)calls to glEnableVertexAttriv Array
    2)Vertex attribute configureations via glVertexAttrivPointer
    3)Vertex buffwe object associated with vertex attrivutes by calls to glVertexAttribPointer
    */
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
    /*
    the vertex shader allows us to specigy any input we want in the form of vertex attributes
    it does mean we have to manualy speciy what part of our input data goes to which vertex
    attribute in the vertex shader

    so given a buffer B, B = {V1,v2,v3} | v contains (x,y,z) | x contains 4 bytes of data

    */

    //first paramter specifes which vertrex attribute we want to configure; above we said 0
    //second paramter specifies the size of the vertex attirbute
    //thrid specifes type of data
    //fourth specifeiss if we want the data to be normaized
    //5th specifies space between balues
    //6th specifies where the data begins
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);

    //mpw we are enabling the attribute at locatin 0
    glEnableVertexAttribArray(0);

    while (!glfwWindowShouldClose(window))
    {
        glClearColor(0.0f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
	
	//here it will use the fragment and shader data
	//we now have a program P | the fragment vertex data describe how the coordinates should be used

        glUseProgram(pId);

        glBindVertexArray(vertexArray);
	
	//here we are drawing what we want
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}



/*Element buffer objects can be used to make rendering overlaping indicies simpler*/
float verticies [] = {
    0.5f, 0.5f, 0.0f,//top right
     0.5f, 0.5f, 0.0f,//bottom right
     0.5f, 0.5f, 0.0f,//bottom left
    -0.5f,0.5f,0.0f //top left

};
unsigned int indicies [] = {
    0,1,3,
    1,2,3
}
glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicies), indicies, GL_STATIC_DRAW);
glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



