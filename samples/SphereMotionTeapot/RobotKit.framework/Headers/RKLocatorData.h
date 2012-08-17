//
//  RKLocatorData.h
//  RobotKit
//
//  Created by Michael DePhillips on 7/10/12.
//  Copyright (c) 2012 Orbotix Inc. All rights reserved.
//

/*! @file */

#import <Foundation/Foundation.h>
#import <RobotKit/RKSensorData.h>

/*!
 * @brief Structure for locator values.
 *
 * Structure with the position x and y value
 */
struct RKLocatorPosition {
    float x; /*!< The x position of the locator (in cm) */
    float y;  /*!< The y position of the locator (in cm) */
};

/*! Type for a the locator position structure. */
typedef struct RKLocatorPosition RKLocatorPosition;

/*!
 * @brief Structure for locator values.
 *
 * Structure with the position x and y value
 */
struct RKLocatorVelocity {
    float x; /*!< The x velocity of the locator (in cm/s) */
    float y;  /*!< The y velocity of the locator (in cm/s) */
};

/*! Type for a the locator position structure. */
typedef struct RKLocatorVelocity RKLocatorVelocity;

/*!
 * @brief Structure of BOOL values that indicate which locator values are valid
 * Structure whose members indicate which of position and velocity values are valid.
 */
struct RKLocatorState {
    BOOL locatorXValid; /*!< Indicates if the locator x position is value. */
    BOOL locatorYValid; /*!< Indicates if the locator y position is value. */
    BOOL locatoryVelocityXValid; /*!< Indicates if the locator velocity y is valid */
    BOOL locatorVelocityYValid; /*!< Indicates if the locator velocity y is valid */
};

/*! Type for the Locator state structure. */
typedef struct RKLocatorState RKLocatorState;

/*!
 * @brief Class to represent samples of locator data.
 *
 * Class that contains structures to the locator data received from data 
 * streaming. Data streaming can be set to return x-position, y-position,
 * x-velocity, or y-velocity.  You can stream any and all of these values.
 *
 * @sa RKSetDataStreamingCommand.
 * @sa RKConfigureLocatorCommand.
 */
@interface RKLocatorData : RKSensorData {
    @private
    RKLocatorPosition   position;  // Position of device x and y
    RKLocatorVelocity   velocity;  // Velocity of device x and y
    RKLocatorState      state;     // State which shows which variables are valid
}

/*! Read only property to access the locator x and y position (in cm) */
@property (nonatomic, readonly) RKLocatorPosition position;
/*! Read only property to access the locator x and y velocity (in cm/s) */
@property (nonatomic, readonly) RKLocatorVelocity velocity; 
/*! Read only property to a structure to use to test which locator values are valid */
@property (nonatomic, readonly) RKLocatorState state;


@end
