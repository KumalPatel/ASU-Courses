//
//  ViewController.swift
//  Lab7
//
//  Created by Kumal Patel on 11/4/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit
import MapKit

class ViewController: UIViewController {

    @IBOutlet weak var address: UITextField!
    @IBOutlet weak var earthquakeInfo: UITextView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        earthquakeInfo.isEditable = false
        earthquakeInfo.isHidden = true
    }
    
    @IBAction func showInfo(_ sender: Any) {
        let geoCoder = CLGeocoder();
        let addressString = address.text!
        earthquakeInfo.isHidden = false
        earthquakeInfo.text = ""
  
        geoCoder.geocodeAddressString(addressString, completionHandler: {(placemarks, error) in
            
            if error != nil {
                print("Geocode failed :\(error!.localizedDescription)")
            } else if placemarks!.count > 0 {
                let placemark = placemarks![0]
                let location = placemark.location
                let coords = location!.coordinate
                let lat = coords.latitude
                let long = abs(coords.longitude)
                
                let north = String(format: "%.2f", lat + 10)
                let south = String(format: "%.2f", lat - 10)
                let west = String(format: "%.2f", long + 10)
                let east = String(format: "%.2f", long - 10)
                                
                self.getJsonInfo(north: north, south: south, west: west, east: east)
            }
        })

    }
    
    func getJsonInfo(north: String, south: String, west: String, east: String) {
        let urlAsString = "http://api.geonames.org/earthquakesJSON?"+"north=\(north)"+"&south=\(south)"+"&east=\(east)"+"&west=\(west)"+"&username=kumal.patel"
        
        let url = URL(string: urlAsString)!
        let urlSession = URLSession.shared
        
        let jsonQuery = urlSession.dataTask(with: url, completionHandler: { data, response, error -> Void in
            if(error != nil) {
                print(error!.localizedDescription)
            }
            var err: NSError?
            
            var jsonResult = (try! JSONSerialization.jsonObject(with: data!, options: JSONSerialization.ReadingOptions.mutableContainers)) as! NSDictionary
            if(err != nil) {
                print("JSON Error: \(err!.localizedDescription)")
            }
            
            let setOne:NSArray = jsonResult["earthquakes"] as! NSArray
            var count = 0
            for value in setOne as! [[String: AnyObject]] {
                let dateTime = value["datetime"]!
                let magnitude = value["magnitude"]!.floatValue!
                
                if count < 10 {
                    print(count)
                    DispatchQueue.main.async {
                        self.earthquakeInfo.text += "Date Time = \(dateTime)\n"
                        self.earthquakeInfo.text += "Magnitude = \(magnitude)\n"
                        self.earthquakeInfo.text += "\n"
                    }
                }
                count += 1
            }
        })
        jsonQuery.resume()
    }
}

