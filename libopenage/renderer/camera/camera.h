// Copyright 2022-2022 the openage authors. See copying.md for legal info.

#pragma once

#include <eigen3/Eigen/Dense>

#include "util/vector.h"

namespace openage::renderer::camera {

/**
 * Maximum possible zoom in level.
 * 
 * Has to be above 0.0f, otherwise we get zero division errors.
 */
static const float MAX_ZOOM_IN = 0.05f;

class Camera {
public:
	/**
     * Create a new camera for the renderer.
     * 
     * The camera uses default values. Its centered on the origin of the scene (0.0f, 0.0f, 0.0f)
     * and has a zoom level of 1.0f.
     *
     * @param viewport_size Initial viewport size of the camera (width x height).
     */
	Camera(util::Vector2s viewport_size);

	/**
     * Create a new camera for the renderer.
     *
     * @param viewport_size Viewport size of the camera (width x height).
     * @param scene_pos Position of the camera in the scene.
     * @param zoom Zoom level of the camera (defaults to 1.0f).
     */
	Camera(util::Vector2s viewport_size,
	       Eigen::Vector3f scene_pos,
	       float zoom = 1.0f);
	~Camera() = default;

	/**
     * Move the camera so that the center of its viewpoint points
     * to the given position in the 3D scene.
     *
     * @param scene_pos Position in the 3D scene that the camera should center on.
     */
	void look_at_scene(Eigen::Vector3f scene_pos);

	/**
     * Move the camera so that the center of its viewpoint points
     * to the given ingame coordinates.
     *
     * @param scene_pos Position of the ingame coordinates that the camera should center on.
     */
	void look_at_coord(util::Vector3f coord_pos);

	/**
     * Move the camera position in the direction of a given vector.
     *
     * @param direction Direction vector. Added to the current position.
     * @param delta Delta for controlling the amount by which the camera is moved. The
     *              value is multiplied with the directional vector before its applied to
     *              the positional vector.
     */
	void move(Eigen::Vector3f direction, float delta = 1.0f);

	/**
      * Set the zoom level of the camera. Values smaller than 1.0f let the
      * camera zoom in, values greater than 1.0f let the camera zoom out.
      * 
      * The max zoom in value is 0.05f. Passing values lower than that
      * will just set the zoom level to max zoom.
      * 
      * For incremental zooming, use the \p zoom_in() and \p zoom_out()
      * methods.
      * 
      * @param zoom New zoom level.
      */
	void set_zoom(float zoom);

	/**
      * Zoom into the scene by an incremental value.
      * 
      * @param zoom_delta 
      */
	void zoom_in(float zoom_delta);

	void zoom_out(float zoom_delta);

	/**
	 * Resize the camera viewport.
	 *
	 * @param width New width of the viewport.
	 * @param height New height of the viewport.
	 */
	void resize(size_t width, size_t height);

	/**
      * Get the view matrix for this camera.
      * 
      * @return Camera view matrix.
      */
	Eigen::Matrix4f get_view_matrix();

	/**
      * Get the projection matrix for this camera.
      * 
      * @return Camera projection matrix.
      */
	Eigen::Matrix4f get_projection_matrix();

private:
	/**
     * Position in the 3D scene.
     */
	Eigen::Vector3f scene_pos;

	/**
     * Size of the camera viewport.
     */
	util::Vector2s viewport_size;

	/**
      * Zoom level.
      * 
      * 0.0f < z < 1.0f => zoom in
      * z = 1.0f        => default view
      * z > 1.0f        => zoom out
      */
	float zoom;
};

} // namespace openage::renderer::camera