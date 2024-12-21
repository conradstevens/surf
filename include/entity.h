#ifndef ENTITY_H
#define ENTITY_H
#include "shader.h"
#include "mesh.h"


class entity {

public:

    Shader shader;
    Mesh mesh;
    entity();

protected:
    virtual Shader initShader();
    virtual Mesh initMesh();


};



#endif //ENTITY_H
