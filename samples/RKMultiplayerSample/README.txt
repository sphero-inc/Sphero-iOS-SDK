                    _______  _______  ______   _______ __________________         
                   (  ___  )(  ____ )(  ___ \ (  ___  )\__   __/\__   __/|\     /|
                   | (   ) || (    )|| (   ) )| (   ) |   ) (      ) (   ( \   / )
                   | |   | || (____)|| (__/ / | |   | |   | |      | |    \ (_) / 
                   | |   | ||     __)|  __ (  | |   | |   | |      | |     ) _ (  
                   | |   | || (\ (   | (  \ \ | |   | |   | |      | |    / ( ) \ 
                   | (___) || ) \ \__| )___) )| (___) |   | |   ___) (___( /   \ )
                   (_______)|/   \__/|/ \___/ (_______)   )_(   \_______/|/     \|

MMMM77777777777777777777777ZMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMM77777777NMMMMMMMM7777777NMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMM777777MMMMMMMMMMMMMMM7I7777MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMM77777MMMMMMMMMMMMMMMMMMM77777MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MM7777$MMMMMMMMMMMMMMMMMMMMM87777MMMMMMMMMMMMMMMMMMMMMMMMMMMM77MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MD7777MMMMMMMMMMMMMMMMMMMMMMM7777IMMMMMMMMMMMMMMMMMMMMMMMMMMM77MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
M7777MMMMMMMMM8777DMMMMMMMMMMM7777MMMMMMMMM7777MMMMMN7I77MMMM77M7777MMMMMMMII7$NMMMMMMO$8MMM$I77OMMM
N777OMMMMMMMM7777777MMMM777MMMM777$MMMMMM$77777$MMM77777777MM777I77777MMM77I777$7NMM77777MI7777I778M
7777MMMMMMMMM7777777MMM77777MMM7777MMMMMM77MMMMMMM77MMMMM$77M77MMMMM77OM77MMMM$777M77NMMM778MMMMM77M
7777MMMMMMMMM7777777MMM77777MMM7777MMMMMMMI77778MM77MMMMMM77M77MMMMMM77M77$77777NMM77MMMM77MMMMMM877
7777MMMMMMMMM7777777MMM77777MMM7777MMMMMMMMMMM77$M77MMMMM777M77MMMMMM77M777ZMMMM7MM77MMMM778MMMMM77M
M777ZMMMMMMMM777777ZMMMM777MMMM777ZMMMMMM777DD77NM777777777MM77MMMMMM77MM777I7777MM77MMMMM77777I77NM
M7777MMMMMMMMMZ7778MMMMMMMMMMM7777MMMMMMMM$7777NMM77N7777MMMM77MMMMMMINMMMM7777MMMM$7MMMMMMM7777DMMM
M87777MMMMMMMMMMMMMMMMMMMMMMM$7777MMMMMMMMMMMMMMMM77MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MM$7777MMMMMMMMMMMMMMMMMMMMMO7777MMMMMMMMMMMMMMMMM7$MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMM77777MMMMMMMMMMMMMMMMMMM77777MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMI77777MMMMMMMMMMMMMMM$7777$MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMM77777I$MMMMMMMMM$I777778MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMN7777777777777777777ZMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMM$77777777777777MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM
MMMMMMMMMMMMMMMMZ7$DMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM

README.txt
RKMultiplayer Sample Project
Platform: iOS
Version: 0.1
Requirements: RobotKit version 1.1 or higher
Copyright 2012 Orbotix, Inc.

Description:
This application demonstrates using the cross platform multiplayer library that is built in the
robot kit.  This example shows how to advertise a game, setup a connection and pass messages between
players in the session.  

The set name button allows you to change the human readable name that the device will advertise to
other players.  Pressing the plus button on the main interface will create and advertise a game
that other players can join.  Available games will be listed on the main screen.  Tapping on the
name of a game will cause the device to join that game.

Once in a game a list of players is shown in the top right and various buttons appear allowing the
game state to change.  Some game state changes can only be initiated by the 'host' or game creator.
A chat area at the bottom of the interface demonstrates passing messages between players. A label
in the top left shows the current state of the game as shown by the RKMultiplayerGameState.
Pressing the back or the home button will cause a player to leave the game.

Explanation of game states:
Lobby - In this state the game is being advertised and other players can join.
Started - In this state no other players can join and the game isn't advertised. Pause allowed.
Paused - This state is provided as a convenience for developers and is only entered explicitly.
Ended - In this state the game has ended and all connections to remote players have been closed.

This example does not demonstrate remote robot control, a more advanced feature of the multiplayer 
library. See the sample code "Two Phones One Ball" for an example of this.
