#include "lab_m1/tema2/tema2.h"
#include "lab_m1/tema2/transform3D.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;

/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


tema2::tema2()
{
}

tema2::~tema2()
{
}

    vector<VertexFormat> to_draw_trees;
    vector<VertexFormat> obstacle_1_road;
    vector<VertexFormat> obstacle_2_road;
    vector<VertexFormat> to_draw;



void tema2::Init()
{
    // renderCameraTarget = false;

    polygonMode = GL_FILL;

    camera = new implemented::Camera();
    camera_up = new implemented::Camera();

    cameraX = 0;
    cameraY = 1;
    cameraZ = 5;
    camera->Set(glm::vec3(cameraX, cameraY, cameraZ), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));


//    cout <<camera->GetTargetPosition();

    camera->RotateThirdPerson_OX(-0.5f);
    camera->TranslateUpward(-0.6f);
    camera->MoveForward(6.f);


    camera_up->RotateThirdPerson_OX(-0.5f);
    camera_up->TranslateUpward(-0.6f);
    camera_up->MoveForward(6.f);

    // camera->TranslateUpward(60);
    // camera->RotateThirdPerson_OX(-0.5f);
    // camera->RotateThirdPerson_OX(1.57f);

    // camera->RotateThirdPerson_OY( -0.7853981634f);

    // camera->TranslateUpward(-0.6f);
    // projectionMatrix = glm::ortho(fov, window->props.aspectRatio, zNear, zFar);
    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);



    // camera_up->MoveForward(3.6f);
    // camera_up->TranslateUpward(50);
    camera_up->RotateThirdPerson_OX(-1.37f);
    // camera_up->RotateThirdPerson_OX(-0.5f);
    // camera_up->RotateThirdPerson_OY( -0.7853981634f);

    // projectionMatrixUp = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);

    // projectionMatrixUp = glm::perspective(left, right, bottom, top, zNear, zFar);
    


    // camera->TranslateUpward(0.5);
    float cameraSpeed = 2.1f;
    camera->TranslateUpward(-cameraSpeed * 0.5f);

    camera->RotateFirstPerson_OX(0.001f * 200);




    // Initialize tx, ty and tz (the translation steps)
    translateX = 0;
    translateY = 0;
    translateZ = 0;

    angularStepOX = 0;
    angularStepOY = 0;
    angularStepOZ = 0;

    {
        Mesh *mesh = new Mesh("box");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("sphere");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "sphere.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // // grass

    const glm::vec3 GrassColor = NormalizedRGB(34, 171, 50);

    

    {
        vector<VertexFormat> vertices{
            VertexFormat(glm::vec3(-100, 0, 100) , GrassColor),
            VertexFormat(glm::vec3(-100, 0, -100), GrassColor),
            VertexFormat(glm::vec3(100, 0, -100), GrassColor), // red ,green ,blue
            VertexFormat(glm::vec3(100, 0, 100), GrassColor),
        };

        vector<unsigned int> indices{
            0, 1, 2, // indices for first triangle
            0, 2, 3,	// indices for second triangle
        };

        meshes["grass"] = new Mesh("generated grass");
        meshes["grass"]->InitFromData(vertices, indices);
        // Create a new mesh from buffer data
        Mesh *tetraedru2 = CreateMesh("grass", vertices, indices);
    }

    const glm::vec3 RoadColor = NormalizedRGB(54, 53, 52);


    vector<VertexFormat> main_dots{
        VertexFormat(glm::vec3(2, 0, 8),RoadColor),    // A
        VertexFormat(glm::vec3(6, 0, 12),RoadColor),   // B
        VertexFormat(glm::vec3(12, 0, 14),RoadColor),  // C
        VertexFormat(glm::vec3(18, 0, 12),RoadColor),  // D
        VertexFormat(glm::vec3(22, 0, 8),RoadColor),   // E
        VertexFormat(glm::vec3(24, 0, 2),RoadColor),  // F
        VertexFormat(glm::vec3(20, 0, -8),RoadColor),  // T
        VertexFormat(glm::vec3(14, 0, -10),RoadColor), // G
        VertexFormat(glm::vec3(8, 0, -5),RoadColor),   // H
        VertexFormat(glm::vec3(4, 0, -6),RoadColor),   // I
        VertexFormat(glm::vec3(-0, 0,-7),RoadColor),   // J
        VertexFormat(glm::vec3(-6, 0, -10),RoadColor),  // K
        VertexFormat(glm::vec3(-14, 0, -8),RoadColor), // L
        VertexFormat(glm::vec3(-20, 0, -2),RoadColor), // M
        VertexFormat(glm::vec3(-24, 0, 2),RoadColor),  // N
        VertexFormat(glm::vec3(-22, 0, 8),RoadColor),  // O
        VertexFormat(glm::vec3(-16, 0, 10),RoadColor), // P
        VertexFormat(glm::vec3(-10, 0, 8),RoadColor),  // Q
        VertexFormat(glm::vec3(-6, 0, 6),RoadColor),   // R
        VertexFormat(glm::vec3(-2, 0, 6),RoadColor),   // S
        VertexFormat(glm::vec3(2, 0, 8),RoadColor),    // A


        // VertexFormat(glm::vec3(9, 0, 7.5f),RoadColor), //A
        // VertexFormat(glm::vec3(20, 0, 15),RoadColor), //B
        // VertexFormat(glm::vec3(35, 0, 25),RoadColor), //C
        // VertexFormat(glm::vec3(45, 0, 20),RoadColor), //D
        // VertexFormat(glm::vec3(50, 0, 10),RoadColor), //E
        // VertexFormat(glm::vec3(25, 0, 22),RoadColor), //F
        // VertexFormat(glm::vec3(47, 0, 0),RoadColor), //G
        // VertexFormat(glm::vec3(40, 0, -5),RoadColor), //H
        // VertexFormat(glm::vec3(30, 0, -10),RoadColor), //I
        // VertexFormat(glm::vec3(15, 0, -5),RoadColor), //J
        // VertexFormat(glm::vec3(5, 0, -10),RoadColor), //K
        // VertexFormat(glm::vec3(-4.5, 0, -17),RoadColor), //L
        // VertexFormat(glm::vec3(-10, 0, -30),RoadColor), //M
        // VertexFormat(glm::vec3(-20, 0, -28),RoadColor), //N
        // VertexFormat(glm::vec3(-30, 0, -23),RoadColor), //O
        // VertexFormat(glm::vec3(-40, 0, -10),RoadColor), //P
        // VertexFormat(glm::vec3(-38, 0, 6),RoadColor), //Q
        // VertexFormat(glm::vec3(-25, 0, 20),RoadColor), //R
        // VertexFormat(glm::vec3(-17, 0, 15),RoadColor), //S
        // VertexFormat(glm::vec3(-5, 0, 5),RoadColor), //T
        // VertexFormat(glm::vec3(9, 0, 7.5f),RoadColor), //A




    };

    glm::vec3 direction = (glm::vec3(0, 0, 0));
    // glm::vec3 P = (glm::vec3(0, 0, 0));

    glm::vec3 UP = (glm::vec3(0, 1, 0));

    glm::vec3 R = (glm::vec3(0, 0, 0));
    glm::vec3 A = (glm::vec3(0, 0, 0));

    for (int i = 0; i != main_dots.size() - 1; ++i)
    {
        direction[0] = main_dots[i].position[0] - main_dots[i + 1].position[0];
        direction[2] = main_dots[i].position[2] - main_dots[i + 1].position[2];

        glm::vec3 P = glm::normalize(glm::cross(direction, UP));

        R[0] = main_dots[i].position[0] + 4.3f * P[0];
        R[2] = main_dots[i].position[2] + 4.3f * P[2];
        R[1]=0.04f;

        to_draw.push_back(VertexFormat(R,RoadColor));

        R[0] = main_dots[i].position[0] + 0.1f * P[0];
        R[2] = main_dots[i].position[2] + 0.1f * P[2];
        R[1]=0.04f;

        obstacle_1_road.push_back(R);

        A[0] = main_dots[i].position[0] - 4.5f * P[0];
        A[2] = main_dots[i].position[2] - 4.5f * P[2];
        A[1]=0.04f;

        to_draw.push_back(VertexFormat(A,RoadColor));

        A[0] = main_dots[i].position[0] - 7.7f * P[0];
        A[2] = main_dots[i].position[2] - 7.7f * P[2];
        A[1]=0.02f;
        to_draw_trees.push_back(A);



        A[0] = main_dots[i].position[0] - 2.1f * P[0];
        A[2] = main_dots[i].position[2] - 2.1f * P[2];
        A[1]=0.02f;
        obstacle_2_road.push_back(A);


    }

    to_draw.push_back(to_draw[0]);
    to_draw.push_back(to_draw[1]);

    // obstacle_1_road.push_back(obstacle_1_road[0]);
    // obstacle_1_road.push_back(obstacle_1_road[1]);



    obstacle_1_road.push_back(obstacle_1_road[0]);

    {
       
        vector<unsigned int> indices{
        1,2,3,
        2,3,4,
        3,4,5,
        4,5,6,
        5,6,7,
        6,7,8,
        7,8,9,
        8,9,10,
        9,10,11,
        10,11,12,
        11,12,13,
        12,13,14,
        13,14,15,
        14,15,16,
        15,16,17,
        16,17,18,
        17,18,19,
        18,19,20,
        19,20,21,
        20,21,22,
        21,22,23,
        22,23,24,
        23,24,25,
        24,25,26,
        25,26,27,
        26,27,28,
        27,28,29,
        28,29,30,
        29,30,31,
        30,31,32,
        31,32,33,
        32,33,34,
        33,34,35,
        34,35,36,
        35,36,37,
        36,37,38,
        37,38,39,
        1,2,39,
        2,38,39,
        };
        meshes["road"] = new Mesh("generated road");
        meshes["road"]->InitFromData(to_draw, indices);
        Mesh *road = CreateMesh("road", to_draw, indices);
    }

    

    //Create tree

    const glm::vec3 TrunckColor = NormalizedRGB(133, 64, 21);
    const glm::vec3 LeavesColor = NormalizedRGB(25, 209, 9);



    {
     vector<VertexFormat> tree{
        //trunck
            VertexFormat(glm::vec3(0.5f, 0, 0),TrunckColor), //B // x,y,z  //0
            VertexFormat(glm::vec3(0, 0, 0),TrunckColor), //A              //1
            VertexFormat(glm::vec3(0, 2, 0),TrunckColor), //D              //2
            VertexFormat(glm::vec3(0.5f, 2, 0),TrunckColor), //C           //3


            VertexFormat(glm::vec3(0.5f, 0, 0.5f),TrunckColor), //G           //4
            VertexFormat(glm::vec3(0.5f, 2, 0.5f),TrunckColor), //F           //5

            VertexFormat(glm::vec3(0, 2, 0.5f),TrunckColor), //E           //6
            VertexFormat(glm::vec3(0, 0, 0.5f),TrunckColor), //H           //7

        //leaves
            VertexFormat(glm::vec3(-1, 2, -1),LeavesColor), //A           //8
            VertexFormat(glm::vec3(1.5f, 2, -1),LeavesColor), //B          //9
            VertexFormat(glm::vec3(1.5f, 2, 1.5f),LeavesColor), //C           //10
            VertexFormat(glm::vec3(-1, 2, 1.5f),LeavesColor), //D           //11


                VertexFormat(glm::vec3(-1, 4, -1),LeavesColor), //E          //12
            VertexFormat(glm::vec3(1.5f, 4, -1),LeavesColor), //H          //13
            VertexFormat(glm::vec3(1.5f, 4, 1.5f),LeavesColor), //G           //14
            VertexFormat(glm::vec3(-1, 4, 1.5f),LeavesColor), //F         //15



        };

    vector<unsigned int> tree_indices{
        0,1,2,
        0,2,3, 
        0,3,5,
        0,4,5,
        1,2,7,
        2,6,7,
        7,6,4,
        6,5,4,

        8,12,13,
        13,8,9,
        13,10,9,
        13,14,10,
        10,11,15,
        10,15,14,
        15,12,11,
        8,12,11,
        15,13,12,
        15,13,14,

    };


        meshes["tree_mesh"] = new Mesh("generated tree_mesh");
        meshes["tree_mesh"]->InitFromData(tree, tree_indices);
        Mesh *tree_mesh = CreateMesh("tree_mesh", tree, tree_indices);
    }

    // Sets the resolution of the small viewport
    glm::ivec2 resolution = window->GetResolution();
    miniViewportArea = ViewportArea(50, 50, resolution.x / 5.f, resolution.y / 5.f);

    //    for (i=0 ; i <= obstacle_1_road.size()-1 ; i++){
    //             cout << obstacle_1_road[i].position[0] << "  ";
    //             cout << obstacle_1_road[i].position[2] << "  ";
    //             cout << "\n";
    //         }

}

