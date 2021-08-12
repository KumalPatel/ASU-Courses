//
//  ShoppingItem.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/23/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import Foundation
import CoreData

public class ShoppingItem: NSManagedObject, Identifiable {
    
    @NSManaged public var title: String?
    @NSManaged public var image: Data?
    @NSManaged public var quantity: Int16
}

extension ShoppingItem {
    static func fetchItems() -> NSFetchRequest<ShoppingItem> {
        let request: NSFetchRequest<ShoppingItem> = ShoppingItem.fetchRequest() as! NSFetchRequest<ShoppingItem>
        let sortDescriptor = NSSortDescriptor(key: "quantity", ascending: true)
        request.sortDescriptors = [sortDescriptor]
        
        return request
    }
}
