//
//  ViewController.swift
//  Homework1
//
//  Created by Kumal Patel on 10/17/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit
import CoreData

class ViewController: UIViewController {
    
    // Reference the managed object context
    let managedObjectContext = (UIApplication.shared.delegate as! AppDelegate).persistentContainer.viewContext
    
    // Model for Core Data functionality
    var MVC:Model?
    
    var list:[DailyHealth]?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        MVC = Model(context: managedObjectContext)
        fetchData()
    }
  
    func fetchData() {
        do {
          self.list = try managedObjectContext.fetch(DailyHealth.fetchRequest())
        }
        catch {
        }
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        // send Daily Health array to SecondViewController
        if segue.identifier == "dataSegue" {
            let des = segue.destination as! SecondViewController
            des.MVC = self.MVC
            des.managedObjectContext = self.managedObjectContext
        }
        else if segue.identifier == "healthSegue" {
            let des = segue.destination as! ThirdViewController
            des.MVC = self.MVC
            des.managedObjectContext = self.managedObjectContext
        }
        else {
            let des = segue.destination as! FourthViewController
            des.MVC = self.MVC
            des.managedObjectContext = self.managedObjectContext
        }
    }
    
}
