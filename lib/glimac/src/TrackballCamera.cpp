#include <cmath>
#include "glimac/glm.hpp"
#include "glimac/TrackballCamera.hpp"

#define M_PI 3.14159265358979323846264338327

namespace glimac {

    TrackballCamera::TrackballCamera() : m_fDistance(0), m_fAngleX(0), m_fAngleY(0)
    {
    }

    void TrackballCamera::moveFront(float delta)
    {
        m_fDistance -= delta;
    }

    void TrackballCamera::rotateLeft(float degrees)
    {
        float radians = degrees / 180 * M_PI;
        m_fAngleY += radians;
    }
    void TrackballCamera::rotateUp(float degrees)
    {
        float radians = degrees / 180 * M_PI;
        m_fAngleX += radians;
    }
    glm::mat4 TrackballCamera::getViewMatrix() const
    {
        glm::mat4 result = glm::translate(glm::mat4(1), glm::vec3(0, 0, -m_fDistance));

        result = glm::rotate(result, m_fAngleX, glm::vec3(1, 0, 0));
        result = glm::rotate(result, m_fAngleY, glm::vec3(0, 1, 0));
        return (result);
    }

}
