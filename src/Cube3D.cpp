
#define GLEW_STATIC



#include "../include/Cube3D.h"

using namespace glimac;

struct Triangle{
    glm::vec3 pos;
    glm::vec3 color;
    glm::vec2 uv;


    Triangle( glm::vec3 pos, glm::vec3 color, glm::vec2 uv){
        this->pos = pos;

        this->color = color;
        this->uv = uv;
    }

};

Cube3D::Cube3D(){
    std::unique_ptr<Image> image;
    image = loadImage("C:/Users/Owen/Desktop/opengl projet/OPEN_GL/dungeonGL/assets/textures/texturepack.png");

    if(image == NULL)
        std::cout << "erreur image" << std::endl;
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA ,GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    FilePath applicationPath(".\\opengl.exe");
    Program program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\CubeTex.vs.glsl",
                                  applicationPath.dirPath() + "\\..\\..\\shaders\\CubeTex.fs.glsl");
    program.use();
    // Matrice de transformation
    this->uModelMatrixID = glGetUniformLocation( program.getGLId(), "MVP" );


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)
    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float unit = 0.5f;
    BBox3f box( glm::vec3(-unit,-unit,-unit), glm::vec3(unit,unit,unit) );

    glm::vec3 upA( box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 upB( box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 upC( -box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 upD( -box.upper.x, box.upper.y, box.upper.z );

    glm::vec3 lowA( box.upper.x, -box.upper.y, box.upper.z  );
    glm::vec3 lowB( box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 lowC( -box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 lowD( -box.upper.x, -box.upper.y, box.upper.z );

    std::vector<Triangle> vertices;
    vertices.push_back( Triangle( upA, glm::vec3(1, 0, 0), glm::vec2(1.f, 0.f)));
    vertices.push_back( Triangle( upB, glm::vec3(1, 1, 0), glm::vec2(1.f, 0.5f)));
    vertices.push_back( Triangle( upC, glm::vec3(1, 1, 1), glm::vec2(0.66f, 0.5f)));
    vertices.push_back( Triangle( upD, glm::vec3(0, 1, 1), glm::vec2(0.66f, 0.f)));
    vertices.push_back( Triangle( lowA, glm::vec3(0, 0, 1), glm::vec2(0.33f, 0.5f)));
    vertices.push_back( Triangle( lowB, glm::vec3(1, 0, 1), glm::vec2(0.33f, 1.f)));
    vertices.push_back( Triangle( lowC, glm::vec3(1, 1, 0), glm::vec2(0.f , 1.f)));
    vertices.push_back( Triangle( lowD, glm::vec3(1, 0, 0), glm::vec2(0.f, 0.5f)));

    //RIGHT
    vertices.push_back( Triangle( upA, glm::vec3(1, 0, 0), glm::vec2(1.f, 0.5f)));
    vertices.push_back( Triangle( lowB, glm::vec3(1, 0, 1), glm::vec2(0.66f, 1.f)));
    vertices.push_back( Triangle( lowA, glm::vec3(0, 0, 1), glm::vec2(1.f, 1.f)));
    vertices.push_back( Triangle( upB, glm::vec3(1, 1, 0), glm::vec2(0.66f, 0.5f)));

    //LEFT
    vertices.push_back( Triangle( upD, glm::vec3(1, 0, 0), glm::vec2(0.66f, 0.5f)));
    vertices.push_back( Triangle( lowC, glm::vec3(1, 0, 1), glm::vec2(0.33f, 1.f)));
    vertices.push_back( Triangle( lowD, glm::vec3(0, 0, 1), glm::vec2(0.66f, 1.f)));
    vertices.push_back( Triangle( upC, glm::vec3(1, 1, 0), glm::vec2(0.33f, 0.5f)));


    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Triangle), vertices.data(), GL_STATIC_DRAW);

    //Debind du glBindBufer (second paramètre à 0)
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    // Ajout ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


    uint32_t indices[] = {
            0, 1, 2,//faceSup
            0, 2, 3,
            8, 10, 9,//face droite
            8, 9, 11,
            //0, 4, 7,//
            //0, 7, 3,
            12, 14, 13,//
            12, 13, 15,
            //1, 2, 6,//
            //1, 6, 5,
            4, 5, 6,//
            4, 6, 7
    };

    // => On remplit l'IBO avec les indices:
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(uint32_t), indices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &vao);

    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);

    // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
    // cela a pour effet d'enregistrer l'IBO dans le VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    //activation des attributs de vertex, prend en para l'index renseignant le type de data
    //on prefere les déclarer auparavant dans des constantes plutot que en clair
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_UV= 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_UV);


    //on rebind vbo pour lui indiquer lequel il doit utiliser
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Triangle), (const GLvoid*)( offsetof(Triangle, pos) ) );
    glVertexAttribPointer(VERTEX_ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Triangle), (const GLvoid*)( offsetof(Triangle, uv) ) );

    glBindBuffer(GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);

}

