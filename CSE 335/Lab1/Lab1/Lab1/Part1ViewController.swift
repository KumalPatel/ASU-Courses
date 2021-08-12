//
//  Part1ViewController.swift
//  Lab1
//
//  Created by Kumal Patel on 9/4/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class Part1ViewController: UIViewController {
    @IBOutlet weak var bmiValue: UILabel!
    @IBOutlet weak var displayMsg: UILabel!
    @IBOutlet weak var height: UITextField!
    @IBOutlet weak var weight: UITextField!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.bmiValue.isHidden = true
        self.displayMsg.isHidden = true
        
        // Do any additional setup after loading the view.
    }
    
    @IBAction func CalculateBMI(_ sender: Any) {
        let userheight = Int(self.height.text!) ?? 0
        let userweight = Float(self.weight.text!) ?? 0
        
        let calculatedValue = ((userweight / Float ((userheight * userheight))) * 703)
        self.bmiValue.text = "\(calculatedValue)"
        
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
        
        self.bmiValue.isHidden = false
        self.displayMsg.isHidden = false
    }
    
    /*
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // Get the new view controller using segue.destination.
        // Pass the selected object to the new view controller.
    }
    */

}
