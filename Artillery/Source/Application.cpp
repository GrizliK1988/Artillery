#include "Application.h"
#include <stdexcept>

using namespace irr;
using namespace core;
using namespace video;
using namespace scene;


namespace
{
    const E_DRIVER_TYPE DeviceType = EDT_OPENGL;
    const dimension2d<u32> WindowSize( 800, 600 );
    const u32 BitsPerPixel = 32;
    const bool Fullscreen = false;
    const bool UseStencil = false;
    const bool VSync = false;
}


Application::Application()
    : m_device( nullptr ),
      m_videoDriver( nullptr ),
      m_sceneManager( nullptr ),
      m_gui( nullptr )
{

}


Application::~Application()
{
    if( m_device != nullptr )
        m_device->drop();
}


void Application::Init()
{
    m_device = createDevice( DeviceType, WindowSize, BitsPerPixel, Fullscreen, UseStencil, VSync );

    if( m_device == nullptr )
        throw std::runtime_error( "can't create video device" );

    m_device->setWindowCaption( L"Artillery" );

    m_videoDriver = m_device->getVideoDriver();
    m_sceneManager = m_device->getSceneManager();
    m_gui = m_device->getGUIEnvironment();
	
    m_device->getCursorControl()->setVisible( false );


    m_camera = m_sceneManager->addCameraSceneNodeFPS();
    m_camera->setPosition( vector3df( 150.0f, 300.0f, 100.0f ) );
    m_camera->setNearValue( 1.0f );
    m_camera->setFarValue( 2000.0f );

    m_terrain = m_sceneManager->addTerrainSceneNode( "Data/Terrain/HeightMap.png" );
    m_terrain->setMaterialTexture( 0, m_videoDriver->getTexture("Data/Terrain/DiffuseMap.png") );
    m_terrain->setMaterialTexture( 1, m_videoDriver->getTexture("Data/Terrain/DetailMap.png") );
    m_terrain->setScale( vector3df( 4.0, 1.0, 4.0 ) );        
    m_terrain->scaleTexture( 1.0f, 15.0f );
    m_terrain->setMaterialType( EMT_DETAIL_MAP );
    m_terrain->setMaterialFlag( EMF_LIGHTING, false );

 

    m_videoDriver->setTextureCreationFlag( ETCF_CREATE_MIP_MAPS, false );

    scene::ISceneNode* skybox=m_sceneManager->addSkyBoxSceneNode(
            m_videoDriver->getTexture("Data/Skybox/irrlicht2_up.jpg"),
            m_videoDriver->getTexture("Data/Skybox/irrlicht2_dn.jpg"),
            m_videoDriver->getTexture("Data/Skybox/irrlicht2_lf.jpg"),
            m_videoDriver->getTexture("Data/Skybox/irrlicht2_rt.jpg"),
            m_videoDriver->getTexture("Data/Skybox/irrlicht2_ft.jpg"),
            m_videoDriver->getTexture("Data/Skybox/irrlicht2_bk.jpg"));


    m_videoDriver->setTextureCreationFlag( ETCF_CREATE_MIP_MAPS, true );

    IAnimatedMesh* mesh = m_sceneManager->getMesh("Data/Man/sydney.md2");
        if (!mesh)
        {
                m_device->drop();
                throw std::runtime_error( "can't create man" );
        }
        IAnimatedMeshSceneNode* node = m_sceneManager->addAnimatedMeshSceneNode( mesh );

        if (node)
        {
                node->setMaterialFlag(EMF_LIGHTING, false);
                node->setMD2Animation(scene::EMAT_STAND);
                node->setMaterialTexture( 0, m_videoDriver->getTexture("Data/Man/sydney.bmp") );
        }

        node->setPosition( vector3df(200.0, 150.0, 200.0) );
}


void Application::MainLoop()
{
    while( m_device->run() )
    {
        m_videoDriver->beginScene( true, true, SColor( 255, 40, 40, 80 ) );
        m_sceneManager->drawAll();
        m_gui->drawAll();
        m_videoDriver->endScene();
        stringw str = L"fps: ";
        str+=m_videoDriver->getFPS();
        m_device->setWindowCaption(str.c_str());
    }
}

