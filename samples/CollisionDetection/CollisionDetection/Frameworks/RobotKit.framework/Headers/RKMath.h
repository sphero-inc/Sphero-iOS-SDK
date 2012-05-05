/*
//  RKMath.h
//  RobotKit
 *
 *  Created by Brian Smith on 12/6/10.
 *  Copyright 2010 Orbotix Inc. All rights reserved.
 *
 */

/*! @file */

/*!
 *  Calculates the normal value of a 2D vector. The algorithm is 
 *  \f$\sqrt(x^2 + y^2)\f$.
 *  @param x The x coordinate.
 *  @param y The y coordinate.
 */
extern double Norm2D(double x, double y);

/*!
 *  Calculate the normal value of a 3D vector. The algorithm used is 
 *  \f$\sqrt(x^2 + y^2 + z^2)\f$.
 *  @param x The x coordinate.
 *  @param y The y coordinate.
 *  @param z The z coordinate.
 */
extern double Norm3D(double x, double y, double z);

/*!
 * Function to clamp a value to minimum and maximum values.
 * @param v The value to clamp.
 * @param min The minimum value that v can go to.
 * @param max The maximum value that v can go to.
 */
extern double Clamp(double v, double min, double max);
 
/*!
 * Function to set a window on a value to keep it at a fixed value
 * within the window's delta.
 * @param v The value to keep within the window.
 * @param fixed The value fix to if the value is within the window's delta.
 * @param delta The delta to keep the value to the fixed value.
 */
extern double Window(double v, double fixed, double delta);
