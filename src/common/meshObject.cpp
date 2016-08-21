/*
 * Copyright (c) 2016 Jonathan Glines
 * Jonathan Glines <jonathan@glines.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "glError.h"

#include "meshObject.h"

namespace ld2016 {
  MeshObject::MeshObject(const std::string &meshFile) {
    // TODO: Load the mesh from file using assimp
    m_loadMesh(meshFile);
  }

  void MeshObject::m_loadMesh(const std::string &meshFile) {
    Assimp::Importer importer;
    auto scene = importer.ReadFile(
        meshFile,
        aiProcess_Triangulate
        );

    if (!scene) {
      fprintf(stderr, "Failed to load mesh from file: '%s'\n",
          meshFile.c_str());
    }
    if (scene->mNumMeshes != 1) {
      fprintf(stderr, "Mesh file '%s' must contain a single mesh",
          meshFile.c_str());
    }
    auto aim = scene->mMeshes[0];
    if (aim->mNormals == NULL) {
      fprintf(stderr, "Error: No normals in mesh '%s'\n",
          meshFile.c_str());
    }
    if (!aim->HasTextureCoords(0)) {
      fprintf(stderr, "Error: No texture coordinates in mesh '%s'\n",
          meshFile.c_str());
    }

    // Copy the mesh vertices into a buffer with the appropriate format
    MeshVertex *vertices = new MeshVertex[aim->mNumVertices];
    for (int i = 0; i < aim->mNumVertices; ++i) {
      vertices[i].pos[0] = aim->mVertices[i].x;
      vertices[i].pos[1] = aim->mVertices[i].y;
      vertices[i].pos[2] = aim->mVertices[i].z;
      vertices[i].norm[0] = aim->mNormals[i].x;
      vertices[i].norm[1] = aim->mNormals[i].y;
      vertices[i].norm[2] = aim->mNormals[i].z;
      vertices[i].tex[0] = aim->mTextureCoords[0][i].x;
      vertices[i].tex[1] = aim->mTextureCoords[0][i].y;
      fprintf(stderr,
          "vertices[%d]:\n"
          "  pos: (%g, %g, %g)\n"
          "  norm: (%g, %g, %g)\n"
          "  tex: (%g, %g)\n",
          i,
          vertices[i].pos[0],
          vertices[i].pos[1],
          vertices[i].pos[2],
          vertices[i].norm[0],
          vertices[i].norm[1],
          vertices[i].norm[2],
          vertices[i].tex[0],
          vertices[i].tex[1]);
    }
    // Copy the vertices buffer to the GL
    glGenBuffers(1, &m_vertexBuffer);
    FORCE_ASSERT_GL_ERROR();
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    FORCE_ASSERT_GL_ERROR();
    glBufferData(
        GL_ARRAY_BUFFER,  // target
        sizeof(MeshVertex) * aim->mNumVertices,  // size
        vertices,  // data
        GL_STATIC_DRAW  // usage
        );
    FORCE_ASSERT_GL_ERROR();
    delete[] vertices;
  }

  MeshObject::~MeshObject() {
  }
}
