//
//  mapList.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/29/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import SwiftUI
import MapKit

struct mapList: View {
    let landmarks: [Landmark]
    
    var body: some View {
        VStack(alignment: .leading) {
            List {
                ForEach(self.landmarks, id: \.id) { landmark in
                    VStack(alignment: .leading) {
                        Text(landmark.name)
                            .fontWeight(.bold)
                        
                        Text(landmark.title)
                    }
                }
            }
        }
        .cornerRadius(10)
    }
}

/*struct mapList_Previews: PreviewProvider {
    static var previews: some View {
        mapList()
    }
} */
