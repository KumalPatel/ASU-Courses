//
//  movieDictionary.swift
//  Lab3
//
//  Created by Kumal Patel on 9/19/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import Foundation

class movieDictionary{

    // global variables
    var pos = -1
    // dictionary that stores maps the title to the object
    var movieRecords : [String:movieInfo] = [String:movieInfo]()
    init() { }
    
    func add(title:String, genre:String, ticket:Float){
        let record = movieInfo(x: title, y: genre, z: ticket)
        movieRecords[record.title!] = record
    }
    
    func delete(title:String){
        movieRecords[title] = nil
    }
    
    func search(title:String) -> movieInfo? {
        var flag = false
        
        for (movie, _) in movieRecords{
            if(movie == title){
                flag = true
            }
        }
        
        if(flag){
            return movieRecords[title]
        }
        else{
            return nil
        }
    }
    
    func next() -> movieInfo? {
        var key = ""
        
        if(pos < movieRecords.count){
            pos = pos + 1
        }
        
        // find movieInfo at pos index
        for(index, dict) in movieRecords.enumerated() {
            if(index == pos) {
                key = dict.key
            }
        }
        
        return movieRecords[key]
    }
    
    func prev() -> movieInfo? {
        var key = ""
        
        if(pos > 0){
            pos = pos - 1
        }
        
        for(index, dict) in movieRecords.enumerated() {
            if(index == pos) {
                key = dict.key
            }
        }
        
            return movieRecords[key]
    }
}
