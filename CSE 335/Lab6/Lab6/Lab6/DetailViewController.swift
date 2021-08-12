//
//  DetailViewController.swift
//  Lab6
//
//  Created by Kumal Patel on 10/24/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit
import CoreLocation
import MapKit

class DetailViewController: UIViewController {

    @IBOutlet weak var mapType: UISegmentedControl!
    @IBOutlet weak var map: MKMapView!
    @IBOutlet weak var searchText: UITextField!
    @IBOutlet weak var btn: UIButton!
    @IBOutlet weak var longText: UILabel!
    @IBOutlet weak var latText: UILabel!
    
    var cityName: String?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        btn.layer.cornerRadius = 10
        btn.layer.masksToBounds = true
        
        // map initally on standard
        DisplayMap()
    }


    @IBAction func displayMap(_ sender: Any) {
        
        switch(mapType.selectedSegmentIndex) {
            case 0:
                map.mapType = MKMapType.standard
            
            case 1:
                map.mapType = MKMapType.satellite
            
            case 2:
                map.mapType = MKMapType.hybrid
            
            default:
                map.mapType = MKMapType.standard
        }
    }
    
    @IBAction func submitBtn(_ sender: Any) {
        let request = MKLocalSearch.Request()
        request.naturalLanguageQuery = self.searchText.text
        request.region = map.region
        let search = MKLocalSearch(request: request)
        
        search.start { response, _ in
            guard let response = response else {
                return
            }
            var matchingItems:[MKMapItem] = []
            matchingItems = response.mapItems
            if(matchingItems.count > 1) {
                for i in 1...matchingItems.count - 1 {
                    let place = matchingItems[i].placemark
                    
                    self.AddAnnotations(locationCoordinate: place.location!.coordinate, title: place.name!)
                }
            }
        }
    }
    
    func DisplayMap() {
        let geoCoder = CLGeocoder()
        let addressString = cityName!
        geoCoder.geocodeAddressString(addressString, completionHandler: { (placemarks, error) in
             if error != nil {
                 print("Geocode failed: \(error!.localizedDescription)")
             } else if placemarks!.count > 0 {
                 let placemark = placemarks![0]
                 let location = placemark.location
                 let coords = location!.coordinate
                 self.latText.text = "\(coords.latitude)"
                 self.longText.text = "\(coords.longitude)"
                 
                self.AddAnnotations(locationCoordinate: placemark.location!.coordinate, title: placemark.locality!)
             }
         })
    }
    
    func AddAnnotations(locationCoordinate: CLLocationCoordinate2D, title: String) {
        let span = MKCoordinateSpan.init(latitudeDelta: 0.05, longitudeDelta: 0.05)
        let region = MKCoordinateRegion(center: locationCoordinate, span: span)
        self.map.setRegion(region, animated: true)
        let annotation = MKPointAnnotation()
        annotation.coordinate = locationCoordinate
        annotation.title = title
        
        self.map.addAnnotation(annotation)
    }
}