Mesh *tema2::CreateMesh(const char *name, const std::vector<VertexFormat> &vertices, const std::vector<unsigned int> &indices)
{
    unsigned int VAO = 0;
    // TODO: Create the VAO and bind it
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // TODO: Create the VBO and bind it
    unsigned int VBO = 0;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    // TODO: Send vertices data into the VBO buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
    // TODO: Crete the IBO and bind it
    unsigned int IBO = 0;
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), &indices[0], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), 0);

    // set vertex normal attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void *)(sizeof(glm::vec3)));

    // set texture coordinate attribute
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void *)(2 * sizeof(glm::vec3)));

    // set vertex color attribute
    glEnableVertexAttribArray(3);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void *)(2 * sizeof(glm::vec3) + sizeof(glm::vec2)));
    // ========================================================================

    // TODO: Unbind the VAO
    glBindVertexArray(0);
    // Check for OpenGL errors
    CheckOpenGLError();

    // Mesh information is saved into a Mesh object
    meshes[name] = new Mesh(name);
    meshes[name]->InitFromBuffer(VAO, static_cast<unsigned short>(indices.size()));
    return meshes[name];
}

void tema2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer

    const glm::vec3 cloudColor = NormalizedRGB(18, 227, 220);
    
    glClearColor(0, 0.498039 , 1.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void tema2::Update(float deltaTimeSeconds)
{
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
 
    RenderScene();
    camera_up->Set(glm::vec3(camera->GetTargetPosition()), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

    projectionMatrixUp = glm::ortho(left, right, bottom, top, zNear, zFar);


    camera_up->RotateThirdPerson_OX(-1.57f);

    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);
    RenderSceneUp();
}

void tema2::RenderScene()
{
        // RenderMesh(meshes["tetrahedron1"], shaders["VertexColor"], modelX);
           glm::mat4 modelX = glm::mat4(1);
    RenderMesh(meshes["grass"], shaders["VertexColor"], modelX);
    RenderMesh(meshes["road"], shaders["VertexColor"], modelX);

    float tree_offset=0;

    for (int i = 0; i != to_draw_trees.size() - 1; ++i){
        glm::mat4 modelTree = glm::mat4(1);
        modelTree *= transform3D::Translate(to_draw_trees[i].position[0], 0, to_draw_trees[i].position[2]+tree_offset);
        RenderMesh(meshes["tree_mesh"], shaders["VertexColor"], modelTree);
    }


    
    // Render the camera target. This is useful for understanding where
    // the rotation point is, when moving in third-person camera mode.
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    modelMatrix *= transform3D::RotateOY(angularStepOY);

    // modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
    RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);


        if(i <= obstacle_1_road.size() - 1){
        // cout << "I= " << i << "\n";
        if(i==0)
        {
            // cout << "FIRST";
            modelObstacle1[3][0] = obstacle_1_road[i].position[0]; //X
            modelObstacle1[3][2] = obstacle_1_road[i].position[2]; //Z
            i++;
        }


            modelObstacle1[3][0] +=  ( obstacle_1_road[i].position[0] - obstacle_1_road[i-1].position[0] )/50;
 

            modelObstacle1[3][2] += (obstacle_1_road[i].position[2] - obstacle_1_road[i-1].position[2])/50;
        if(( obstacle_1_road[i].position[0] + 0.04f > modelObstacle1[3][0] &&  modelObstacle1[3][0] > obstacle_1_road[i].position[0] - 0.04f)  ||  (obstacle_1_road[i].position[2] + 0.04f > modelObstacle1[3][2]  && modelObstacle1[3][2] > obstacle_1_road[i].position[2] - 0.04f) ){
            // cout << "CHANGE!" << "\n";
            i++;
        }

    }
    else
    {
        i=0;
    }
            RenderMesh(meshes["sphere"], shaders["VertexColor"], modelObstacle1);




        if(j <= obstacle_2_road.size() - 1){
        // cout << "I= " << i << "\n";
        if(j==0)
        {
            // cout << "FIRST";
            modelObstacle2[3][0] = obstacle_2_road[j].position[0]; //X
            modelObstacle2[3][2] = obstacle_2_road[j].position[2]; //Z
            j++;
        }


            modelObstacle2[3][0] +=  ( obstacle_2_road[j].position[0] - obstacle_2_road[j-1].position[0] )/50;
 

            modelObstacle2[3][2] += (obstacle_2_road[j].position[2] - obstacle_2_road[j-1].position[2])/50;

        if(( obstacle_2_road[j].position[0] + 0.04f > modelObstacle2[3][0] &&  modelObstacle2[3][0] > obstacle_2_road[j].position[0] - 0.04f)  ||  (obstacle_2_road[j].position[2] + 0.04f > modelObstacle2[3][2]  && modelObstacle2[3][2] > obstacle_2_road[j].position[2] - 0.04f) ){
            // cout << "CHANGE!" << "\n";
            j++;
        }

    }
    else
    {
        j=0;
    }
            RenderMesh(meshes["sphere"], shaders["VertexColor"], modelObstacle2);

}



