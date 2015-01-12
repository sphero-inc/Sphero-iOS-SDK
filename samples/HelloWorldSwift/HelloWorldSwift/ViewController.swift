//
//  Copyright (c) 2011-2014 orbotix. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    var robot: RKConvenienceRobot!
    var ledON = false
    
    @IBOutlet var connectionLabel: UILabel!

    override func viewDidLoad() {
        super.viewDidLoad()
       
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "appWillResignActive:", name: UIApplicationWillResignActiveNotification, object: nil)
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "appDidBecomeActive:", name: UIApplicationDidBecomeActiveNotification, object: nil)
        
        RKRobotDiscoveryAgent.sharedAgent().addNotificationObserver(self, selector: "handleRobotStateChangeNotification:")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        
        connectionLabel = nil;
    }

    required init(coder aDecoder: NSCoder) {
        
        super.init(coder: aDecoder)
    }
    
    @IBAction func sleepButtonTapped(sender: AnyObject) {
        if let robot = self.robot {
            connectionLabel.text = "Sleeping"
            robot.sleep()
        }
    }
    
    func appWillResignActive(note: NSNotification) {
        RKRobotDiscoveryAgent.disconnectAll()
        stopDiscovery()
    }
    
    func appDidBecomeActive(note: NSNotification) {
        startDiscovery()
    }
    
    func handleRobotStateChangeNotification(notification: RKRobotChangedStateNotification) {
        let noteRobot = notification.robot
        
        switch (notification.type) {
        case .Connecting:
            connectionLabel.text = "\(notification.robot.name()) Connecting"
            break
        case .Online:
            let conveniencerobot = RKConvenienceRobot(robot: noteRobot);
            
            if (UIApplication.sharedApplication().applicationState != .Active) {
                conveniencerobot.disconnect()
            } else {
                self.robot = RKConvenienceRobot(robot: noteRobot);
                
                connectionLabel.text = noteRobot.name()
                togleLED()
            }
            break
        case .Disconnected:
            connectionLabel.text = "Disconnected"
            startDiscovery()
            robot = nil;
            
            break
        default:
            NSLog("State change with state: \(notification.type)")
        }
    }
    
    func startDiscovery() {
        connectionLabel.text = "Discovering Robots"
        RKRobotDiscoveryAgent.startDiscovery()
    }
    
    func stopDiscovery() {
        RKRobotDiscoveryAgent.stopDiscovery()
    }
    
    func togleLED() {
        if let robot = self.robot {
            if (ledON) {
                robot.setLEDWithRed(0.0, green: 0.0, blue: 0.0)
            } else {
                robot.setLEDWithRed(0.0, green: 0.0, blue: 1.0)
            }
            ledON = !ledON
            
            var delay = Int64(0.5 * Float(NSEC_PER_SEC))
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, delay), dispatch_get_main_queue(), { () -> Void in
                self.togleLED();
            })
        }
    }
}

