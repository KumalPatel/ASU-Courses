//
//  Part2ViewController.swift
//  Lab1
//
//  Created by Kumal Patel on 9/4/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class Part2ViewController: UIViewController {
    @IBOutlet weak var HSlider: UISlider!
    @IBOutlet weak var HLabel: UILabel!
    @IBOutlet weak var WSlider: UISlider!
    @IBOutlet weak var WLabel: UILabel!
    @IBOutlet weak var BMIValue: UILabel!
    @IBOutlet weak var displayMsg: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.BMIValue.isHidden = true
        self.displayMsg.isHidden = true
        // Do any additional setup after loading the view.
    }
    

    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

    @IBAction func HeightSlider(_ sender: Any) {
        HLabel.text = "\(HSlider.value)"
        //let calculatedValue = ((userweight / Float ((userheight * userheight))) * 703)
        let calculatedValue = ((WSlider.value / (HSlider.value * HSlider.value)) * 703)
        self.BMIValue.text = "\(calculatedValue)"
        
        if calculatedValue < 18 {
            self.displayMsg.text = "You are Underweight"
            displayMsg.textColor = UIColor.blue
        }
        else if calculatedValue >= 18 && calculatedValue < 25 {
            self.displayMsg.text = "You are Normal"
            displayMsg.textColor = UIColor.green
        }
        else if calculatedValue >= 25 && calculatedValue <= 30 {
            self.displayMsg.text = "You are Pre-obese"
            displayMsg.textColor = UIColor.purple
        }
        else if calculatedValue > 30 {
            self.displayMsg.text = "You are Obese"
            displayMsg.textColor = UIColor.red
        }
        else{
            self.displayMsg.text = "Error: Unknown BMI"
        }
        
        self.BMIValue.isHidden = false
        self.displayMsg.isHidden = false
    }
    
    
    @IBAction func WeightSlider(_ sender: Any) {
        WLabel.text = "\(WSlider.value)"
        let calculatedValue = ((WSlider.value / (HSlider.value * HSlider.value)) * 703)
        self.BMIValue.text = "\(calculatedValue)"
        
        if calculatedValue < 18 {
            self.displayMsg.text = "You are Underweight"
            displayMsg.textColor = UIColor.blue
        }
        else if calculatedValue >= 18 && calculatedValue < 25 {
            self.displayMsg.text = "You are Normal"
            displayMsg.textColor = UIColor.green
        }
        else if calculatedValue >= 25 && calculatedValue <= 30 {
            self.displayMsg.text = "You are Pre-obese"
            displayMsg.textColor = UIColor.purple
        }
        else if calculatedValue > 30 {
            self.displayMsg.text = "You are Obese"
            displayMsg.textColor = UIColor.red
        }
        else{
            self.displayMsg.text = "Error: Unknown BMI"
        }
        
        self.BMIValue.isHidden = false
        self.displayMsg.isHidden = false
    }
}
