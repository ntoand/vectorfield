#ifndef __TERRAIN_H__
#define __TERRAIN_H__

#include <vector>
#include <string>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/rotate_vector.hpp>

using std::vector;
using std::string;

#include "Material.h"
#include "Mesh.h"

struct ControlPoint {
    glm::vec2 pos;
    glm::vec2 value;
};

enum ParticleState {
    STATE_ALIVE,
    STATE_DYING,
    STATE_DEAD
};

struct Particle {
    ParticleState state;
    glm::vec3 pos;
    glm::vec4 color;
    float opaque;
    Particle() {
        state = STATE_DEAD;
        pos = glm::vec3(0);
        color = glm::vec4(1.0);
        opaque = 0;
    }
};

namespace vectorfield {
    
    /**
     Tessellation terrain
     */
    class VectorField {
        
    private:
        bool m_updated;
        bool m_initialized;
        
        vector<ControlPoint> m_controlPoints;
        vector<Mesh*> m_meshControlPoints;
        vector<Mesh*> m_meshTest;
        
        //2d grid
        glm::vec2 m_gridMin, m_gridMax;
        float m_gridHeight;
        float m_cellSize;
        int m_gridSizeX, m_gridSizeZ;
        vector<glm::vec2> m_gridValues;
        
        //particles
        int m_maxParticles;
        int m_lastUsedParticle;
        vector<Particle> m_particleContainer;
        float m_curOffset;
        //to render
        int m_numActiveParticles;
        vector<glm::vec3> m_activeVertices;
        vector<glm::vec4> m_activeColors;
        float m_pointScale;
        
        //display
        unsigned int m_vbo[2];
        unsigned int m_vao;
        glm::vec2 m_lengthRange;
        Material* m_material;
        
    private:
        glm::vec4 calColor(float value);
        glm::vec2 calGridValue(int x, int z, float power = 2, float smoothing = 0);
        //particles
        int findUnusedParticle();
        void simulateParticles();
        //render
        void setup();
        
    public:
        VectorField();
        ~VectorField();
        
        void init(float min_x, float min_z, float max_x, float max_z, float cell_size, float height = 0);
        void printInfo();
        
        void addControlPoint(const float px, const float pz,
                             const float vx, const float vz);
        
        void setPointScale(float ps) { m_pointScale = ps; }
        void update();
        void render(const float MV[16], const float P[16]);
    };
    
}; //namespace vectorfield

#endif
