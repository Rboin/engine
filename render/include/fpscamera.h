#ifndef FPSCAMERA_H
#define FPSCAMERA_H

#include "camera.h"

class FPSCamera : public Camera
{
public:
  /**
   * An implementation of the abstract Camera class. Creates a First Person perspective camera.
   * @brief FPSCamera
   * @param p
   * @param v
   */
  FPSCamera(const projection_information &p, glm::vec3 position);

  /**
   * Updates the position and rotation vertices, limits the
   * pitch to the interval [-89, 89] and resets the buffer
   * variables.
   * @brief update
   * @param delta A float representing the delta time in seconds.
   */
  void update(const double delta) override;

  /**
   * Determines the current orientation (based on the rotation vector)
   * in 3D space.
   * @brief getOrientation
   * @return A glm::mat4 (rotation matrix) containing the current
   * orientation.
   */
  glm::mat4 getRotation() const override;

  /**
   * Updates the view matrix using a translation matrix that uses
   * the negative position and a rotation matrix obtained by
   * FPSCamera::getOrientation().
   * @brief updateViewMatrix
   */
  void updateViewMatrix() override;

  /**
   * Updates the projection matrix using the given width and height values.
   * Constructs the projection matrix using glm::perspective.
   * @brief updateProjectionMatrix
   * @param width
   * @param height
   */
  void updateProjectionMatrix(const int width, const int height) override;

  //TODO: Give FPSCamera ref to PlayableEntity and make it update the entity's positions when the camera has been updated.
};

#endif // FPSCAMERA_H
