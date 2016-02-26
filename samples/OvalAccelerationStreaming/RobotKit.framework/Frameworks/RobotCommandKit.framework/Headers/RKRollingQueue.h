//
//  RKRollingQueue.h
//  RobotCommandKit
//
//  Borrowed from CelloHill by wes on 11/14/14.
//  Copyright (c) 2014 Orbotix Inc. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface RKRollingQueue : NSObject

/*! @brief The maximum size for the rolling queue. */
@property ( nonatomic, assign) int maxSize;

/*! @brief Create a new rolling queue with the given maximum size.
 * @param maxSize The maximum size of the rolling queue.
 */
- (id) initWithMaxSize:(int) maxSize;

/*! @brief Add an object to the queue.
 * @param sample The sample to enqueue.
 */
- (void) enqueue:(id) obj;

/*! @brief Remove and return the next object in the queue */
- (id) dequeue;

/*! @brief Peek at the next object in the queue without removing it. */
- (id) peek;

/*! @brief Fetch the previously added (enqueued) object */
- (id) prev;

/*! @brief Determine the number of objects in the sample queue. */
- (int) count;

/*! @brief Get the data in the queue as an array. */
- (NSArray *) dataset;

/*! @brief Get the data in the queue as a reversed array. */
- (NSArray *) invertedDataset;


@end
