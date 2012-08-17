#RKMultiplayer Sample Project


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