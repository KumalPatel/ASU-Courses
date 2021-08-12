//
//  DailyHealth+CoreDataProperties.swift
//  Homework1
//
//  Created by Kumal Patel on 10/17/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//
//

import Foundation
import CoreData


extension DailyHealth {

    @nonobjc public class func fetchRequest() -> NSFetchRequest<DailyHealth> {
        return NSFetchRequest<DailyHealth>(entityName: "DailyHealth")
    }

    @NSManaged public var sBlood: Int64
    @NSManaged public var dBlood: Int64
    @NSManaged public var weight: Int64
    @NSManaged public var sugarLevel: Int64
    @NSManaged public var symptoms: String?

}
