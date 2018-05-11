#include "Application.h"
#include "Scene.h"

Scene::Scene()
{
	name = "scene";
}

Scene::~Scene() {}

bool Scene::Awake(pugi::xml_node& sceneNode)
{
	return true;
}

bool Scene::Start()
{
	return true;
}

bool Scene::PreUpdate()
{
	return true;
}

bool Scene::Update(float dt)
{	
	return true;
}

bool Scene::CleanUp()
{
	return true;
}