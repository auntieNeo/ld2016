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

#ifndef LD2016_COMMON_ANIMATED_OBJECT_H_
#define LD2016_COMMON_ANIMATED_OBJECT_H_

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"

#include "glError.h"
#include "shaderProgram.h"
#include "shaders.h"

#include "sceneObject.h"

namespace ld2016 {
  class AnimatedObject : public SceneObject {
    private:
      typedef struct {
        float pos[3];
        float norm[3];
        float tex[2];
        float weights[4];
        int bones[4];
      } MeshVertex;

      typedef struct Node {
        struct Node *children;
        unsigned int numChildren;
      } Node;

      GLuint m_vertexBuffer, m_indexBuffer, m_texture;
      float m_time, m_lastTime;
      int m_numIndices;

      void m_loadMesh(const std::string &meshFile);
      void m_loadTexture(const std::string &textureFile);

      void m_updateBoneMatrices(float time);
      void m_traverseNodeHierarchy(
          const aiNode *node,
          const aiMesh *mesh,
          glm::mat4 transform,
          int level);

      static glm::mat4 m_aiMatrixToGlmMat(const aiMatrix4x4 &in);

      void m_drawSurface(
          const glm::mat4 &modelView,
          const glm::mat4 &projection);
    public:
      AnimatedObject(
          const std::string &meshFile,
          const std::string &textureFile);
      virtual ~AnimatedObject();

      virtual void tick(float dt);

      virtual void draw(const glm::mat4 &modelWorld,
          const glm::mat4 &worldView, const glm::mat4 &projection,
          float alpha, bool debug);
  };
}

#endif
