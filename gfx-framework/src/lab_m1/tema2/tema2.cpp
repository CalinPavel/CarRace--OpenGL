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
    camera_up->Set(glm::vec3(cameraX, cameraY, cameraZ), glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));

//    cout <<camera->GetTargetPosition();

    camera->RotateThirdPerson_OX(-0.5f);
    camera->TranslateUpward(-0.6f);
    camera->MoveForward(6.f);

    // camera->TranslateUpward(60);
    // camera->RotateThirdPerson_OX(-0.5f);
    // camera->RotateThirdPerson_OX(1.57f);

    // camera->RotateThirdPerson_OY( -0.7853981634f);

    // camera->TranslateUpward(-0.6f);
    // projectionMatrix = glm::ortho(fov, window->props.aspectRatio, zNear, zFar);
    projectionMatrix = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);



    // camera_up->MoveForward(3.6f);
    // camera_up->TranslateUpward(50);
    // camera_up->RotateThirdPerson_OX(1.57f);
    // camera_up->RotateThirdPerson_OX(-0.5f);
    // camera_up->RotateThirdPerson_OY( -0.7853981634f);

    // projectionMatrixUp = glm::ortho(left, right, bottom, top, zNear, zFar);
    projectionMatrixUp = glm::perspective(fov, window->props.aspectRatio, zNear, zFar);

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

    // TODO(student): After you implement the changing of the projection
    // parameters, remove hardcodings of these parameters
    // fov=RADIANS(60);
    // projectionMatrix = glm::perspective(fov, window->props.aspectRatio, 0.01f, 300.0f);

    // // camera->RotateThirdPerson_OX(RADIANS(45));
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

    // road
    // glm::vec3 p1 = (glm::vec3(3, 0, 6));
    // glm::vec3 p2 = (glm::vec3(2, 0, 3));
    // glm::vec3 d = (glm::vec3(0, 0, 0));

    // d[0] = p1[0] - p2[0];
    // d[1] = p1[1] - p2[1];
    // d[2] = p1[2] - p2[2];

    // glm::vec3 up = (glm::vec3(0, 1, 0));
    // glm::vec3 P = glm::normalize(glm::cross(d, up));

    // P[0] = 2 * P[0];
    // P[2] = 2 * P[2];
    // glm::vec3 R = p1 + P;

    // glm::vec3 A = p1 - P;
    // P[0] = P[0] / 2;
    // P[2] = P[2] / 2;

    // cout << d[0] << "\n";
    // cout << d[1] << "\n";
    // cout << d[2] << "\n";

    // {
    //     vector<VertexFormat> vertices{
    //         VertexFormat(glm::vec3(3, 0, 3)),
    //         VertexFormat(glm::vec3(2, 0, 0)),
    //         VertexFormat(glm::vec3(1, 0, 3)), // red ,green ,blue
    //         // VertexFormat(glm::vec3(-1, 1, 0)),
    //     };

    //     vector<unsigned int> indices{
    //         0, 1, 2, // indices for first triangle
    //                  // 1, 0, 3,	// indices for second triangle
    //     };

    //     meshes["tetrahedron1"] = new Mesh("generated tetrahedron 1");
    //     meshes["tetrahedron1"]->InitFromData(vertices, indices);
    //     // Create a new mesh from buffer data
    //     Mesh *tetraedru2 = CreateMesh("tetrahedron2", vertices, indices);
    // }

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
    vector<VertexFormat> to_draw;

    glm::vec3 direction = (glm::vec3(0, 0, 0));
    // glm::vec3 P = (glm::vec3(0, 0, 0));

    glm::vec3 UP = (glm::vec3(0, 1, 0));

    glm::vec3 R = (glm::vec3(0, 0, 0));
    glm::vec3 A = (glm::vec3(0, 0, 0));

    for (int i = 0; i != main_dots.size() - 1; ++i)
    {
        // cout<<main_dots[i].position[0] << " ";
        // cout<<main_dots[i].position[2]<< "\n";

        // d[0] = p1[0] - p2[0];
        // d[1] = p1[1] - p2[1];
        // d[2] = p1[2] - p2[2];

        direction[0] = main_dots[i].position[0] - main_dots[i + 1].position[0];
        direction[2] = main_dots[i].position[2] - main_dots[i + 1].position[2];

        glm::vec3 P = glm::normalize(glm::cross(direction, UP));

        R[0] = main_dots[i].position[0] + 3.3f * P[0];
        R[2] = main_dots[i].position[2] + 3.3f * P[2];
        R[1]=0.04f;

        to_draw.push_back(VertexFormat(R,RoadColor));

        R[0] = main_dots[i].position[0] + 1.3f * P[0];
        R[2] = main_dots[i].position[2] + 1.3f * P[2];
        R[1]=0.04f;

        obstacle_1_road.push_back(R);

        A[0] = main_dots[i].position[0] - 3.5f * P[0];
        A[2] = main_dots[i].position[2] - 3.5f * P[2];
        A[1]=0.04f;

        to_draw.push_back(VertexFormat(A,RoadColor));

        A[0] = main_dots[i].position[0] - 5.6f * P[0];
        A[2] = main_dots[i].position[2] - 5.6f * P[2];
        A[1]=0.02f;
        to_draw_trees.push_back(A);



        A[0] = main_dots[i].position[0] - 2.1f * P[0];
        A[2] = main_dots[i].position[2] - 2.1f * P[2];
        A[1]=0.02f;
        obstacle_2_road.push_back(A);

        //    A = main_dots[i] + P;
        // to_draw.push_back(direction);
    }



    // for (int i = 0; i < 100; i++)
    // {
    //     cout << i << ","<<i+1<< "," << i+2 << "," << "\n";
    // }
    


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
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void tema2::Update(float deltaTimeSeconds)
{
    glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
    // glm::mat4 modelMatrix = glm::mat4(1);
    glm::mat4 modelX = glm::mat4(1);
    // RenderMesh(meshes["tetrahedron1"], shaders["VertexColor"], modelX);
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

    



    //obstacle_1
    glm::mat4 modelObstacle1 = glm::mat4(1);

    // for (int i = 0; i != obstacle_1_road.size() - 1; ++i){
    //     glm::mat4 modelObstacle1 = glm::mat4(1);
    //     modelObstacle1 *= transform3D::Translate(obstacle_1_road[i].position[0], 0, obstacle_1_road[i].position[2]);
    //     modelObstacle1 = glm::scale(modelObstacle1, glm::vec3(0.6f));
    //     RenderMesh(meshes["box"], shaders["VertexColor"], modelObstacle1);
    // }
    

    // if(i <= obstacle_1_road.size() - 1){
    //     glm::mat4 modelObstacle1 = glm::mat4(1);
    //     modelObstacle1 *= transform3D::Translate(obstacle_1_road[i].position[0], 0, obstacle_1_road[i].position[2]);
    //     modelObstacle1 = glm::scale(modelObstacle1, glm::vec3(0.6f));
    //     RenderMesh(meshes["box"], shaders["VertexColor"], modelObstacle1);
    //     if(i == obstacle_1_road.size() - 1){
    //         i=0;
    //     }
    // }

    // cout<< i << "\n";
    
    // keeptime += deltaTimeSeconds;
    // if(keeptime > 1 ){
    //     keeptime=0;
    if(i <= obstacle_1_road.size() - 1){

        if(i==0)
        {
            modelObstacle1 *= transform3D::Translate(obstacle_1_road[i].position[0], 0,obstacle_1_road[i].position[2]);
            // RenderMesh(meshes["box"], shaders["VertexColor"], modelObstacle1);
            count_x = obstacle_1_road[i].position[0];
            count_y = obstacle_1_road[i].position[2];
            i++;
            count_x= obstacle_1_road[i].position[0] -obstacle_1_road[i].position[0]/300 *299 ;
            count_y= obstacle_1_road[i].position[2] -obstacle_1_road[i].position[2]/300 *299 ;
        }

        float to_add_x , to_add_y;
        to_add_x = obstacle_1_road[i].position[0]/300;
        to_add_y = obstacle_1_road[i].position[2]/300;

        // cout << count_x << "\n";
        //aici sa fac cazurile de obstacle negativ /pozitiv
        if(count_x > obstacle_1_road[i].position[0] || count_y > obstacle_1_road[i].position[2] )
        {
            count_x=obstacle_1_road[i].position[0];
            count_y=obstacle_1_road[i].position[2];
            modelObstacle1 *= transform3D::Translate(count_x, 0, count_y);

            i++;
            count_x= obstacle_1_road[i].position[0] -obstacle_1_road[i].position[0]/300 *299 ;
            count_y= obstacle_1_road[i].position[2] -obstacle_1_road[i].position[2]/300 *299 ;
            cout<<"next value"<<"\n";
        }
        else
        {
            cout<<"Add to value" << " " << count_x << " " << "To reach" << obstacle_1_road[i].position[0] <<"\n";
            if(obstacle_1_road[i].position[0] < 0){
                count_x -=to_add_x;
            }else{
                count_x +=to_add_x;
            }

            if(obstacle_1_road[i].position[2] < 0){
                count_y -=to_add_y;
            }else{
                count_y +=to_add_y;
            }
            modelObstacle1 *= transform3D::Translate(count_x, 0, count_y);
            
           
        }
    }else{
        i=0;
    }
    // }

            RenderMesh(meshes["box"], shaders["VertexColor"], modelObstacle1);

    

    // cout << deltaTimeSeconds << "\n";


    //Viewport
    glClear(GL_DEPTH_BUFFER_BIT);
    glViewport(miniViewportArea.x, miniViewportArea.y, miniViewportArea.width, miniViewportArea.height);


}

