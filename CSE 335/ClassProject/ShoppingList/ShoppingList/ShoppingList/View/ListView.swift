//
//  ListView.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/23/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import SwiftUI

struct ListView: View {
        
    @State private var newItem = ""
    @State private var showAlert = false
    @State private var deleteAlert = false

    @Environment(\.managedObjectContext) var managedObjectContext
    @FetchRequest(fetchRequest: ShoppingItem.fetchItems()) var shoppingItems: FetchedResults<ShoppingItem>
    
    var body: some View {
        ZStack {
            List {
                Section(header: Text("What To Buy")) {
                    ForEach(self.shoppingItems) { item in
                        itemCell(title: item.title!, quantity: "Quantity: \(item.quantity)", image: (item.image)! )
                    }
                    .onDelete{ index in
                        let deleteItem = self.shoppingItems[index.first!]
                        self.managedObjectContext.delete(deleteItem)
                        
                        do {
                            try self.managedObjectContext.save()
                        }
                        catch {
                            deleteAlert.toggle()
                        }
                    }
                }
            }
                .navigationBarTitle(Text("Shopping List"))
                .navigationBarItems(trailing:
                    Button(action: {
                        self.showAlert.toggle()
                    })
                {
                    Image(systemName: "plus.circle.fill")
                        .foregroundColor(.green)
                    .font(.title)
                    .frame(width: 30, height: 30)
                })
            
                // alerts
                .alert(isPresented: $deleteAlert) {
                    Alert(title: Text("Error: Could Not Delete Item"))
                }
                customAlert(showAlert: $showAlert)
            }
    }
}

struct ListView_Previews: PreviewProvider {
    static var previews: some View {
        ListView()
    }
}
