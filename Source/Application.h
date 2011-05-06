#pragma once

#include <Irrlicht.h>


class World;


class Application
{
public:
    Application();
    ~Application();

    void Initialize();
    void MainLoop();

private:
    irr::IrrlichtDevice *m_irrDevice;
    irr::video::IVideoDriver *m_videoDriver;
    irr::scene::ISceneManager *m_sceneManager;
    irr::gui::IGUIEnvironment *m_guiEnvironment;

    bool m_isInitialized;
    bool m_inMainLoop;

    World *m_world;
};