void tema2::RenderSceneUp()
{
    glm::mat4 modelX = glm::mat4(1);
    RenderMeshUp(meshes["grass"], shaders["VertexColor"], modelX);
    RenderMeshUp(meshes["road"], shaders["VertexColor"], modelX);

    float tree_offset=0;

    for (int i = 0; i != to_draw_trees.size() - 1; ++i){
        glm::mat4 modelTree = glm::mat4(1);
        modelTree *= transform3D::Translate(to_draw_trees[i].position[0], 0, to_draw_trees[i].position[2]+tree_offset);
        RenderMeshUp(meshes["tree_mesh"], shaders["VertexColor"], modelTree);
    }


    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::translate(modelMatrix, camera->GetTargetPosition());
    modelMatrix *= transform3D::RotateOY(angularStepOY);

    RenderMeshUp(meshes["box"], shaders["VertexNormal"], modelMatrix);

        if(i <= obstacle_1_road.size() - 1){
        if(i==0)
        {
            modelObstacle1[3][0] = obstacle_1_road[i].position[0]; //X
            modelObstacle1[3][2] = obstacle_1_road[i].position[2]; //Z
            i++;
        }


            modelObstacle1[3][0] +=  ( obstacle_1_road[i].position[0] - obstacle_1_road[i-1].position[0] )/50;
 

            modelObstacle1[3][2] += (obstacle_1_road[i].position[2] - obstacle_1_road[i-1].position[2])/50;
        if(( obstacle_1_road[i].position[0] + 0.04f > modelObstacle1[3][0] &&  modelObstacle1[3][0] > obstacle_1_road[i].position[0] - 0.04f)  ||  (obstacle_1_road[i].position[2] + 0.04f > modelObstacle1[3][2]  && modelObstacle1[3][2] > obstacle_1_road[i].position[2] - 0.04f) ){
            i++;
        }

    }
    else
    {
        i=0;
    }
            RenderMeshUp(meshes["sphere"], shaders["VertexColor"], modelObstacle1);
}

