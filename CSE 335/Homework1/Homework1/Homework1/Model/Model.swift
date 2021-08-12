//
//  Model.swift
//  Homework1
//
//  Created by Kumal Patel on 10/18/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import Foundation
import CoreData

public class Model {
    let managedObjectContext: NSManagedObjectContext?
    
    init(context: NSManagedObjectContext) {
        managedObjectContext = context
    }
        
    func SaveContext(sBlood_: Int64, dBlood_: Int64, weight_: Int64, sugarLevel_: Int64, symptoms_: String) -> DailyHealth{
        let entity = NSEntityDescription.entity(forEntityName: "DailyHealth", in: self.managedObjectContext!)
        let newEntry = DailyHealth(entity: entity!, insertInto: managedObjectContext)
        
        newEntry.sBlood = sBlood_
        newEntry.dBlood = dBlood_
        newEntry.weight = weight_
        newEntry.sugarLevel = sugarLevel_
        newEntry.symptoms = symptoms_
        
        // save data
        do {
            try self.managedObjectContext!.save()
        }
        catch {
            
        }
        
        return newEntry
    }
    
    func clearData() {
        let fetchRequest = NSFetchRequest<NSFetchRequestResult>(entityName: "DailyHealth")
        let deleteRequest = NSBatchDeleteRequest(fetchRequest: fetchRequest)
        
        do {
            try managedObjectContext!.execute(deleteRequest)
            try managedObjectContext!.save()
        }
        catch {
        }
        
    }
    
    
    
}
