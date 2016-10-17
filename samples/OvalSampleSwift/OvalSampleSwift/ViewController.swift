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
        // Do any additional setup after loading the view, typically from a nib.
        let tap:UITapGestureRecognizer = UITapGestureRecognizer(target:self, action:#selector(ViewController.hideKeyboard));
        tap.cancelsTouchesInView = false;
        self.view.addGestureRecognizer(tap);
    }
    
    override func viewDidAppear(_ animated: Bool) {
        super.viewDidAppear(animated)
        
        RKRobotDiscoveryAgent.shared().addNotificationObserver(self, selector: #selector(ViewController.handleRobotStateChangeNotification(_:)))
    }

    override func didReceiveMemoryWarning() {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func awakeFromNib() {
        NotificationCenter.default.addObserver(self, selector: #selector(ViewController.appDidBecomeActive(_:)), name: NSNotification.Name.UIApplicationDidBecomeActive, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(ViewController.appWillResignActive(_:)), name: NSNotification.Name.UIApplicationWillResignActive, object: nil)
    }
    
    func appDidBecomeActive(_ notification: Notification) {
        RKRobotDiscoveryAgent.startDiscovery()
    }
    
    func appWillResignActive(_ notification: Notification) {
        RKRobotDiscoveryAgent.disconnectAll()
    }

    func handleRobotStateChangeNotification(_ notification: RKRobotChangedStateNotification) {
        switch (notification.type) {
        case .online:
            self.robot = RKConvenienceRobot(robot: notification.robot)
            self.ovalControl = RKOvalControl(robot: notification.robot, delegate: self)
            break
        case .disconnected:
            self.robot = nil
            self.ovalControl = nil
            break
        default:
            break
        }
    }
    
    func sendOvalProgram() {
        let path:String = Bundle.main.path(forResource: "Sample", ofType: "oval")!
        let source = try? String(contentsOfFile: path, encoding: String.Encoding.utf8)
        if let unwrappedSource = source {
            self.ovalControl.sendOvalPrograms([unwrappedSource])
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
        NSLog("Oval successfully sent")
    }
    
    func ovalControlDidResetOvm(_ control: RKOvalControl!) {
        NSLog("OVM Reset")
        sendOvalProgram()
    }
    
    func ovalControl(_ control: RKOvalControl!, receivedOvalNotification notification: RKOvalDeviceBroadcast!) {
        NSLog("Did receive oval async with floats: \(notification.floats) ints: \(notification.ints)")
    }
    
    func ovalControl(_ control: RKOvalControl!, receivedVmRuntimeError notification: RKOvalErrorBroadcast!) {
        NSLog("Did receive OVM Error: \(notification.errorDescription())")
    }
    
    func ovalControl(_ control: RKOvalControl!, didFailToSendProgramWithMessage message: String!) {
        NSLog("Failed to send program with message: \(message)")
    }
}

