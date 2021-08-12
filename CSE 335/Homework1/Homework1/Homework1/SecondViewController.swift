//
//  SecondViewController.swift
//  Homework1
//
//  Created by Kumal Patel on 10/17/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit
import CoreData

class SecondViewController: UIViewController, UITextViewDelegate {
        
    var managedObjectContext: NSManagedObjectContext?
    var MVC:Model?
    var list:[DailyHealth]?
    
    @IBOutlet weak var sblood: UITextField!
    @IBOutlet weak var dblood: UITextField!
    @IBOutlet weak var weight: UITextField!
    @IBOutlet weak var sugarlevel: UITextField!
    @IBOutlet weak var symptoms: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        symptoms.delegate = self
        fetchData()
    }
    
    func fetchData() {
        do {
            self.list = try managedObjectContext!.fetch(DailyHealth.fetchRequest())
        }
        catch {
        }
    }
    
    //delegate function
    func textViewDidBeginEditing(_ textView: UITextView) {
        symptoms.text = ""
    }
    
    @IBAction func addData(_ sender: Any) {
        // clear data from core data if list array passes 1 week
        if(list!.count > 7) {
            MVC?.clearData()
            
            // display alert that data was cleared
            let alert = UIAlertController(title: "Error: Records Full", message: "Data Entries Cleared!", preferredStyle: .alert)
            alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
            self.present(alert, animated: true, completion: nil)
            
            // update list to data from core data
              fetchData()
              
              // clear all textfields
              sblood.text = ""
              dblood.text = ""
              weight.text = ""
              sugarlevel.text = ""
              symptoms.text = "Describe any other symptoms you have"
        }
        else {
            // add data to core data
            if let sbloodT = Int64(sblood.text!), let dbloodT = Int64(dblood.text!),
                let weightT = Int64(weight.text!), let sugarlevelT = Int64(sugarlevel.text!),
                let symptomsT = symptoms.text{
                
                // save data to core data
                MVC?.SaveContext(sBlood_: sbloodT, dBlood_: dbloodT, weight_: weightT, sugarLevel_: sugarlevelT, symptoms_: symptomsT)
                
                // display alert that entry was saved
                let alert = UIAlertController(title: "", message: "Entry Saved!", preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
                self.present(alert, animated: true, completion: nil)
                
                // update list to data from core data
                fetchData()
                
                // clear all textfields
                sblood.text = ""
                dblood.text = ""
                weight.text = ""
                sugarlevel.text = ""
                symptoms.text = "Describe any other symptoms you have"
            }
            else {
                // if data types do not match or textfields are empty add alert to user
                let alert = UIAlertController(title: "Error", message: "Invalid Data Types", preferredStyle: .alert)
                alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
                self.present(alert, animated: true, completion: nil)
                
            }
        }
    }
    

}
