//
//  ViewController.swift
//  OvalSampleSwift
//
//  Created by Corey Earwood on 6/22/15.
//  Copyright (c) 2015 Orbotix. All rights reserved.
//

import UIKit

class ViewController: UIViewController, RKOvalControlDelegate, UITextFieldDelegate {
    var robot: RKConvenienceRobot!
    var ovalControl: RKOvalControl!
    @IBOutlet var lightSpeed: UITextField!

    override func viewDidLoad() {
        super.viewDidLoad()
        
        let tap = UITapGestureRecognizer(target:self, action:#selector(hideKeyboard));
        tap.cancelsTouchesInView = false;
        self.view.addGestureRecognizer(tap);
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        RKRobotDiscoveryAgent.shared().addNotificationObserver(self, selector: #selector(handleRobotStateChangeNotification(_:)))
    }
    
    override func awakeFromNib() {
        super.awakeFromNib()
        NotificationCenter.default.addObserver(self, selector: #selector(appDidBecomeActive(_:)), name: NSNotification.Name.UIApplicationDidBecomeActive, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(appWillResignActive(_:)), name: NSNotification.Name.UIApplicationWillResignActive, object: nil)
    }
    
    func appDidBecomeActive(_: Notification) {
        RKRobotDiscoveryAgent.startDiscovery()
    }
    
    func appWillResignActive(_: Notification) {
        RKRobotDiscoveryAgent.disconnectAll()
    }

    func handleRobotStateChangeNotification(_ notification: RKRobotChangedStateNotification) {
        switch (notification.type) {
        case .online:
            self.robot = RKConvenienceRobot(robot: notification.robot)
            self.ovalControl = RKOvalControl(robot: notification.robot, delegate: self)
        case .disconnected:
            self.robot = nil
            self.ovalControl = nil
        default:
            break
        }
    }
    
    func sendOvalProgram() {
        guard let path = Bundle.main.path(forResource: "Sample", ofType: "oval") else {
            return
        }
        
        var source: String? = nil
        do {
            source = try String(contentsOfFile: path, encoding: String.Encoding.utf8)
            if let unwrappedSource = source {
                self.ovalControl.sendOvalPrograms([unwrappedSource])
            }
        } catch let error as NSError {
            debugPrint("Error: \(error)")
        }
    }
    
    func hideKeyboard() {
        self.view.endEditing(true);
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        hideKeyboard();
        return true;
    }
    
    @IBAction func updateOval(_ sender: AnyObject?) {
        self.ovalControl.sendOvalString("speed = \(lightSpeed.text!);...")
    }
    
    //MARK: RKOvalControlDelegate
    
    func ovalControlDidInitialize(_ control: RKOvalControl!) {
        self.ovalControl.resetOvmAndLibrary(true)
    }
    
    func ovalControlDidFinishSendingProgram(_ control: RKOvalControl!) {
        debugPrint("Oval successfully sent")
    }
    
    func ovalControlDidResetOvm(_ control: RKOvalControl!) {
        debugPrint("OVM Reset")
        sendOvalProgram()
    }
    
    func ovalControl(_ control: RKOvalControl!, receivedOvalNotification notification: RKOvalDeviceBroadcast!) {
        debugPrint("Did receive oval async with floats: \(notification.floats) ints: \(notification.ints)")
    }
    
    func ovalControl(_ control: RKOvalControl!, receivedVmRuntimeError notification: RKOvalErrorBroadcast!) {
        debugPrint("Did receive OVM Error: \(notification.errorDescription())")
    }
    
    func ovalControl(_ control: RKOvalControl!, didFailToSendProgramWithMessage message: String!) {
        debugPrint("Failed to send program with message: \(message)")
    }
}

