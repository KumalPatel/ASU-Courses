//
//  LoadImage.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/29/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import SwiftUI
import Combine

struct Post: Codable {
    var results: [Results]
}

class LoadImage {
    func getPosts(query: String, completion: @escaping (Post) -> ()) {
        guard let url = URL(string: "https://api.unsplash.com/search/photos?query=\(query)&client_id=rhM4DQrKUk-5thjp1UuHIKskoKik6lWFG-t08hlAcsI") else { return }
        
        URLSession.shared.dataTask(with: url) { (data, _, _) in
            do {
                let posts = try JSONDecoder().decode(Post.self, from: data!)
                
                DispatchQueue.main.async {
                    completion(posts)
                }
            }
            catch {
                print("Could not decode")
            }
            //let posts = try! JSONDecoder().decode(Post.self, from: data!)
            //print(posts)
            //DispatchQueue.main.async {
                //ompletion(posts)
            //}
        }
        .resume()
    }
}

struct Results: Codable {
    var urls = Urls()
}

struct Urls: Codable {
    var raw: String?
    var full: String?
    var regular: String?
    var small: String?
    var thumb: String?
}


/*
struct Api: Decodable {
    let name: String
    let imageURL: String
}

class NetworkManager: ObservableObject {
    var didChange = PassthroughSubject<NetworkManager, Never>()
    
    var ImageApi = [Api]() {
        didSet {
            didChange.send(self)
        }
    }
    
    init() {
       // guard let url = URL(string: "https://api.unsplash.com/search/photos?query=apple&client_id=rhM4DQrKUk-5thjp1UuHIKskoKik6lWFG-t08hlAcsI") else { return }
        guard let url = URL(string: "https://api.letsbuildthatapp.com/jsondecodable/courses") else { return }
        URLSession.shared.dataTask(with: url) { (data, _, _) in
            
            guard let data = data else { return }
            
            let ImageApi = try! JSONDecoder().decode([Api].self, from: data)
            DispatchQueue.main.async {
                self.ImageApi = ImageApi
            }
            
            print("Fetched Data")
        }
        .resume()
    }
}
*/
