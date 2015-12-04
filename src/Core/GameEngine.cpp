#include "Core/GameEngine.h"
#include <Core/Resources/ResourceLoader.h>

#include <iostream>
#include "Utility/FPSCounter.h"
#include <Utility/Profiler.h>

cac::GameEngine::~GameEngine()
{

}

void cac::GameEngine::exit()
{
    isRunning = false;
}

void cac::GameEngine::run(IGameScene* initialScene, cac::WindowDesc windowDesc, bool isMainloop)
{
    cac::Profiler::instance()->track("Initialize GameEngine");

    if(!initialScene)
    {
	std::cout<<"Invalid initial gamescene passed!"<<std::endl;
	return;
    }
    
   
    if(!initializeRenderEngine(windowDesc))
	return;

    if(!audioManager.initialize())
	return;
    
    inputManager.initialize(renderEngine.getWindow());
    
    gameScenes.emplace_back(initialScene);
    
    if(!initialScene->setEngine(this))
    {
	std::cout<<"Couldn't set game engine for initial gamescene!"<<std::endl;
	return;
    }
    
    if(!initialScene->initialize())
    {
	std::cout<<"Couldn't initialize initial gamescene!"<<std::endl;
	return;
    }
 
   
    cac::IWindow* context = renderEngine.getWindow();
    
    cac::FPSCounter fpsCounter;
    
    cac::Profiler::instance()->stop("Initialize GameEngine");
    while(isRunning && !context->shouldClose())
    {
	fpsCounter.update();
	float dt = fpsCounter.getDeltaTime();
	
	update(dt);
    }
    
}

void cac::GameEngine::update(float dt)
{
    cac::Profiler::instance()->track("Game Loop");
    renderEngine.clearScreen(0,0,1);
    gameScenes.back()->update(dt);
    renderEngine.updateScreen();
  
    inputManager.update();
    audioManager.update();
    cac::Profiler::instance()->stop("Game Loop");
}

bool cac::GameEngine::loadPackage(std::string packagePath)
{
    ResourceLoader loader;
    ResourcePackage package;
    package = loader.loadPackage(packagePath);
    
    for(auto& texture : package.textures)
	renderEngine.loadTexture(texture);
    
    for(auto& font: package.fonts)
	renderEngine.loadFont(font);
    
    for(auto& audio : package.audios)
	audioManager.loadAudio(audio);
    
    return true;
}


cac::RenderEngine<cac::OGLRenderer>* cac::GameEngine::getRenderEngine()
{
    return &renderEngine;
}

cac::AudioManager<cac::OALAudioPlayer>* cac::GameEngine::getAudioManager()
{
    return &audioManager;
}


cac::InputManager* cac::GameEngine::getInputManager()
{
    return &inputManager;
}


bool cac::GameEngine::initializeRenderEngine(cac::WindowDesc windowDesc)
{
    cac::Profiler::instance()->track("Initialize RenderEngine");
    if(!renderEngine.initialize(windowDesc))
    {
	std::cout<<"Failed to initialze RenderEngine"<<std::endl;
	return false;
    }
    
    
    //default resources
    std::string vertexShader = "#version 330\n"
				"layout (location = 0) in vec3 vertex;"
				"layout (location = 1) in vec2 uv;"
				"layout (location = 2) in vec4 color;"
				"layout (location = 3) in vec4 textureRectangle;"
				"layout (location = 4) in mat4 MVP;"
				"out vec4 fragmentColor;"
				"out vec2 fragmentUV;"
				"void main()"
				"{"
				"fragmentColor = color;"
				"fragmentUV.x = textureRectangle.x + uv.x * textureRectangle.z;"
				"fragmentUV.y = textureRectangle.y + uv.y * textureRectangle.a;"
				"gl_Position = MVP * vec4(vertex, 1.0f);"
				"}";
				
     std::string fragShader =   "#version 330\n"
				"uniform sampler2D texture;"
				"in vec4 fragmentColor;"
				"in vec2 fragmentUV;"
				"out vec4 finalColor;"
				"void main()"
				"{"
				"finalColor =  vec4(fragmentColor.rgb,texture2D(texture, fragmentUV).r);"
				"}";
			
     std::string fragShaderText = "#version 330\n"
				"uniform sampler2D texture;"
				"in vec4 fragmentColor;"
				"in vec2 fragmentUV;"
				"out vec4 finalColor;"
				"void main()"
				"{"
				"finalColor =  vec4(fragmentColor.rgb,texture2D(texture, fragmentUV).r);"
				"}";
			
				
				
				
    renderEngine.setShaderAttributeLocation("vertex", 0);
    renderEngine.setShaderAttributeLocation("uv", 1);
    renderEngine.setShaderAttributeLocation("color", 2);
    renderEngine.setShaderAttributeLocation("textureRectangle", 3);
    renderEngine.setShaderAttributeLocation("MVP", 4);
    
    cac::ShaderResource basicShader;
    basicShader.name = "basicProgram";
    basicShader.vertexShader = vertexShader;
    basicShader.fragmentShader = fragShader;
   
    if(!renderEngine.loadShaderProgram(basicShader))
    {
        std::cout<<"Failed to create BasicShader!"<<std::endl;
	return false;
    }
    cac::RenderTechnique basicTechnique;
    basicTechnique.addRenderpass("basicProgram");
    renderEngine.setDefaultRenderTechnique(basicTechnique);
    
    cac::ShaderResource textShader;
    textShader.name = "textProgram";
    textShader.vertexShader = vertexShader;
    textShader.fragmentShader = fragShaderText;
    
    if(!renderEngine.loadShaderProgram(textShader))
    {
        std::cout<<"Failed to create TextShader!"<<std::endl;
	return false;
    }
    
    cac::RenderTechnique textTechnique;
    basicTechnique.addRenderpass("textProgram");
    renderEngine.setDefaultTextTechnique(textTechnique);
     
    cac::TextureResource defaultTexture;
    defaultTexture.name = "default";
    defaultTexture.width = 1;
    defaultTexture.height = 1;
    defaultTexture.hasAlpha = false;
    defaultTexture.data.push_back(255);
    defaultTexture.data.push_back(255);
    defaultTexture.data.push_back(255);
    
    if(!renderEngine.loadTexture(defaultTexture))
    {
	std::cout<<"Failed to create default texture!"<<std::endl;
	return false ;
    }
    
    //default Quad Mesh
    cac::MeshResource mesh;
    mesh.name = "Quad";
    mesh.vertices.push_back(cac::Vertex(0, 1, 0, 0, 1));
    mesh.vertices.push_back(cac::Vertex(1, 1, 0, 1, 1));     
    mesh.vertices.push_back(cac::Vertex(0, 0, 0, 0, 0));
    mesh.vertices.push_back(cac::Vertex(1, 0, 0, 1, 0));
    
    if(!renderEngine.loadMesh(mesh))
    {
	std::cout<<"Failed to create Quad mesh!"<<std::endl;
	return false;
    }
    
        cac::Profiler::instance()->stop("Initialize RenderEngine");
    return true;
}