void tema2::RenderScene()
{
    modelMatrix = glm::mat4(1);
    // modelMatrix *= transform3D::Translate(2.5f, 0.5f, -1.5f);
    // modelMatrix *= transform3D::RotateOX(angularStepOX);
    // modelMatrix *= transform3D::RotateOY(angularStepOY);
    // modelMatrix *= transform3D::RotateOZ(angularStepOZ);
    // RenderMesh(meshes["box"], shaders["VertexNormal"], modelMatrix);
}

void tema2::FrameEnd()
{
    // DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
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

void tema2::OnInputUpdate(float deltaTime, int mods)
{
    // move the camera only if MOUSE_RIGHT button is pressed

    float cameraSpeed = 15.1f;

    if (window->KeyHold(GLFW_KEY_W))
    {
        camera->MoveForward(cameraSpeed * deltaTime);
        camera_up->MoveForward(cameraSpeed * deltaTime);

        translateZ -= cameraSpeed * deltaTime;
    }
    float sensivityOX = 0.001f;
    float sensivityOY = 0.001f;

    if (window->KeyHold(GLFW_KEY_S))
    {
        // TODO(student): Translate the camera backward
        // camera->TranslateForward(-cameraSpeed * deltaTime);
        camera->MoveForward(-cameraSpeed * deltaTime);
        camera_up->MoveForward(-cameraSpeed * deltaTime);

        translateZ += cameraSpeed * deltaTime;
    }

    if (window->KeyHold(GLFW_KEY_Q))
    {
        // TODO(student): Translate the camera downward
        camera->TranslateUpward(-cameraSpeed * deltaTime);
        
    }

    if (window->KeyHold(GLFW_KEY_E))
    {
        // TODO(student): Translate the camera upward
        camera->TranslateUpward(cameraSpeed * deltaTime);
    }
    ////////////////////////////////////////////////////

    // TODO(student): Change projection parameters. Declare any extra
    // variables you might need in the class header. Inspect this file
    // for any hardcoded projection arguments (can you find any?) and
    // replace them with those extra variables.

    if (window->KeyHold(GLFW_KEY_A))
    {
        angularStepOY +=2* deltaTime;
        camera->RotateThirdPerson_OY(2*deltaTime);
        camera_up->RotateThirdPerson_OY(2*deltaTime);

    }
    if (window->KeyHold(GLFW_KEY_D))
    {
        angularStepOY -= 2*deltaTime;
        camera->RotateThirdPerson_OY(-2*deltaTime);
        camera_up->RotateThirdPerson_OY(-2*deltaTime);

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
