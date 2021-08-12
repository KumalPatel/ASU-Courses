//
//  SecondViewController.swift
//  Lab2
//
//  Created by Kumal Patel on 9/10/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class SecondViewController: UIViewController {
    var EarthWeight:Int?
    @IBOutlet weak var EarthL: UILabel!
    @IBOutlet weak var MoonL: UILabel!
    @IBOutlet weak var display: UILabel!
    @IBOutlet weak var titleL: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        EarthL.text = "Your weight in Earth is \(EarthWeight!)"
        MoonL.text = "Youur weight on Moon is \(getMoonWeight())"
        display.text = "I feel much lighter !"
    }

    func getMoonWeight()->Int
    {
        // Moon's gravity is 1/6th of Earth's gravity
        let moonWeight = Float(EarthWeight!) / 6.0
        let tempWeight = Int(moonWeight)
        let remainder = moonWeight.truncatingRemainder(dividingBy: Float(tempWeight))
        
        
        if remainder <= 0.5 // round down
        {
            return Int(moonWeight.rounded(.down))
        }
        else // round up
        {
            return Int(moonWeight.rounded(.up))
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?)
    {
        if let des = segue.destination as? ThirdViewController
        {
            des.eWeight = EarthWeight
            des.mWeight = getMoonWeight()
        }
    }
    
    @IBAction func returnedtoMoon(segue: UIStoryboardSegue)
    {
        if let des = segue.source as? ThirdViewController
        {
            titleL.text = "Coming from the Jupiter"
        }
    }
}
