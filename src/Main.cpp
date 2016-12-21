#define GLEW_STATIC

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <GL/glut.h>
#include <GL/gl.h>
#include <string>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>


#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>

#include "../include/Triangle3D.h"
#include "../include/Cube3D.h"
#include "../include/Sphere3D.h"

using namespace glimac;

void initGlew() {
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        std::cerr << glewGetErrorString(glewInitError) << std::endl;
        exit(1);
    }
}

int main(int argc, char **argv) {

    std::cout << "test log console" << std::endl;

    // Init de l'application
    SDLWindowManager windowManager(800, 800, "DungeonGL");
    initGlew();
    glEnable(GL_DEPTH_TEST);

    //Init Son
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        std::cout << "erreur Initialisation Mixer" << std::endl;

    Mix_Music *musique = NULL;
    musique = Mix_LoadMUS("cindysander_papillondelumiere.mp3");
    if(musique == NULL)
        std::cout << "erreur repertoire musique" << std::endl;
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    Mix_PlayMusic(musique, -1);

    Mix_AllocateChannels(32);
    Mix_Chunk *cindyattack = Mix_LoadWAV("cindyattack.ogg");
    if(cindyattack == NULL)
        std::cout << Mix_GetError() << std::endl;

    //===== Construction du monde =====//
    Cube3D cube1, cube2, cube3, cube4;
    //Sphere3D sphere(windowManager);
    cube1.setTranslation( 0, 0, -5 );
    cube2.setTranslation( 0, 0, -6 );
    cube4.setTranslation( 1, 0, -7 );
    cube3.setRotation( glm::vec3(0, 90, 0), 1.5f );

/*    Cube3D c1,c2,c3;
    c1.setTranslation( -1, -2, -5 );
    c2.setTranslation( 0, -2, -5 );
    c3.setTranslation( 1, -2, -5 );

    Triangle3D t;
    t.setTranslation( 0,1.35,-3 );*/



    // Application loop:
    bool done = false;
    while(!done) {
        // Event loop:
        SDL_Event e;
        while(windowManager.pollEvent(e)) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }
            switch(e.type) {
                case SDL_KEYDOWN:
                    switch( e.key.keysym.sym ){
                        case SDLK_w:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            std::cout << "z" << std::endl;
                            break;
                        case SDLK_s:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            std::cout << "s" << std::endl;
                            break;
                        case SDLK_a:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            std::cout << "q" << std::endl;
                            break;
                        case SDLK_d:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            std::cout << "d" << std::endl;
                            break;
                        case SDLK_RIGHT:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            std::cout << "RIGHT" << std::endl;
                            break;
                        case SDLK_LEFT:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            std::cout << "LEFT" << std::endl;
                            break;
                        case SDLK_SPACE: // Attaque
                            Mix_PlayChannel(-1, cindyattack, 0);
                            std::cout << "espace" << std::endl;
                            break;
                    }
                break;
            }
        }

        // Jeu
        /*cube.addRotation( glm::vec3(0, 1, 0), 0.025f );
        cube.addRotation( glm::vec3(1, 0, 0), 0.01f );
        cube.addRotation( glm::vec3(0, 0, 1), 0.015f );
        c1.addRotation( glm::vec3(1, 0, 0), 0.005f );
        c2.addRotation( glm::vec3(1, 0, 0), 0.005f );
        c3.addRotation( glm::vec3(1, 0, 0), 0.005f );
        t.addRotation( glm::vec3(0, 1, 0), 0.005f );*/

        // Clear de la fenêtre avant le nouveau rendu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rendu des objets de la scene
        for ( std::vector<Object3D*>::const_iterator it = Object3D::getSceneObjects().begin() ;  it != Object3D::getSceneObjects().end() ; it++ ) {
            (*it)->draw();
        }

        // Update the display
        windowManager.swapBuffers();
    }

    //liberation des ressources
    // TODO
    //glDeleteBuffers(1, &vbo);
    //glDeleteVertexArrays(1, &vao);

    Mix_FreeChunk(cindyattack);
    Mix_FreeMusic(musique);
    Mix_CloseAudio();

    return 0;
}
