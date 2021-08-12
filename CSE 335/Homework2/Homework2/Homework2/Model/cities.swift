//
//  cities.swift
//  Homework2
//
//  Created by Kumal Patel on 11/17/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import Foundation
import UIKit

class cities {
    var cities:[city] = []
    var cityList = [String: [city]]()
    let citySectionTitles = ["A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"]
    
    init() {
        let c1 = city(name: "Phoenix", desc: "Captial of Arizona", img: UIImage(named:"Phoenix.jpg")!)
        let c2 = city(name: "Springfield", desc: "Capital of Illinois", img: UIImage(named:"SpringField.jpg")!)
        let c3 = city(name: "Newport", desc: "City set on Aquidneck island in Rhode island", img: UIImage(named:"Newport.jpg")!)
        
        cities.append(c1)
        cities.append(c2)
        cities.append(c3)
    }
    
    func createCityDictionary() {
        for city in cities {
            let cName = city.cityName
            let endIndex = cName.index((cName.startIndex), offsetBy:1)
            let cityKey = String(cName[(..<endIndex)])
            
            // create array of each key
            if var cityObjects = cityList[cityKey] {
                cityObjects.append(city)
                cityList[cityKey] = cityObjects
            }
            else {
                cityList[cityKey] = [city]
            }
        }
    }
    
    func getSectionCount(key:String) -> Int? {
        return cityList[key]?.count
    }
    
    func getCityObjectRow(key:String, index:Int) -> city? {
        if let cityValues = cityList[key] {
            return cityValues[index];
        }
        else {
            return nil
        }
    }
    
    func removeCityObject(key:String, index:Int) {
        cityList[key]?.remove(at: index)
    }
    
    func addCityObject(name:String, description:String, image:UIImage) {
        let newCity = city(name: name, desc: description, img: image)
        self.cities.append(newCity)
        
        let cName = name
        let endIndex = cName.index((cName.startIndex), offsetBy:1)
        let cityKey = String(cName[(..<endIndex)])
        
        // add city to the dictionary
        if var cityObjects = self.cityList[cityKey] {
            cityObjects.append(newCity)
            self.cityList[cityKey] = cityObjects
        }
        else {
            self.cityList[cityKey] = [newCity]
        }
    }
}

class city {
    var cityName:String
    
    
    
    var cityDescription:String
    var cityImage:UIImage
    
    init(name:String, desc:String, img:UIImage) {
        cityName = name
        cityDescription = desc
        cityImage = img
    }
}