Cube3D::Cube3D(int type){
    //charge les shaders que l'on a ajouté dans le dossier shaders
    std::unique_ptr<Image> image;


    //image = loadImage("C:/Users/Owen/Desktop/opengl projet/OPEN_GL/dungeonGL/assets/textures/Cube.jpg");

    image = loadImage("C:/Users/Owen/Desktop/opengl projet/OPEN_GL/dungeonGL/assets/textures/texturepack.png");

    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture( GL_TEXTURE_2D, texture );
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, image->getWidth(), image->getHeight(), 0, GL_RGBA ,GL_FLOAT, image->getPixels());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    FilePath applicationPath(".\\opengl.exe");
    Program program = loadProgram(applicationPath.dirPath() + "\\..\\..\\shaders\\CubeTex.vs.glsl",
                                  applicationPath.dirPath() + "\\..\\..\\shaders\\CubeTex.fs.glsl");
    program.use();
    // Matrice de transformation
    this->uModelMatrixID = glGetUniformLocation( program.getGLId(), "MVP" );

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glDepthMask(GL_FALSE);


    /*********************************
     * HERE SHOULD COME THE INITIALIZATION CODE
     *********************************/

    //glGenBuffers(GLsizei n, Gluint*buffers); créer un buffer (nb vbo à créer, pointer id vbo)
    GLuint vbo;
    glGenBuffers(1, &vbo); //vbo affecté directement

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    float unit = 0.5f;
    BBox3f box( glm::vec3(-unit,-unit,-unit), glm::vec3(unit,unit,unit) );

    glm::vec3 upA( box.upper.x, box.upper.y, box.upper.z );
    glm::vec3 upB( box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 upC( -box.upper.x, box.upper.y, -box.upper.z );
    glm::vec3 upD( -box.upper.x, box.upper.y, box.upper.z );

    glm::vec3 lowA( box.upper.x, -box.upper.y, box.upper.z  );
    glm::vec3 lowB( box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 lowC( -box.upper.x, -box.upper.y, -box.upper.z );
    glm::vec3 lowD( -box.upper.x, -box.upper.y, box.upper.z );

    std::vector<Triangle> vertices;
    //TOP
    vertices.push_back( Triangle( upA, glm::vec3(1, 0, 0), glm::vec2(1.f, 0.f)));//0
    vertices.push_back( Triangle( upB, glm::vec3(1, 1, 0), glm::vec2(1.f, 0.33f)));//1
    vertices.push_back( Triangle( upC, glm::vec3(1, 1, 1), glm::vec2(0.66f, 0.33f)));//2
    vertices.push_back( Triangle( upD, glm::vec3(0, 1, 1), glm::vec2(0.66f, 0.f)));//3

    //BOT
    vertices.push_back( Triangle( lowA, glm::vec3(0, 0, 1), glm::vec2(0.33f, 0.33f)));//4
    vertices.push_back( Triangle( lowB, glm::vec3(1, 0, 1), glm::vec2(0.33f, 0.66f)));//5
    vertices.push_back( Triangle( lowC, glm::vec3(1, 1, 0), glm::vec2(0.f , 0.66f)));//6
    vertices.push_back( Triangle( lowD, glm::vec3(1, 0, 0), glm::vec2(0.f, 0.33f)));//7

    //RIGHT
    vertices.push_back( Triangle( upA, glm::vec3(1, 0, 0), glm::vec2(1.f, 0.33f)));//8
    vertices.push_back( Triangle( lowB, glm::vec3(1, 0, 1), glm::vec2(0.66f, 0.66f)));//9
    vertices.push_back( Triangle( lowA, glm::vec3(0, 0, 1), glm::vec2(1.f, 0.66f)));//10
    vertices.push_back( Triangle( upB, glm::vec3(1, 1, 0), glm::vec2(0.66f, 0.33f)));//11

    //LEFT
    vertices.push_back( Triangle( upD, glm::vec3(1, 0, 0), glm::vec2(0.66f, 0.33f)));//12
    vertices.push_back( Triangle( lowC, glm::vec3(1, 0, 1), glm::vec2(0.33f, 0.66f)));//13
    vertices.push_back( Triangle( lowD, glm::vec3(0, 0, 1), glm::vec2(0.66f, 0.66f)));//14
    vertices.push_back( Triangle( upC, glm::vec3(1, 1, 0), glm::vec2(0.33f, 0.33f)));//15

    //BACK
    vertices.push_back( Triangle( upD, glm::vec3(1, 0, 0), glm::vec2(0.33f, 0.f)));//16
    vertices.push_back( Triangle( lowA, glm::vec3(1, 0, 1), glm::vec2(0.66f, 0.33f)));//17
    vertices.push_back( Triangle( lowD, glm::vec3(0, 0, 1), glm::vec2(0.33f, 0.33f)));//18
    vertices.push_back( Triangle( upA, glm::vec3(1, 1, 0), glm::vec2(0.66f, 0.f)));//19

    //EXIT
    vertices.push_back( Triangle( upD, glm::vec3(1, 0, 0), glm::vec2(0.66f, 0.66f)));//20
    vertices.push_back( Triangle( lowA, glm::vec3(1, 0, 1), glm::vec2(1.f, 1.f)));//21
    vertices.push_back( Triangle( lowD, glm::vec3(0, 0, 1), glm::vec2(0.66f, 1.f)));//22
    vertices.push_back( Triangle( upA, glm::vec3(1, 1, 0), glm::vec2(1.f, 0.66f)));//23

    //MICRO
    vertices.push_back( Triangle( upD, glm::vec3(1, 0, 0), glm::vec2(0.15f, 0.93f)));//24
    vertices.push_back( Triangle( lowA, glm::vec3(1, 0, 1), glm::vec2(0.19f, 1.f)));//25
    vertices.push_back( Triangle( lowD, glm::vec3(0, 0, 1), glm::vec2(0.15f, 1.f)));//26
    vertices.push_back( Triangle( upA, glm::vec3(1, 1, 0), glm::vec2(0.19f, 0.93f)));//27

    //ENNEMI
    vertices.push_back( Triangle( upD, glm::vec3(1, 0, 0), glm::vec2(0.33f, 0.66f)));//28
    vertices.push_back( Triangle( lowA, glm::vec3(1, 0, 1), glm::vec2(0.66f, 1.f)));//29
    vertices.push_back( Triangle( lowD, glm::vec3(0, 0, 1), glm::vec2(0.33f, 1.f)));//30
    vertices.push_back( Triangle( upA, glm::vec3(1, 1, 0), glm::vec2(0.66f, 0.66f)));//31

    glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(Triangle), vertices.data(), GL_STATIC_DRAW);

    //Debind du glBindBufer (second paramètre à 0)
    glBindBuffer(GL_ARRAY_BUFFER, 0 );

    // Ajout ibo
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    if(type == 1){
        uint32_t indices[] = {
                0, 1, 2,//faceSup
                0, 2, 3,
                8, 10, 9,//face droite
                8, 9, 11,
                  //0, 4, 7,//
                  //0, 7, 3,
                12, 14, 13,//
                12, 13, 15,
                //1, 2, 6,//
                //1, 6, 5,
                4, 5, 6,//
                4, 6, 7
        };
        // => On remplit l'IBO avec les indices:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 30 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if(type == 2){
        uint32_t indices[] = {
                0, 1, 2,//faceSup
                0, 2, 3,
                8, 10, 9,//face droite
                8, 9, 11,
                19, 16, 18,//
                19, 18, 17,
                //3, 7, 6,//
                //3, 6, 2,

                //1, 2, 6,//
                //1, 6, 5,

                4, 5, 6,//
                4, 6, 7
        };
        // => On remplit l'IBO avec les indices:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if(type == 3){
        uint32_t indices[] = {
                0, 1, 2,//faceSup
                0, 2, 3,
                8, 10, 9,//face droite
                8, 9, 11,
                19, 16, 18,//
                19, 18, 17,
                12, 14, 13,//
                12, 13, 15,

                //1, 2, 6,//
                //1, 6, 5,

                4, 5, 6,//
                4, 6, 7
        };
        // => On remplit l'IBO avec les indices:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if(type == 4){
        uint32_t indices[] = {
                27, 24, 26,//
                27, 26, 25,
        };
        // => On remplit l'IBO avec les indices:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if(type == 5){
        uint32_t indices[] = {
                31, 28, 30,//
                31, 30, 29,
        };
        // => On remplit l'IBO avec les indices:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    if(type == 6){
        uint32_t indices[] = {
                0, 1, 2,//faceSup
                0, 2, 3,
                8, 10, 9,//face droite
                8, 9, 11,
                23, 20, 22,//
                23, 22, 21,
                12, 14, 13,//
                12, 13, 15,

                //1, 2, 6,//
                //1, 6, 5,

                4, 5, 6,//
                4, 6, 7
        };
        // => On remplit l'IBO avec les indices:
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, 24 * sizeof(uint32_t), indices, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    glGenVertexArrays(1, &vao);

    //binding du vao : pas de cible car une seule cible possible pour vao
    glBindVertexArray(vao);

    // => On bind l'IBO sur GL_ELEMENT_ARRAY_BUFFER; puisqu'un VAO est actuellement bindé,
    // cela a pour effet d'enregistrer l'IBO dans le VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

    //activation des attributs de vertex, prend en para l'index renseignant le type de data
    //on prefere les déclarer auparavant dans des constantes plutot que en clair
    const GLuint VERTEX_ATTR_POSITION = 0;
    const GLuint VERTEX_ATTR_UV= 1;
    glEnableVertexAttribArray(VERTEX_ATTR_POSITION);
    glEnableVertexAttribArray(VERTEX_ATTR_UV);


    //on rebind vbo pour lui indiquer lequel il doit utiliser
    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glVertexAttribPointer(VERTEX_ATTR_POSITION, 3, GL_FLOAT, GL_FALSE, sizeof(Triangle), (const GLvoid*)( offsetof(Triangle, pos) ) );
    glVertexAttribPointer(VERTEX_ATTR_UV, 2, GL_FLOAT, GL_FALSE, sizeof(Triangle), (const GLvoid*)( offsetof(Triangle, uv) ) );

    glBindBuffer(GL_ARRAY_BUFFER, 0 );
    glBindVertexArray(0);

}

void Cube3D::draw() {

    /*********************************
    * HERE SHOULD COME THE RENDERING CODE
    *********************************/

    glm::mat4 projMatrix;
    projMatrix = glm::perspective<float>(glm::radians(70.f),1.0,0.1f,100.f);
    // Transformations
    modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;
    glUniformMatrix4fv( uModelMatrixID, 1, GL_FALSE, glm::value_ptr(projMatrix * modelMatrix) );
    // !!! 4fv !!!

    //Dessiner avec le VAO
    glBindVertexArray(vao);

    //glDrawArrays(GL_TRIANGLES, 0, 3); // avant ibo
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}