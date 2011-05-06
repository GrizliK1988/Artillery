#pragma once

#include <Irrlicht.h>


class World
{
public:
    World( irr::IrrlichtDevice *irrDevice );

private:
    irr::IrrlichtDevice *m_irrDevice;
    irr::video::IVideoDriver *m_videoDriver;
    irr::scene::ISceneManager *m_sceneManager;
    irr::scene::ITerrainSceneNode *m_terrain;
};

