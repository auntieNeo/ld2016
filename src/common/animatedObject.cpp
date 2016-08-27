/*
 * Copyright (c) 2016 Jonathan Glines, Galen Cochrane
 * Jonathan Glines <jonathan@glines.net>
 * Galen Cochrane <galencochrane@gmail.com>
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

#include <cstdlib>

#include "debug.h"

#include "animatedObject.h"

namespace ld2016 {
  AnimatedObject::AnimatedObject(
      const std::string &meshFile,
      const std::string &textureFile)
  {
    // Load the mesh from file using assimp
    m_loadMesh(meshFile);
    // Load the texture from file using SDL2
    m_loadTexture(textureFile);
  }

  AnimatedObject::~AnimatedObject() {
  }

  void AnimatedObject::m_loadMesh(const std::string &meshFile) {
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
      for (int j = 0; j < 4; ++j) {
        vertices[i].weights[j] = 0.0f;
        vertices[i].bones[j] = -1;
      }
    }
    // Collect the bone weights with the most influence
    for (int i = 0; i < aim->mNumBones; ++i) {
      auto bone = aim->mBones[i];
      fprintf(stderr, "Bone name: '%s'\n",
          bone->mName.C_Str());
      for (int j = 0; j < bone->mNumWeights; ++j) {
        auto vertexId = bone->mWeights[j].mVertexId;
        auto weight = bone->mWeights[j].mWeight;
        auto vertex = &vertices[vertexId];
        // Look at all of this vertex's existing bone weights
        for (int k = 0; k < 4; ++k) {
          if (vertex->weights[k] < weight) {
            // Insert this bone into this position
            for (int l = 3; l > k; --l) {
              vertex->weights[l] = vertex->weights[l - 1];
              vertex->bones[l] = vertex->bones[l - 1];
            }
            vertex->weights[k] = weight;
            vertex->bones[k] = i;
            break;
          }
        }
      }
    }
    // XXX: Print out the vertices for debugging
    /*
    for (int i = 0; i < aim->mNumVertices; ++i) {
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
      fprintf(stderr,
          "  bones:\n");
      for (int j = 0; j < 4; ++j) {
        fprintf(stderr,
            "    bone[%d]: %g\n",
            vertices[i].bones[j],
            vertices[i].weights[j]);
      }
    }
    */
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
    // Copy the face data into an index buffer
    uint32_t *indices = new uint32_t[3 * aim->mNumFaces];
    for (int i = 0; i < aim->mNumFaces; ++i) {
      assert(aim->mFaces[i].mNumIndices == 3);
      indices[i * 3] = aim->mFaces[i].mIndices[0];
      indices[i * 3 + 1] = aim->mFaces[i].mIndices[1];
      indices[i * 3 + 2] = aim->mFaces[i].mIndices[2];
    }
    // Copy the index data to the GL
    glGenBuffers(1, &m_indexBuffer);
    FORCE_ASSERT_GL_ERROR();
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    FORCE_ASSERT_GL_ERROR();
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,  // target
        sizeof(uint32_t) * 3 * aim->mNumFaces,  // size
        indices,  // data
        GL_STATIC_DRAW  // usage
        );
    FORCE_ASSERT_GL_ERROR();
    delete[] indices;
    m_numIndices = aim->mNumFaces * 3;
    // TODO: Store all of the animations, including all channels of each
    // animation
    // TODO: Read the animation into a buffer
    // TODO: Recursively traverse the scene nodes
    m_traverseNodeHierarchy(scene->mRootNode, aim, glm::mat4(1.0f), 0);
  }

  void AnimatedObject::m_traverseNodeHierarchy(
      const aiNode *node,
      const aiMesh *mesh,
      glm::mat4 transform,
      int level)
  {
    fprintf(stderr, "node: %s\n", node->mName.C_Str());
    transform *= m_aiMatrixToGlmMat(node->mTransformation);

    glm::vec3 start, end;
    start = glm::vec3(transform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    end = glm::vec3(transform * glm::vec4(0.1f, 0.0f, 0.0f, 1.0f));
    Debug::drawLine(start, end, glm::vec3(1.0f, 1.0f, 0.0f));

    /* TODO: Look for the bone that uses this node */
    for (int i = 0; i < mesh->mNumBones; ++i) {
      auto bone = mesh->mBones[i];
      if (strcmp(node->mName.C_Str(), bone->mName.C_Str()) == 0) {
        fprintf(stderr, "bone: %s\n",
            bone->mName.C_Str());
      }
    }
    for (int i = 0; i < node->mNumChildren; ++i) {
      m_traverseNodeHierarchy(node->mChildren[i], mesh, transform, level + 1);
    }
  }

  glm::mat4 AnimatedObject::m_aiMatrixToGlmMat(const aiMatrix4x4 &in) {
    glm::mat4 out;
    out[0][0] = in.a1;
    out[1][0] = in.a2;
    out[2][0] = in.a3;
    out[3][0] = in.a4;
    out[0][1] = in.b1;
    out[1][1] = in.b2;
    out[2][1] = in.b3;
    out[3][1] = in.b4;
    out[0][2] = in.c1;
    out[1][2] = in.c2;
    out[2][2] = in.c3;
    out[3][2] = in.c4;
    out[0][3] = in.d1;
    out[1][3] = in.d2;
    out[2][3] = in.d3;
    out[3][3] = in.d4;
    return out;
  }

  void AnimatedObject::m_loadTexture(const std::string &textureFile) {
    int x, y, n;
    uint8_t* data = stbi_load(textureFile.c_str(), &x, &y, &n, 0);
    if (!data) {
      fprintf(stderr, "Failed to load texture file '%s'.\n",
          textureFile.c_str());
    }
    // Create the texture object in the GL
    glGenTextures(1, &m_texture);
    FORCE_ASSERT_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, m_texture);
    FORCE_ASSERT_GL_ERROR();
    // Copy the image to the GL
    glTexImage2D(
        GL_TEXTURE_2D,  // target
        0,  // level
        GL_RGBA,  // internal format
        x,  // width
        y,  // height
        0,  // border
        GL_RGBA,  // format
        GL_UNSIGNED_BYTE,  // type
        data  // data
        );
    FORCE_ASSERT_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    FORCE_ASSERT_GL_ERROR();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    FORCE_ASSERT_GL_ERROR();
    stbi_image_free(data);
  }

  void AnimatedObject::m_updateBoneMatrices(float time) {
    // TODO: Traverse the bone hierarchy
  }

  void AnimatedObject::m_drawSurface(
      const glm::mat4 &modelView,
      const glm::mat4 &projection)
  {
    // Use a simple shader
    auto shader = Shaders::textureShader();
    shader->use();

    // Prepare the uniform values
    assert(shader->modelViewLocation() != -1);
    glUniformMatrix4fv(
        shader->modelViewLocation(),  // location
        1,  // count
        0,  // transpose
        glm::value_ptr(modelView)  // value
        );
    ASSERT_GL_ERROR();
    assert(shader->projectionLocation() != -1);
    glUniformMatrix4fv(
        shader->projectionLocation(),  // location
        1,  // count
        0,  // transpose
        glm::value_ptr(projection)  // value
        );
    ASSERT_GL_ERROR();

    /*
    // Prepare the texture sampler
    assert(shader->texture0() != -1);
    glUniform1i(
        shader->texture0(),  // location
        0  // value
        );
    ASSERT_GL_ERROR();
    glActiveTexture(GL_TEXTURE0);
    ASSERT_GL_ERROR();
    glBindTexture(GL_TEXTURE_2D, m_texture);
    ASSERT_GL_ERROR();
    */

    // Prepare the vertex attributes
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
    ASSERT_GL_ERROR();
    assert(shader->vertPositionLocation() != -1);
    glEnableVertexAttribArray(shader->vertPositionLocation());
    ASSERT_GL_ERROR();
    glVertexAttribPointer(
        shader->vertPositionLocation(),  // index
        3,  // size
        GL_FLOAT,  // type
        0,  // normalized
        sizeof(MeshVertex),  // stride
        &(((MeshVertex *)0)->pos[0])  // pointer
        );
    ASSERT_GL_ERROR();
    /*
    assert(shader->vertNormalLocation() != -1);
    glEnableVertexAttribArray(shader->vertNormalLocation());
    ASSERT_GL_ERROR();
    glVertexAttribPointer(
        shader->vertNormalLocation(),  // index
        3,  // size
        GL_FLOAT,  // type
        0,  // normalized
        sizeof(MeshVertex),  // stride
        &(((MeshVertex *)0)->norm[0])  // pointer
        );
    ASSERT_GL_ERROR();
    */
    assert(shader->vertTexCoordLocation() != -1);
    glEnableVertexAttribArray(shader->vertTexCoordLocation());
    ASSERT_GL_ERROR();
    glVertexAttribPointer(
        shader->vertTexCoordLocation(),  // index
        2,  // size
        GL_FLOAT,  // type
        0,  // normalized
        sizeof(MeshVertex),  // stride
        &(((MeshVertex *)0)->tex[0])  // pointer
        );
    ASSERT_GL_ERROR();

    // Draw the surface
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
    ASSERT_GL_ERROR();
    glDrawElements(
        GL_TRIANGLES,  // mode
        m_numIndices,  // count
        GL_UNSIGNED_INT,  // type
        0  // indices
        );
    ASSERT_GL_ERROR();
  }

  void AnimatedObject::tick(float dt) {
    m_lastTime = m_time;
    m_time += dt;
  }

  void AnimatedObject::draw(const glm::mat4 &modelWorld,
      const glm::mat4 &worldView, const glm::mat4 &projection,
      float alpha, bool debug)
  {
    glm::mat4 modelView = worldView * modelWorld;

    m_updateBoneMatrices(
        (1.0f - alpha) * m_lastTime + alpha * m_time);
    m_drawSurface(modelView, projection);
  }
}
