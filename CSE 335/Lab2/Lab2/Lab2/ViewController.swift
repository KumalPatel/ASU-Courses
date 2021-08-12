//
//  ViewController.swift
//  Lab2
//
//  Created by Kumal Patel on 9/10/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class ViewController: UIViewController {

    @IBOutlet weak var weight: UITextField!
    @IBOutlet weak var Ephoto: UIImageView!
    @IBOutlet weak var display: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        let des = segue.destination as! SecondViewController
            des.EarthWeight = Int(weight.text!) ?? 0
        
    }
    
    @IBAction func returnedtoEarth(segue: UIStoryboardSegue)
    {
        if let sourceViewController = segue.source as? SecondViewController
        {
            display.text = "Coming from the Moon"
        }
        else
        {
            display.text = "Coming from the Jupiter"
        }
    }
    
}

