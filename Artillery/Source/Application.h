#pragma once

#include <irrlicht.h>


class Application
{
public:
    Application();
    ~Application();

    void Init();
    void MainLoop();

private:
    irr::IrrlichtDevice *m_device;
    irr::video::IVideoDriver *m_videoDriver;
    irr::scene::ISceneManager *m_sceneManager;
    irr::gui::IGUIEnvironment *m_gui;

    irr::scene::ICameraSceneNode *m_camera;
    irr::scene::ITerrainSceneNode *m_terrain;
};

