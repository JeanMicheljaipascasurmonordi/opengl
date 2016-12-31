#define GLEW_STATIC

#include <glimac/SDLWindowManager.hpp>
#include <GL/glew.h>
#include <iostream>
#include <vector>
#include <GL/glut.h>
#include <GL/gl.h>
#include <math.h>
#include <string>
#include <fstream>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

#include <glimac/Program.hpp>
#include <glimac/FilePath.hpp>
#include <glimac/Sphere.hpp>
#include <glimac/glm.hpp>
#include <glimac/Image.hpp>
#include <glimac/FreeflyCamera.hpp>

#include "../include/Triangle3D.h"
#include "../include/Cube3D.h"
#include "../include/Sphere3D.h"

#include "../include/mur.h"
#include "../include/murAngle.h"
#include "../include/murCulDeSac.h"
#include "../include/position.h"
#include "../include/loot.h"
#include "../include/ennemi.h"
#include "../include/hero.h"
#include "../include/niveau.h"

using namespace glimac;
using namespace std;

Hero hero;
Hero camera;

Niveau niveau = Niveau("D:\\Sons\\CindySandersOnTheRoadToRouteOfDiamant\\opengl\\assets\\niveaux\\niveautest.txt");
//FreeflyCamera camera;



void initGlew() {
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        cerr << glewGetErrorString(glewInitError) << endl;
        exit(1);
    }
}

