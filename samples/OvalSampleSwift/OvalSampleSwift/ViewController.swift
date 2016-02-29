//
//  ViewController.swift
//  OvalSampleSwift
//
//  Created by Corey Earwood on 6/22/15.
//  Copyright (c) 2015 Orbotix. All rights reserved.
//

import UIKit

class ViewController: UIViewController, RKOvalControlDelegate {
    var robot: RKConvenienceRobot!
    var ovalControl: RKOvalControl!
    @IBOutlet var lightSpeed: UITextField!

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewDidAppear(animated: Bool) {
        super.viewDidAppear(animated)
        
        RKRobotDiscoveryAgent.sharedAgent().addNotificationObserver(self, selector: "handleRobotStateChangeNotification:")
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func awakeFromNib() {
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "appDidBecomeActive:", name: UIApplicationDidBecomeActiveNotification, object: nil)
        NSNotificationCenter.defaultCenter().addObserver(self, selector: "appWillResignActive:", name: UIApplicationWillResignActiveNotification, object: nil)
    }
    
    func appDidBecomeActive(notification: NSNotification) {
        RKRobotDiscoveryAgent.startDiscovery()
    }
    
    func appWillResignActive(notification: NSNotification) {
        RKRobotDiscoveryAgent.disconnectAll()
    }

    func handleRobotStateChangeNotification(notification: RKRobotChangedStateNotification) {
        switch (notification.type) {
        case .Online:
            self.robot = RKConvenienceRobot(robot: notification.robot)
            self.ovalControl = RKOvalControl(robot: notification.robot, delegate: self)
            self.ovalControl.resetOvmAndLibrary(true) //Reset the OVM. The OVM can run without a connection so this ensures we start from a blank state
            sendOvalProgram()
            break
        case .Disconnected:
            self.robot = nil
            self.ovalControl = nil
            break
        default:
            break
        }
    }
    
    func sendOvalProgram() {
        do {
            let source = try NSString(contentsOfFile: NSBundle.mainBundle().pathForResource("Sample", ofType: "oval")!, encoding: NSUTF8StringEncoding)
            self.ovalControl.sendOvalPrograms([source])
        } catch let error as NSError {
            print(error.localizedDescription)
        }

    }
    
    @IBAction func updateOval(sender: AnyObject?) {
        self.ovalControl.sendOvalString("speed = \(lightSpeed.text);...")
    }
    
    //MARK: RKOvalControlDelegate
    
    func ovalControlDidFinishSendingProgram(control: RKOvalControl!) {
        NSLog("Oval successfully sent")
    }
    
    func ovalControlDidResetOvm(control: RKOvalControl!) {
        NSLog("OVM Reset")
    }
    
    func ovalControl(control: RKOvalControl!, receivedOvalNotification notification: RKOvalDeviceBroadcast!) {
        NSLog("Did receive oval async with floats: \(notification.floats) ints: \(notification.ints)")
    }
    
    func ovalControl(control: RKOvalControl!, receivedVmRuntimeError notification: RKOvalErrorBroadcast!) {
        NSLog("Did receive OVM Error: \(notification.errorDescription())")
    }
    
    func ovalControl(control: RKOvalControl!, didFailToSendProgramWithMessage message: String!) {
        NSLog("Failed to send program with message: \(message)")
    }
}

