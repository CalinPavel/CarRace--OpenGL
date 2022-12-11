#pragma once

#include "components/simple_scene.h"
#include "lab_m1/tema2/camera.h"
#include <vector>
#include <string>
#include <iostream>

namespace m1
{
    class tema2 : public gfxc::SimpleScene
    {
    public:
        struct ViewportArea
        {
            ViewportArea() : x(0), y(0), width(1), height(1) {}
            ViewportArea(int x, int y, int width, int height)
                : x(x), y(y), width(width), height(height) {}
            int x;
            int y;
            int width;
            int height;
        };

        tema2();
        ~tema2();

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix) override;
        void RenderMeshUp(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix);


        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void RenderScene();
        void RenderSceneUp();



		Mesh* CreateMesh(const char *name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned int>& indices);


    protected:
        glm::mat4 modelMatrix , modelX , modelCameraUp;
        glm::mat4 modelGrassUp , modelRoadUp , modelCubeUp , modelTreeUp;

        glm::mat4 modelObstacle2 = glm::mat4(1);
        glm::mat4 modelObstacle1 = glm::mat4(1);

        bool go=1;
        int k=4;


        float translateX, translateY, translateZ;
        float cameraX, cameraY, cameraZ;

        float scaleX, scaleY, scaleZ;
        float angularStepOX, angularStepOY, angularStepOZ;
        GLenum polygonMode;
        ViewportArea miniViewportArea;
        

        // glm::mat4 modelTree1,modelTree2,modelTree3,modelTree4,modelTree5,modelTree6,modelTree7,modelTree8,modelTree9,modelTree10,modelTree11,modelTree12;

    protected:
        implemented::Camera *camera;
        implemented::Camera *camera_up;
        glm::mat4 projectionMatrix;
        glm::mat4 projectionMatrixUp;

        bool renderCameraTarget;

        float fov = 3.14f/4;
        float left = -20, right = 10, bottom = -10, top = 10, zNear = 0.1f, zFar = 100;
        float i=0;
        float count_x = 0;
        float count_y = 0;
        float keeptime=0;

          float countX=0,countY=0;

        // vector<VertexFormat> to_draw;

    };
}