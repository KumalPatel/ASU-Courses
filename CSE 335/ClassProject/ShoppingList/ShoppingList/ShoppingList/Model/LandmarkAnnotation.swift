//
//  LandmarkAnnotation.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/28/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit
import MapKit

class LandmarkAnnotation: NSObject, MKAnnotation {
    let title: String?
    let coordinate: CLLocationCoordinate2D
    
    init(landmark: Landmark) {
        self.title = landmark.name
        self.coordinate = landmark.coordinate
    }
}
