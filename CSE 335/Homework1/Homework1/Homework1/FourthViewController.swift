//
//  FourthViewController.swift
//  Homework1
//
//  Created by Kumal Patel on 10/18/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit
import CoreData

class FourthViewController: UIViewController {

    var managedObjectContext: NSManagedObjectContext?
    var MVC:Model?
    var list:[DailyHealth]?
    
    @IBOutlet weak var msg: UITextView!
    @IBOutlet weak var bloodLbl: UILabel!
    @IBOutlet weak var weightLbl: UILabel!
    @IBOutlet weak var sugarLbl: UILabel!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        fetchData()
        
        // clear textview
        msg.text = ""
        
        // initally set labels to good and green
        bloodLbl.text = ""
        weightLbl.text = ""
        sugarLbl.text = ""

        
        if(list?.count != 7) {
            // display alert that the full week entries has not been filled
            let alert = UIAlertController(title: "Error", message: "Not Enough Entries", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
        }
        else {
            // initally set labels to good and green
            bloodLbl.text = "Good"
            weightLbl.text = "Good"
            sugarLbl.text = "Good"
            bloodLbl.textColor = UIColor.green
            weightLbl.textColor = UIColor.green
            sugarLbl.textColor = UIColor.green
            
            avgWeight()
            highSugarLevel()
            highBloodPressure()
            
            if(msg.text == "") {
                msg.text = "You are in good health, keep up the work \u{1F600}"
            }
        }
    }
    
    func fetchData() {
        do {
          self.list = try managedObjectContext!.fetch(DailyHealth.fetchRequest())
        }
        catch {
        }
    }
    
    func avgWeight() {
        // find avg weight in last 4 days
        var avgFirst:Int64 = 0
        var avgLast:Int64 = 0
        
        for (key, value) in list!.enumerated() {
            if (key < 3) {
                avgFirst += value.weight
            }
            else {
                avgLast += value.weight
            }
        }
        
        let floatFirst:Float = Float(avgFirst) / 3
        let floatLast:Float = Float(avgLast) / 4
        
        let tempFirst = Int(floatFirst)
        let tempLast = Int(floatLast)
        
        let remainderFirst = floatFirst.truncatingRemainder(dividingBy: Float(tempFirst))
        let remainderLast = floatLast.truncatingRemainder(dividingBy: Float(tempLast))
        
        if remainderFirst <= 0.5 {
            avgFirst = Int64(floatFirst.rounded(.down))
        }
        else {
            avgFirst = Int64(floatFirst.rounded(.up))
        }
        
        if remainderLast <= 0.5 {
            avgLast = Int64(floatLast.rounded(.down))
        }
        else {
            avgLast = Int64(floatLast.rounded(.up))
        }
                    
        // if avgLast > avgFirst, print warning
        if(avgLast > avgFirst) {
            msg.text.append("\nYou are gaining weight!")
            weightLbl.text = "High"
            weightLbl.textColor = UIColor.red
        }
    }
    
    func highSugarLevel() {
        // find current and prev sugar level
        var currLevel:Int64 = 0
        var prevLevel:Int64 = 0
        
        for (key, value) in list!.enumerated() {
            if(key == 5) { // 6th day
                prevLevel = value.sugarLevel
            }
            else if(key == 6) { // last day
                currLevel = value.sugarLevel
            }
        }
        
        let temp:Float = Float(prevLevel) * 0.10

        if(temp == Float(currLevel)) { // curr is 10% higher
            msg.text.append("\nYour sugar level is high!")
            sugarLbl.text = "High"
            sugarLbl.textColor = UIColor.red
        }
    }
    
    func highBloodPressure() {
        // find blood pressure for current and previous
        var currSblood:Int64 = 0
        var currDblood:Int64 = 0
        var prevSblood:Int64 = 0
        var prevDblood:Int64 = 0
        
        for (key, value) in list!.enumerated() {
            if(key == 5) {
                prevSblood = value.sBlood
                prevDblood = value.dBlood
            }
            else if(key == 6) {
                currSblood = value.sBlood
                currDblood = value.dBlood
            }
        }
        
        let tempS:Float = Float(prevSblood) * 0.10
        let tempD:Float = Float(prevDblood) * 0.10
        
        if(tempS == Float(currSblood)) {
            msg.text.append("\nYour blood pressure is high!")
            bloodLbl.text = "High"
            bloodLbl.textColor = UIColor.red
        }
        else if(tempD == Float(currDblood)) {
            msg.text.append("\nYour blood pressure is high!")
            bloodLbl.text = "High"
            bloodLbl.textColor = UIColor.red
        }
    }
    
    
   

}
