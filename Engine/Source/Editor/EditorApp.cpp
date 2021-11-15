// Copyright (c) 2021 Futureblur. All rights reserved. Visit https://ice.futureblur.com for more information.

#include "Runtime/Core/CoreMinimal.h"

#include "EditorCamera.h"

#include "Runtime/Scene/Components/CameraComponent.h"
#include "Runtime/Scene/Components/MeshComponent.h"
#include "Renderer/Intern/OpenGLData.h"
#include "Renderer/Intern/Texture.h"

using namespace Iceblur;

class EditorApp : public Application
{
public:
	EditorApp() = default;

	~EditorApp() override = default;

	void OnPostInit() override
	{
		Log::SetLogVerbosity(ELogVerbosity::Error);
		WindowManager::CreateWindow(EWindowType::Editor, { }, true);

		KeyAction action(ICE_KEY_ESCAPE, ICE_PRESS, std::bind(&Application::Quit, this));
		InputManager::BindKey(action);

		Application::OnPostInit();
	}

	void OnStart() override
	{
		Application::OnStart();

		auto ent = Entity::CreateAndAdd("Awesome Entity");
		Entity::CreateAndAdd("Cool Entity");
		Entity::CreateAndAdd("Great Entity");
		ent->Transform()->Translate(glm::vec3(0.0f, 0.0f, -1.0f));

		//ent->GetComponent<TransformComponent>()->SetPosition(glm::vec3(0, 69, 0));

		/*std::vector<Vertex> m_Vertices = {
				Vertex(0.5f, 0.5f, 0.0f, 1.0f, 1.0f),
				Vertex(0.5f, -0.5f, 0.0f, 1.0f, 0.0f),
				Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 0.0f),
				Vertex(-0.5f, 0.5f, 0.0f, 0.0f, 1.0f)
		};*/

		std::vector<Vertex> m_Vertices = {
				Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
				Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
				Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
				Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
				Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
				Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),

				Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),
				Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f),
				Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
				Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
				Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f),
				Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f),

				Vertex(-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
				Vertex(-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
				Vertex(-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
				Vertex(-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
				Vertex(-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
				Vertex(-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f),

				Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
				Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
				Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
				Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
				Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
				Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),

				Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),
				Vertex(0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f),
				Vertex(0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
				Vertex(0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f),
				Vertex(-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),
				Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 1.0f),

				Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
				Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
				Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
				Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
				Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
				Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0)
		};

		std::vector<VID> m_Indices = {
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
		};

		TextureProps props;
		props.source = VIO::GetEngineLocation() + "\\Binaries\\Win64\\Debug\\Editor\\Resources\\uvtest.png";
		Texture* texture = new Texture(props);
		MeshData* data = new MeshData(m_Vertices, m_Indices, { texture });
		MeshComponent* meshComponent = new MeshComponent(data);
		meshComponent->m_DrawIndexed = false;
		ent->AddComponent<MeshComponent>(meshComponent);

		auto* camera = new EditorCamera();
		camera->SetupInput();
		Renderer::GetCurrentPipeline()->SetSpectatorCamera(camera);
	}
};

ICE_ENTRY_POINT(EditorApp)