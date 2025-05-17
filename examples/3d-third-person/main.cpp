// loopxia-engine.cpp : Defines the entry point for the application.
//

#include "loopxia/loopxia.h"
#include <iostream>

using namespace std;
using namespace loopxia;

std::shared_ptr<Mesh> g_pCharacterMesh;
MeshRenderer* meshRenderer;

Camera* g_camera;

int g_characterMeshId = 0;

void render()
{
    auto projection = g_camera->GetProjectionMatrix();
    auto view = g_camera->GetViewMatrix();

    meshRenderer->BeginRender();
    //meshRenderer->Render(g_characterMeshId, projection * view);
    meshRenderer->EndRender();
}


int main()
{
    InitEngine();

    auto pResourceManager = CreateResourceManager();

    auto game = CreateGame();
    game->Init();

    //g_pCharacterMesh = pResourceManager->CreateMesh("assets\\models\\dragonball\\GINE & BABY GOKU_model\\fbx\\Baby_Goku.fbx", "goku");
    g_pCharacterMesh = pResourceManager->CreateMesh("assets\\models\\stickman\\source\\Simple_Character.fbx", "stickman");
    bool bLoad = g_pCharacterMesh->Load();

    //meshRenderer = CreateMeshRenderer();
    //g_characterMeshId = meshRenderer->AddMesh(g_pCharacterMesh);
    
    auto scene = CreateScene();
    game->SetScene(scene, nullptr);
    
    auto avatar = CreateAvatar();
    avatar->SetMesh(g_pCharacterMesh);

    auto cameraInitialPosition = Vector3(0, 5, 2);
    g_camera = CreateCamera(cameraInitialPosition, 75.0f /* fov */, 1.33 /* aspect ratio */, 0.1f /* near clip */, 100.0f /* far clip */);

    auto cameraController = CreateCameraController();
    cameraController->Init(game);
    cameraController->SetCamera(g_camera);

    auto sceneRoot = scene->SceneRoot();
    g_camera->SetParent(sceneRoot);
    //sceneRoot->AttachObject(g_camera);
    //sceneRoot->AttachObject(avatar);
    avatar->SetParent(sceneRoot);

    scene->SetActiveCamera(g_camera);

    auto lookDir = Vector3(0, 0, 0) - cameraInitialPosition;
    g_camera->SetLookDirection(lookDir);

    uint64_t displacementElapsed = 0;

    auto drawEventFunc = [scene, cameraInitialPosition , &displacementElapsed](const GameTime& time) -> bool {
        
        auto camMoveDir = Vector3(1, 0, 0);

        displacementElapsed += time.ElapsedTimeMilliseconds(); 
        auto sinDis = ((float)displacementElapsed / 1000.0f);
        //LogInfo(std::format("elapsed time {} {} {}", time.ElapsedTimeMilliseconds(), displacementElapsed, sinDis));
        auto camDisplacement = camMoveDir * 10.0f * sin(sinDis);
        g_camera->SetPosition(cameraInitialPosition + camDisplacement);

        return true;
    };

    auto m_updateEventConnection = game->GameUpdate.connect(drawEventFunc);
    game->Run();

    ShutdownEngine();

    return 0;
}
