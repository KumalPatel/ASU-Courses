//
//  itemCell.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/25/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import SwiftUI

struct itemCell: View {

    var title: String
    var quantity: String
    var image: Data
    
    
    var body: some View {
        HStack {
            Image(uiImage: UIImage(data: image)!)
                .resizable()
                .frame(width: 80, height: 80)
            VStack(alignment: .leading) {
                Text(title)
                    .font(.headline)
                Text(quantity)
                    .font(.caption)
            }
        }
    }
}
/*
struct itemCell_Previews: PreviewProvider {
    static var previews: some View {
        itemCell()
    }
} */
