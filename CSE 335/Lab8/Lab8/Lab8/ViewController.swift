//
//  ViewController.swift
//  Lab8
//
//  Created by Kumal Patel on 11/15/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var leftArrow: UIButton!
    @IBOutlet weak var upArrow: UIButton!
    @IBOutlet weak var rightArrow: UIButton!
    @IBOutlet weak var downArrow: UIButton!
    @IBOutlet weak var monkey: UIImageView!
    @IBOutlet weak var apple: UIImageView!
    @IBOutlet weak var apple2: UIImageView!
    @IBOutlet weak var apple3: UIImageView!
    @IBOutlet weak var apple4: UIImageView!
    @IBOutlet weak var timerVal: UILabel!
    @IBOutlet weak var status: UILabel!
    
    // timer
    var timer : Timer?
    var counter = 0
    
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        // clip buttons
        clipButton(arrow: self.leftArrow)
        clipButton(arrow: self.upArrow)
        clipButton(arrow: self.rightArrow)
        clipButton(arrow: self.downArrow)
        
        // rotation buttons
        rotateButton(arrow: self.upArrow, degrees: CGFloat(90*(Double.pi/180)))
        rotateButton(arrow: self.rightArrow, degrees: CGFloat(180*(Double.pi/180)))
        rotateButton(arrow: self.downArrow, degrees: CGFloat(270*(Double.pi/180)))
        
        // timer
        timer = Timer();
        timer = Timer.scheduledTimer(timeInterval: 1, target: self, selector: #selector(ViewController.count), userInfo: nil, repeats: true)
        
        // hide winner/loser text
        status.isHidden = true
    }

    func clipButton(arrow: UIButton) {
        arrow.layer.cornerRadius = arrow.bounds.width / 2
        arrow.clipsToBounds = true
    }
    
    func rotateButton(arrow: UIButton, degrees: CGFloat) {
        arrow.transform = CGAffineTransform(rotationAngle: degrees)
    }
    
    func imagesIntersects(firstFrame: UIView, secondFrame: UIView) -> Bool {
        return firstFrame.frame.intersects(secondFrame.frame)
    }
    
    @objc func count() {
        counter += 1
        timerVal.text = String(counter)
        
        endCount(time: counter, apple: apple, apple2: apple2, apple3: apple3, apple4: apple4)
        
    }
    
    func endCount(time: Int, apple: UIImageView, apple2: UIImageView, apple3: UIImageView, apple4: UIImageView) {
        if((apple.isHidden) && (apple2.isHidden) && (apple3.isHidden) && (apple4.isHidden)) {
            timer?.invalidate()
            
            // hide everything on view
            monkey.isHidden = true
            leftArrow.isHidden = true
            upArrow.isHidden = true
            downArrow.isHidden = true
            rightArrow.isHidden = true
            timerVal.isHidden = true
            
            // decide if winner or loser
            if(time <= 10) {
                status.isHidden = false
                status.text = "WINNER"
                status.textColor = UIColor.green
            }
            else {
                status.isHidden = false
                status.text = "LOSER"
                status.textColor = UIColor.red
            }
        }
    }
    
    @IBAction func up(_ sender: Any) {
        var frame = self.monkey.frame
        frame.origin.y -= 10
        self.monkey.frame = frame
        
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple)) {
            apple.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple2)) {
            apple2.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple3)) {
            apple3.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple4)) {
            apple4.isHidden = true
        }
    }
    
    @IBAction func down(_ sender: Any) {
        var frame = self.monkey.frame
        frame.origin.y += 10
        self.monkey.frame = frame
        
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple)) {
            apple.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple2)) {
            apple2.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple3)) {
            apple3.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple4)) {
            apple4.isHidden = true
        }
    }
    
    @IBAction func left(_ sender: Any) {
        var frame = self.monkey.frame
        frame.origin.x -= 10
        self.monkey.frame = frame
        
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple)) {
            apple.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple2)) {
            apple2.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple3)) {
            apple3.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple4)) {
            apple4.isHidden = true
        }
    }
    @IBAction func right(_ sender: Any) {
        var frame = self.monkey.frame
        frame.origin.x += 10
        self.monkey.frame = frame
        
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple)) {
            apple.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple2)) {
            apple2.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple3)) {
            apple3.isHidden = true
        }
        if(imagesIntersects(firstFrame: monkey, secondFrame: apple4)) {
            apple4.isHidden = true
        }
    }
}

