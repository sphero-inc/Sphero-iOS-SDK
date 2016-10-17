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
       
        NotificationCenter.default.addObserver(self, selector: #selector(ViewController.appWillResignActive(note:)), name: NSNotification.Name.UIApplicationWillResignActive, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(ViewController.appDidBecomeActive(note:)), name: NSNotification.Name.UIApplicationDidBecomeActive, object: nil)
        
        RKRobotDiscoveryAgent.shared().addNotificationObserver(self, selector: #selector(ViewController.handleRobotStateChangeNotification(notification:)))
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        
        connectionLabel = nil;
    }

    required init?(coder aDecoder: NSCoder) {
        
        super.init(coder: aDecoder)
    }
    
    @IBAction func sleepButtonTapped(sender: AnyObject) {
        if let robot = self.robot {
            connectionLabel.text = "Sleeping"
            robot.sleep()
        }
    }
    
    func appWillResignActive(note: Notification) {
        RKRobotDiscoveryAgent.disconnectAll()
        stopDiscovery()
    }
    
    func appDidBecomeActive(note: Notification) {
        startDiscovery()
    }
    
    func handleRobotStateChangeNotification(notification: RKRobotChangedStateNotification) {
        let noteRobot = notification.robot
        
        switch (notification.type) {
        case .connecting:
            connectionLabel.text = "\(notification.robot.name()) Connecting"
            break
        case .online:
            let conveniencerobot = RKConvenienceRobot(robot: noteRobot);
            
            if (UIApplication.shared.applicationState != .active) {
                conveniencerobot?.disconnect()
            } else {
                self.robot = RKConvenienceRobot(robot: noteRobot);
                
                connectionLabel.text = noteRobot?.name()
                togleLED()
            }
            break
        case .disconnected:
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
            
            let delay = Int64(0.5 * Float(NSEC_PER_SEC))
            DispatchQueue.main.asyncAfter(deadline: DispatchTime.now() + Double(delay) / Double(NSEC_PER_SEC), execute: { () -> Void in
                self.togleLED();
            })
        }
    }
}

