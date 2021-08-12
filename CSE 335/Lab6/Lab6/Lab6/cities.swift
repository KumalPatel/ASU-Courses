//
//  cities.swift
//  Lab6
//
//  Created by Kumal Patel on 10/24/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import Foundation

class cities
{
    var cities:[city] = []
    
    init()
    {
        let desc1 = "Phoenix is the capital of the southwestern U.S. state of Arizona. Known for its year-round sun and warm temperatures, it anchors a sprawling, multicity metropolitan area known as the Valley of the Sun. It's known for high-end spa resorts, Jack Nicklaus–designed golf courses and vibrant nightclubs. Other highlights include the Desert Botanical Garden, displaying cacti and numerous native plants."
        let desc2 = "Springfield is the capital of the U.S. state of Illinois and the county seat and largest city of Sangamon County. The city's population was 116,250 at the 2010 U.S. Census, which makes it the state's sixth most-populous city, the second largest outside of the Chicago metropolitan area (after Rockford), and the largest in central Illinois. As of 2019, the city's population was estimated to have decreased to 114,230, with just over 211,700 residents living in the Springfield Metropolitan Statistical Area, which includes Sangamon County and the adjacent Menard County"
        let desc3 = "Newport is a city set on Aquidneck Island in the New England state of Rhode Island. Its yacht-filled harbor hosted the America’s Cup, a renowned annual sailing regatta, for many years. Newport is also known for the Gilded Age mansions lining Bellevue Avenue, some of which are now museums. The most famous is The Breakers, an 1895 mansion patterned after a Renaissance palace."
        
        _ = addCityObject(cityname: "Phoenix", description: desc1, image: "Phoenix.jpg")
        _ = addCityObject(cityname: "Springfield", description: desc2, image: "SpringField.jpg")
        _ = addCityObject(cityname: "Newport", description: desc3, image: "Newport.jpg")
    }
    
    func getCount() -> Int
    {
        return cities.count
    }
    
    func getCityObject(item:Int) -> city
    {
        return cities[item]
    }
    
    func removeCityObject(item:Int)
    {
        cities.remove(at: item)
    }
    
    func addCityObject(cityname:String, description:String, image:String) -> city
    {
        let c = city(name: cityname, desc:description, img: image)
        cities.append(c)
        return c
    }
}

class city
{
    var cityName:String?
    var cityDescription:String?
    var cityImage:String?
    
    init(name:String, desc:String, img:String)
    {
        cityName = name
        cityDescription = desc
        cityImage = img
    }
}
