//
//  MacroCommand.h
//  MacroLab
//
//  Created by Jon Carroll on 9/11/11.
//  Copyright (c) 2011 Orbotix, Inc. All rights reserved.
//


#import <Foundation/Foundation.h>

/*! @file */

/*!
 *  @brief Base class that represents a macro command
 *
 *  This is a base class that all macro command classes should subclass.
 *  This class should not be used directly.
 */
@interface RKMacroCommand : NSObject {
    
}

/*! Initialize a new command with the given binary command data
 *  @param data Binary data the command will be initialized from.
 *  @return A new instance of the macro command initialized from data
 */
-(RKMacroCommand*)initWithBytes:(NSData*)data;

/*! @return a human readable description of the command and parameters. */
-(NSString*)description;

/*! @return a binary byte representation for the command */
-(NSData*)getByteRepresentation;

/*! @return the length of the command in bytes */
-(int)length;

/*! @return human readable name of the command */
-(NSString*)name;

@end
