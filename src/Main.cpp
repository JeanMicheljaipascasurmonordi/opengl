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
#define PI 3.14159265
Hero hero;
//Hero camera;

Niveau niveau = Niveau("C:/Users/Owen/Desktop/opengl projet/OPEN_GL/dungeonGL/assets/niveaux/niveautest.txt");
FreeflyCamera camera;



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
    musique = Mix_LoadMUS("C:/Users/Owen/Desktop/opengl projet/OPEN_GL/dungeonGL/assets/music/cindysander_papillondelumiere.mp3");
    if(musique == NULL)
        cout << "erreur repertoire musique" << endl;
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    Mix_PlayMusic(musique, -1);

    Mix_AllocateChannels(32);
    Mix_Chunk *cindyattack = Mix_LoadWAV("cindyattack.ogg");
    Mix_Chunk *cindymove = Mix_LoadWAV("cindymove.ogg");
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

        if(i==size-1)
            cubeCDS[i] = Cube3D(6);
        else
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
        loot[i].setScale(0.1, 0.1, 1);
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

    // Application loop:
    bool done = false;
    while(!done) {
        //Position positionCamera = newPosition(0, 0, 0);
        //camera.setPosition(positionCamera);


        if (samePosition(hero.getPosition(), niveau.positionFin) && hero.getNbrFan() == niveau.getFanNeeded()) {
            cout << "niveau fini" << endl;
            done = true;
        }

        for (int i = 0; i < niveau.loots.size(); i++) {
            //cout << distance(hero.getPosition(), niveau.loots[i].getPosition())<<endl;
            if (samePosition(hero.getPosition(), niveau.loots[i].getPosition())) {
                int fan = hero.getNbrFan();
                hero.setNbrFan(fan + niveau.loots[i].getNbrFan());
                niveau.loots[i].setNbrFan(0);
                loot[i].setTranslation(40, 40, 40);
            }
        }

         for (int i = 0; i < niveau.ennemis.size(); i++) {

            if (niveau.ennemis[i].getPv() < 1) {
                int fan = hero.getNbrFan();
                hero.setNbrFan(fan + niveau.ennemis[i].getFanDrop());
                niveau.ennemis[i].setNbrFan(0);
                cout << "ennemis mort" << endl;
                ennemi[i].setTranslation(40, 40, 40);
            }
        }
         

        // Event loop:
        SDL_Event e;
        if (SDL_PollEvent(&e) == 1) {
            if (e.type == SDL_QUIT) {
                done = true; // Leave the loop after this iteration
            }

            switch (e.type) {
                case SDL_KEYDOWN:
                    switch (e.key.keysym.sym) {
                        case SDLK_w: {
                            Mix_PlayChannel(1, cindymove, 0);
                            cout << "z" << std::endl;
                            Position p = hero.getPosition();
                            int angle = hero.getAngle();
                           
                            p.z = p.z - 0.5*cos(angle * PI /180);
                            p.x = p.x + 0.5*sin(angle * PI /180);
                            
                           
                            cout<<niveau.distanceFromObject(p)<<endl;
                            if(niveau.distanceFromObject(p)){
                                hero.setPosition(p);
                                //camera.setPosition(pCamera);
                                camera.moveFront(0.5);
                            }

                        }
                            break;
                        case SDLK_s: {
                            Mix_PlayChannel(1, cindymove, 0);
                            cout << "s" << std::endl;
                            Position p = hero.getPosition();
                            int angle = hero.getAngle();
                           
                            p.z = p.z + 0.5*cos(angle * PI /180);
                            p.x = p.x - 0.5*sin(angle * PI /180);

                            if(niveau.distanceFromObject(p)){
                                hero.setPosition(p);
                                //camera.setPosition(pCamera);
                                camera.moveFront(-0.5); 
                            }

                        }
                            break;
                        case SDLK_a: {
                            Mix_PlayChannel(1, cindymove, 0);
                            cout << "q" << std::endl;
                            Position p = hero.getPosition();
                            int angle = hero.getAngle();
                           
                            p.z = p.z - 0.5*sin(angle * PI /180);
                            p.x = p.x - 0.5*cos(angle * PI /180);
                            if(niveau.distanceFromObject(p)){
                                hero.setPosition(p);
                                //camera.setPosition(pCamera);
                                camera.moveLeft(0.5);
                            }

                        }

                            break;
                        case SDLK_d: {
                            Mix_PlayChannel(1, cindymove, 0);
                            cout << "d" << std::endl;
                            Position p = hero.getPosition();
                            int angle = hero.getAngle();
                           
                            p.z = p.z + 0.5*sin(angle * PI /180);
                            p.x = p.x + 0.5*cos(angle * PI /180);
                            if(niveau.distanceFromObject(p)){
                               // camera.setPosition(pCamera);
                                hero.setPosition(p);
                                camera.moveLeft(-0.5);
                            }


                        }

                            break;
                        case SDLK_RIGHT: {
                            Mix_PlayChannel(1, cindymove, 0);
                            cout << "RIGHT" << std::endl;
                            int alphaH = hero.getAngle();
                            hero.setAngle(alphaH + 90);
                            camera.rotateLeft(-90);
                        }

                            break;
                        case SDLK_LEFT: {
                            Mix_PlayChannel(1, cindymove, 0);
                            cout << "LEFT" << std::endl;
                            int alphaH = hero.getAngle();
                            hero.setAngle(alphaH - 90);
                            camera.rotateLeft(90);


                        }

                            break;
                        case SDLK_SPACE: {// Attaque
                            Mix_PlayChannel(3, cindyattack, 0);
                            cout << "espace" << std::endl;
                            for (int i=0; i < niveau.ennemis.size(); i++){                                
                                if (abs(distance(hero.getPosition(), niveau.ennemis[i].getPosition())) < 2){
                                    cout<<"Attaque"<<endl;
                                    int pv = niveau.ennemis[i].getPv();
                                    niveau.ennemis[i].setPv(pv - 1);
                                    
                                }
                            }
                        }
                            break;
                        default:
                            break;
                    }
                    break;

            }
        }


        // Clear de la fenêtre avant le nouveau rendu
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Rendu des objets de la scene
        //Position pC = camera.getPosition();
        Position pHero = hero.getPosition();

        int alphaHero = hero.getAngle();

        for (std::vector<Object3D *>::const_iterator it = Object3D::getSceneObjects().begin();
             it != Object3D::getSceneObjects().end(); it++) {
            /*Position newp = (*it)->getPosition();
            newp.x -= pC.x;
            newp.x -= pC.y;
            newp.x -= pC.z;
            (*it)->setPosition(newp);
            (*it)->addTranslation(pC.x, pC.y, pC.z);*/
            //(*it)->modelMatrix = (*it)->modelMatrix * camera.getViewMatrix() * (*it)->translationMatrix;

            (*it)->draw(camera.getViewMatrix());
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