void tema2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}

void tema2::RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}


void tema2::RenderMeshUp(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix)
{
    if (!mesh || !shader || !shader->program)
        return;

    // Render an object using the specified shader and the specified position
    shader->Use();
    glUniformMatrix4fv(shader->loc_view_matrix, 1, GL_FALSE, glm::value_ptr(camera_up->GetViewMatrix()));
    glUniformMatrix4fv(shader->loc_projection_matrix, 1, GL_FALSE, glm::value_ptr(projectionMatrixUp));
    glUniformMatrix4fv(shader->loc_model_matrix, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    mesh->Render();
}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

float triangle_area(float Ax , float Ay , float Bx , float By ,float Cx , float Cy){
      float ABx , ABy , ACx , ACy;
      ABx = Bx - Ax;
      ABy = By - Ay;
      ACx = Cx - Ax;
      ACy = Cy - Ay;
      float cross;
      cross = ABx*ACy - ABy*ACx;
      return abs(cross/2);
}

void tema2::OnInputUpdate(float deltaTime, int mods)
{
    float cameraSpeed = 15.1f;

   

    if (window->KeyHold(GLFW_KEY_W))
    {
        camera->MoveForward(cameraSpeed * deltaTime);
        translateZ -= cameraSpeed * deltaTime;

        for(int i=0 ; i<= to_draw.size()-3;i++){

           float base = triangle_area(to_draw[i].position[0] , to_draw[i].position[2] , to_draw[i+1].position[0] , to_draw[i+1].position[2] , to_draw[i+2].position[0] , to_draw[i+2].position[2] ) ;

           float R1PA1 = triangle_area(to_draw[i].position[0] , to_draw[i].position[2] , camera->GetTargetPosition()[0] , camera->GetTargetPosition()[2] , to_draw[i+2].position[0] , to_draw[i+2].position[2] );
           float R2PA1 = triangle_area(to_draw[i].position[0] , to_draw[i].position[2] , to_draw[i+1].position[0] , to_draw[i+1].position[2] , camera->GetTargetPosition()[0] , camera->GetTargetPosition()[2] );
           float R1PR2 = triangle_area(camera->GetTargetPosition()[0] , camera->GetTargetPosition()[2] , to_draw[i+1].position[0] , to_draw[i+1].position[2] , to_draw[i+2].position[0] , to_draw[i+2].position[2] );

        float sum = R1PA1 + R2PA1 +R1PR2;
           if ( round(base) == round(sum) ){ 
              out = 0 ;
              break;
           }else
           {
            out=1;
           }
        }

        if(out == 1){
            camera->MoveForward(-cameraSpeed * deltaTime);
            translateZ -= cameraSpeed * deltaTime;
        }
    }
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;

    if (window->KeyHold(GLFW_KEY_S))
    {
      
        camera->MoveForward(-cameraSpeed * deltaTime);
        translateZ += cameraSpeed * deltaTime;

        for(int i=0 ; i<= to_draw.size()-3;i++){

           float base = triangle_area(to_draw[i].position[0] , to_draw[i].position[2] , to_draw[i+1].position[0] , to_draw[i+1].position[2] , to_draw[i+2].position[0] , to_draw[i+2].position[2] ) ;

           float R1PA1 = triangle_area(to_draw[i].position[0] , to_draw[i].position[2] , camera->GetTargetPosition()[0] , camera->GetTargetPosition()[2] , to_draw[i+2].position[0] , to_draw[i+2].position[2] );
           float R2PA1 = triangle_area(to_draw[i].position[0] , to_draw[i].position[2] , to_draw[i+1].position[0] , to_draw[i+1].position[2] , camera->GetTargetPosition()[0] , camera->GetTargetPosition()[2] );
           float R1PR2 = triangle_area(camera->GetTargetPosition()[0] , camera->GetTargetPosition()[2] , to_draw[i+1].position[0] , to_draw[i+1].position[2] , to_draw[i+2].position[0] , to_draw[i+2].position[2] );
  
        float sum = R1PA1 + R2PA1 +R1PR2;
           if ( round(base) == round(sum) ){ 
              out = 0 ;
              break;
           }else
           {
            out=1;
           }
        }

          if(out == 1){
        camera->MoveForward(cameraSpeed * deltaTime);
        translateZ += cameraSpeed * deltaTime;
        }

    }

    // if (window->KeyHold(GLFW_KEY_Q))
    // {
    //     camera->TranslateUpward(-cameraSpeed * deltaTime);
    // }

    // if (window->KeyHold(GLFW_KEY_E))
    // {
    //     camera->TranslateUpward(cameraSpeed * deltaTime);
    // }

    if (window->KeyHold(GLFW_KEY_A))
    {
        angularStepOY +=2* deltaTime;
        camera->RotateThirdPerson_OY(2*deltaTime);
    }
    if (window->KeyHold(GLFW_KEY_D))
    {
        angularStepOY -= 2*deltaTime;
        camera->RotateThirdPerson_OY(-2*deltaTime);
    }
}

void tema2::OnKeyPress(int key, int mods)
{
    // Add key press event
    if (key == GLFW_KEY_T)
    {
        renderCameraTarget = !renderCameraTarget;
    }
    // TODO(student): Switch projections
    if (key == GLFW_KEY_O)
    {
        projectionMatrix = glm::ortho(left, right, bottom, top, zNear, zFar);
    }

    if (key == GLFW_KEY_P)
    {
        projectionMatrix = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);
    }

    if (key == GLFW_KEY_SPACE)
    {
        switch (polygonMode)
        {
        case GL_POINT:
            polygonMode = GL_FILL;
            break;
        case GL_LINE:
            polygonMode = GL_POINT;
            break;
        default:
            polygonMode = GL_LINE;
            break;
        }
    }
}

void tema2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}

void tema2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event

    if (window->MouseHold(GLFW_MOUSE_BUTTON_RIGHT))
    {
        float sensivityOX = 0.001f;
        float sensivityOY = 0.001f;

        // cout << deltaY << "\n";

        if (window->GetSpecialKeyState() == 0)
        {
            renderCameraTarget = false;
            // TODO(student): Rotate the camera in first-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera->RotateFirstPerson_OY(-sensivityOY * deltaX);
            camera_up->RotateFirstPerson_OX(-sensivityOX * deltaY);
            camera_up->RotateFirstPerson_OY(-sensivityOY * deltaX);
        }

        if (window->GetSpecialKeyState() & GLFW_MOD_CONTROL)
        {
            renderCameraTarget = true;
            // TODO(student): Rotate the camera in third-person mode around
            // OX and OY using `deltaX` and `deltaY`. Use the sensitivity
            // variables for setting up the rotation speed.
            camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
            camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
            camera_up->RotateThirdPerson_OX(-sensivityOX * deltaY);
            camera_up->RotateThirdPerson_OY(-sensivityOY * deltaX);
        }
    }
}

void tema2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
}

void tema2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}

void tema2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}

void tema2::OnWindowResize(int width, int height)
{
}
