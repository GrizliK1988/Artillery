#include "Application.h"
#include "World.h"
#include <stdexcept>
#include <cassert>


namespace
{
    const irr::core::stringw WindowCaption = L"Artillery Storm";
}


Application::Application()
    : m_irrDevice( nullptr ),
      m_videoDriver( nullptr ),
      m_sceneManager( nullptr ),
      m_guiEnvironment( nullptr ),
      m_isInitialized( false ),
      m_inMainLoop( false ),
      m_world( nullptr )
{
}


Application::~Application()
{
    if( m_irrDevice != nullptr )
        m_irrDevice->drop();

    if( m_world != nullptr )
        delete m_world;
}


void Application::Initialize()
{
    if( m_isInitialized )
        throw std::runtime_error( "application is already initialized" );

    irr::SIrrlichtCreationParameters params;

    params.DriverType = irr::video::EDT_OPENGL;
    params.Bits = 32;

    m_irrDevice = irr::createDeviceEx( params );

    if( m_irrDevice == nullptr )
        throw std::runtime_error( "can't create Irrlicht device" );

    m_irrDevice->setWindowCaption( WindowCaption.c_str() );

    m_videoDriver = m_irrDevice->getVideoDriver();
    m_sceneManager = m_irrDevice->getSceneManager();
    m_guiEnvironment = m_irrDevice->getGUIEnvironment();

    m_world = new World( m_irrDevice );

    m_isInitialized = true;
}


void Application::MainLoop()
{
    if( !m_isInitialized )
        throw std::runtime_error( "application is not initialized" );
    if( m_inMainLoop )
        throw std::runtime_error( "application is already in main loop" );

    m_inMainLoop = true;

    while( m_irrDevice->run() )
    {
        if( m_videoDriver->beginScene( true, true, irr::video::SColor( 0xFF, 0x40, 0x40, 0x80 ) ) )
        {
            m_sceneManager->drawAll();
            m_guiEnvironment->drawAll();
            m_videoDriver->endScene();
        }
    }

    m_inMainLoop = false;
}

