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
Niveau niveau = Niveau("D:/Sons/CindySandersOnTheRoadToRouteOfDiamant/opengl/assets/niveaux/niveautest.txt");

void initGlew() {
    // Initialize glew for OpenGL3+ support
    GLenum glewInitError = glewInit();
    if(GLEW_OK != glewInitError) {
        cerr << glewGetErrorString(glewInitError) << endl;
        exit(1);
    }
}

int main(int argc, char **argv) {

   
    cout<<niveau.getFanNeeded();


    cout << "test log console" << endl;

    // Init de l'application
    SDLWindowManager windowManager(900, 900, "DungeonGL");
    initGlew();
    glEnable(GL_DEPTH_TEST);


    //Init Son
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1)
        cout << "erreur Initialisation Mixer" << endl;

    Mix_Music *musique = NULL;
    musique = Mix_LoadMUS("D:/Sons/CindySandersOnTheRoadToRouteOfDiamant/opengl/assets/music/cindysander_papillondelumiere.mp3");
    if(musique == NULL)
        cout << "erreur repertoire musique" << endl;
    Mix_VolumeMusic(MIX_MAX_VOLUME / 2);
    Mix_PlayMusic(musique, -1);

    Mix_AllocateChannels(32);
    Mix_Chunk *cindyattack = Mix_LoadWAV("cindyattack.ogg");
    if(cindyattack == NULL)
        cout << Mix_GetError() << endl;

//===== Construction du monde =====//
//    Cube3D cube1, cube2, cube3;
//    //Sphere3D sphere(windowManager);
//    cube1.setTranslation( 0, 0, -1 );
//    cube2.setTranslation( 0, 0, -2 );
//    cube3.setTranslation( -1, 0, 0 );
//    cube3.setRotation( glm::vec3(0, 1, 0), 3.14f );
    
    int size = niveau.murs.size();
    Cube3D cube[size];
    for(int i=0; i<size; i++){
        Position p = niveau.murs[i].getPosition();
        float alpha = niveau.murs[i].getAngle();
        cube[i] = Cube3D(1);
        cube[i].setTranslation(p.x, p.y, p.z);
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
    }

    size = niveau.ennemis.size();
    Cube3D ennemi[size];
    for(int i=0; i<size; i++){
        Position p = niveau.ennemis[i].getPosition();
        ennemi[i] = Cube3D(5);
        ennemi[i].setTranslation(p.x, p.y, p.z);
    }


    /*ifstream fileNiveau("C:/Users/Owen/Desktop/opengl projet/OPEN_GL/dungeonGL/src/test.txt");
    int size;
    if(fileNiveau){
        for(int i=0; i<5; i++){
            Cube3D cube;
            int xcube = 0;
            int ycube = 0;
            int zcube = 0;
            int alphacube = 0;
            fileNiveau >> xcube;
            cout<<"x = "<<xcube;
            fileNiveau >> ycube;
            fileNiveau >> zcube;
            fileNiveau >> alphacube;
            cube.setTranslation(xcube, ycube, zcube);
            cube.setRotation(glm::vec3(0, alphacube, 0), 1.5f);
        }
    }
    else{
        cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << endl;
    }*/

    int alpha;
    int newx, newz;
    Position p;
    int test=0;

    // Application loop:
    bool done = false;
    while(!done) {

        Position positionHero = newPosition(0,0,0);
        hero.setPosition(positionHero);
        hero.setAngle(0);
        if (samePosition(hero.getPosition(), niveau.positionFin) && hero.getNbrFan() == niveau.getFanNeeded()){
            cout<<"niveau fini"<<endl;
        }

        for (int i=0; i<niveau.loots.size(); i++){
            if (samePosition(hero.getPosition(), niveau.loots[i].getPosition())){
                int fan = hero.getNbrFan();
                hero.setNbrFan(fan + niveau.loots[i].getNbrFan());
                niveau.deleteLoot(niveau.loots[i].getID());
                cout<<"loot !"<<endl;
                loot[i].setTranslation(40, 40, 40);
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
                    switch( e.key.keysym.sym ){
                        case SDLK_w:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "z" << std::endl;
                            p = hero.getPosition();
                            alpha = hero.getAngle();
                            p.z=1;
                            hero.setPosition(p);
                            cout << hero.getPosition().z << endl;
                            break;
                        case SDLK_s :
                             Mix_PlayChannel(-1, cindyattack, 0);
                             cout << "s" << std::endl;
                             p = hero.getPosition();
                             alpha = hero.getAngle();
                             p.z--;
                             hero.setPosition(p);
                             break;
                        case SDLK_a:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "q" << std::endl;
                            p = hero.getPosition();
                            alpha = hero.getAngle();
                            newx = p.x + 1;
                            p.x = newx;
                            hero.setPosition(p);
                            break;
                        case SDLK_d:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "d" << std::endl;
                            p = hero.getPosition();
                            alpha = hero.getAngle();
                            newx =p.x - 1;
                            p.x = newx;
                            hero.setPosition(p);
                            break;
                        case SDLK_RIGHT:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "RIGHT" << std::endl;
                            alpha = hero.getAngle();
                            hero.setAngle(alpha + 90);
                            break;
                        case SDLK_LEFT:
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "LEFT" << std::endl;
                            alpha = hero.getAngle();
                            hero.setAngle(alpha - 90);
                            break;
                        case SDLK_SPACE: // Attaque
                            Mix_PlayChannel(-1, cindyattack, 0);
                            cout << "espace" << std::endl;
                            break;
                        default:
                            break;
                    }
                    break;
                default:
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
        Position p = hero.getPosition();
        int alpha = hero.getAngle();
        for ( std::vector<Object3D*>::const_iterator it = Object3D::getSceneObjects().begin() ;  it != Object3D::getSceneObjects().end() ; it++ ) {
            (*it)->addTranslation(p.x, p.y, p.z);
            if (alpha != 0) (*it)->addRotation(glm::vec3(0, alpha, 0), 1.5f);
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
