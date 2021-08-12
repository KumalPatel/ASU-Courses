//
//  ThirdViewController.swift
//  Lab2
//
//  Created by Kumal Patel on 9/11/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class ThirdViewController: UIViewController {
    var eWeight:Int?
    var mWeight:Int?
    @IBOutlet weak var eLabel: UILabel!
    @IBOutlet weak var mLabel: UILabel!
    @IBOutlet weak var jLabel: UILabel!
    @IBOutlet weak var status: UILabel!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        eLabel.text = "Your weight in Earth is \(eWeight!)"
        mLabel.text = "Your weight on Moon is \(mWeight!)"
        jLabel.text = "Your weight on Jupiter is \(getJupiterWeight())"
        status.text = "I feel heavier!"
        
    }
    func getJupiterWeight()->Int
    {
        let JupiterWeight = Float(eWeight!) * 2.4
        let temp = Int(JupiterWeight)
        let remainder = JupiterWeight.truncatingRemainder(dividingBy: Float(temp))
        
        if remainder <= 0.5
        {
            return Int(JupiterWeight.rounded(.down))
        }
        else
        {
            return Int(JupiterWeight.rounded(.up))
        }
    }
}
