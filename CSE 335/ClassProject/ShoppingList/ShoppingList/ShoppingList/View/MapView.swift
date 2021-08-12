//
//  MapView.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/22/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import SwiftUI
import MapKit

struct MapView: UIViewRepresentable {
   // let locationManager = CLLocationManager()
    let landmarks: [Landmark]
    
    class Coordinator: NSObject, MKMapViewDelegate {
    
    var parent: MapView
    
    init(_ parent: MapView) {
        self.parent = parent
    }
    
    func mapView(_ mapView: MKMapView, didAdd views: [MKAnnotationView]) {
        if let annotationView = views.first {
            if let annotation = annotationView.annotation {
                if annotation is MKUserLocation {
                    let region = MKCoordinateRegion(center: annotation.coordinate, latitudinalMeters: 1000, longitudinalMeters: 1000)
                    mapView.setRegion(region, animated: true)
                }
            }
        }
    }
    
    } // end of class
    
    func makeCoordinator() -> Coordinator {
        Coordinator(self)
    }
    
    func makeUIView(context: Context) -> MKMapView {
        let mapView = MKMapView(frame: .zero)
        mapView.showsUserLocation = true
        mapView.delegate = context.coordinator
        return mapView
    }

    func updateUIView(_ uiView: MKMapView, context: Context) {
        addAnnotations(view: uiView)
    }
    
    func addAnnotations(view: MKMapView) {
        view.removeAnnotations(view.annotations)
        let annotations = self.landmarks.map(LandmarkAnnotation.init)
        view.addAnnotations(annotations)
    }
}
    