int main(int argc, char **argv) {





    cout << "test log console" << endl;

    // Init de l'application
    SDLWindowManager windowManager(900, 900, "DungeonGL");
    initGlew();
    glEnable(GL_DEPTH_TEST);


    //Init Son
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        cout << "erreur Initialisation Mixer" << endl;

    Mix_Music *musique = NULL;
    musique = Mix_LoadMUS("D:\\Sons\\CindySandersOnTheRoadToRouteOfDiamant\\opengl\\assets\\music\\cindysander_papillondelumiere.mp3");
    if(musique == NULL)
        cout << "erreur repertoire musique" << endl;
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    Mix_PlayMusic(musique, -1);

    Mix_AllocateChannels(32);
    Mix_Chunk *cindyattack = Mix_LoadWAV("cindyattack.ogg");
    if(cindyattack == NULL)
        cout << Mix_GetError() << endl;

//===== Construction du monde =====//

    int size = niveau.murs.size();
    Cube3D cube[size];
    for(int i=0; i<size; i++){
        Position p = niveau.murs[i].getPosition();
        float alpha = niveau.murs[i].getAngle();
        cube[i] = Cube3D(1);
        cube[i].setTranslation(p.x, p.y, p.z);
        cube[i].setPosition(p);
        if(alpha)

            cube[i].setRotation(glm::vec3(0, 1, 0), alpha);

    }

    size = niveau.mursAngles.size();
    Cube3D cubeAngle[size];
    for(int i=0; i<size; i++){
        Position p = niveau.mursAngles[i].getPosition();
        float alpha = niveau.mursAngles[i].getAngle();
        cubeAngle[i] = Cube3D(2);
        cubeAngle[i].setTranslation(p.x, p.y, p.z);
        if(alpha)

            cubeAngle[i].setRotation(glm::vec3(0, 1, 0), alpha);
    }

    size = niveau.mursCDS.size();
    Cube3D cubeCDS[size];
    for(int i=0; i<size; i++){
        Position p = niveau.mursCDS[i].getPosition();
        float alpha = niveau.mursCDS[i].getAngle();
        cubeCDS[i] = Cube3D(3);
        cubeCDS[i].setTranslation(p.x, p.y, p.z);
        if(alpha)
            cubeCDS[i].setRotation(glm::vec3(0, 1, 0), alpha);

    }

    size = niveau.loots.size();
    Cube3D loot[size];
    for(int i=0; i<size; i++){
        Position p = niveau.loots[i].getPosition();

        loot[i] = Cube3D(4);
        loot[i].setTranslation(p.x, p.y, p.z);
        loot[i].setScale(0.5, 0.5, 0.5);
    }

    size = niveau.ennemis.size();
    Cube3D ennemi[size];
    for(int i=0; i<size; i++){
        Position p = niveau.ennemis[i].getPosition();
        ennemi[i] = Cube3D(5);
        ennemi[i].setTranslation(p.x, p.y, p.z);
    }

    int alpha;
    int newx, newz;
    Position p;
    int test=0;

    // Application loop:
    bool done = false;
    while(!done) {
        Position positionCamera = newPosition(0,0,0);
        camera.setPosition(positionCamera);
      
       


        if (samePosition(hero.getPosition(), niveau.positionFin) && hero.getNbrFan() == niveau.getFanNeeded()){
            cout<<"niveau fini"<<endl;
        }

        for (int i=0; i<niveau.loots.size(); i++){
            if (samePosition(hero.getPosition(), niveau.loots[i].getPosition())){
                int fan = hero.getNbrFan();
                hero.setNbrFan(fan + niveau.loots[i].getNbrFan());
                niveau.deleteLoot(niveau.loots[i].getID());
                cout<<"loot !"<<endl;
                //loot[i].setTranslation(40, 40, 40);
            }
        }


        // Event loop:
        SDL_Event e;
        if(SDL_PollEvent( &e ) == 1) {
            if(e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            switch(e.type) {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_w:{
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "z" << std::endl;
                            Position p = hero.getPosition();
                            Position pCamera = camera.getPosition();
                            double newz;
                            newz = p.z + 0.5;
                            p.z = newz;
                            pCamera.z = 0.5;


                            hero.setPosition(p);
                            camera.setPosition(pCamera);
                            }
                            break;

                        case SDLK_s: {
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "s" << std::endl;
                            Position p = hero.getPosition();
                            double newz;
                            Position pCamera = camera.getPosition();
                            pCamera.z = -0.5;
                            newz = p.z - 0.5;
                            p.z = newz;


                            hero.setPosition(p);
                            camera.setPosition(pCamera);
                        }
                            break;

                        case SDLK_a:{
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "q" << std::endl;
                            Position p = hero.getPosition();
                            double newx;
                            Position pCamera = camera.getPosition();
                            pCamera.x = 0.5;
                            newx = p.x + 0.5;
                            p.x = newx;
                            //move = 1;
                            hero.setPosition(p);
                            camera.setPosition(pCamera);
                        }
                        break;

                        case SDLK_d : {
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "d" << std::endl;
                            Position p = hero.getPosition();
                            Position pCamera = camera.getPosition();
                            double newx;
                            //move = 1;
                            pCamera.x = -0.5;
                            newx = p.x - 0.5;
                            p.x = newx;
                            camera.setPosition(pCamera);
                            hero.setPosition(p);
                        }
                        break;

                        case SDLK_RIGHT: {
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "RIGHT" << std::endl;
                            alpha = hero.getAngle();
                            hero.setAngle(alpha + 90);
                        }
                        break;


                        case SDLK_LEFT: {
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "LEFT" << std::endl;
                            alpha = hero.getAngle();
                            hero.setAngle(alpha - 90);
                        }
                        break;

                        case SDLK_SPACE: { // Attaque
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "espace" << std::endl;
                        }
                        break;

                        default:
                            break;
                    }
                default:
                    break;
            }
        }


        // Clear de la fenêtre avant le nouveau rendu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rendu des objets de la scene
        Position p = camera.getPosition();
        Position pHero = hero.getPosition();

        int alphaHero = hero.getAngle();

        for ( std::vector<Object3D*>::const_iterator it = Object3D::getSceneObjects().begin() ;  it != Object3D::getSceneObjects().end() ; it++ ) {
            (*it)->addTranslation(p.x, p.y, p.z); 




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

