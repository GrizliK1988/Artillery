#include "World.h"


namespace
{
    // Terrain parameters
    const irr::io::path HeightMapPath = "Data/Terrain/HeightMap.png";
    const irr::io::path DiffuseMapPath = "Data/Terrain/DiffuseMap.png";
    const irr::io::path DetailMapPath = "Data/Terrain/DetailMap.png";

    const irr::u32 DiffuseMapLayer = 0;
    const irr::u32 DetailMapLayer = 1;

    const irr::core::vector3df TerrainScale( 2.0f, 0.5f, 2.0f );
    const irr::f32 DiffuseMapScale = 1.0f;
    const irr::f32 DetailMapScale = 20.0f;

    // Skydome parameters
    const irr::io::path SkydomeTexturePath = "Data/Skydome/Skydome.jpg";

    // Fog parameters
    const irr::video::E_FOG_TYPE FogType = irr::video::EFT_FOG_LINEAR;

    const irr::video::SColor FogColor( 255, 192, 192, 224 );

    const irr::f32 FogStart = 250.0f;
    const irr::f32 FogEnd = 1000.0f;
    const irr::f32 FogDensity = 0.003f;

    const bool PixelFog = true;
    const bool RangeFog = false;
}


World::World( irr::IrrlichtDevice *irrDevice )
    : m_irrDevice( irrDevice ),
      m_videoDriver( irrDevice->getVideoDriver() ),
      m_sceneManager( irrDevice->getSceneManager() ),
      m_terrain( nullptr )
{
    m_terrain = m_sceneManager->addTerrainSceneNode( HeightMapPath );

    m_terrain->setScale( TerrainScale );
    m_terrain->setMaterialType( irr::video::EMT_DETAIL_MAP );
    m_terrain->setMaterialTexture( DiffuseMapLayer, m_videoDriver->getTexture( DiffuseMapPath ) );
    m_terrain->setMaterialTexture( DetailMapLayer, m_videoDriver->getTexture( DetailMapPath ) );
    m_terrain->setMaterialFlag( irr::video::EMF_FOG_ENABLE, true );
    m_terrain->setMaterialFlag( irr::video::EMF_LIGHTING, false );
    m_terrain->scaleTexture( DiffuseMapScale, DetailMapScale );

    irr::scene::ISceneNode *skydome = m_sceneManager->addSkyDomeSceneNode( m_videoDriver->getTexture( SkydomeTexturePath ), 18, 8, 1.0f, 2.0f, 1000.0f );

    irr::scene::ICameraSceneNode *camera = m_sceneManager->addCameraSceneNodeFPS();
    camera->setPosition( irr::core::vector3df( 1024.0f, m_terrain->getHeight( 1024.0f, 1024.0f ) + 50.0f, 1024.0f ) );

    m_videoDriver->setFog( FogColor, FogType, FogStart, FogEnd, FogDensity, PixelFog, RangeFog );
}

