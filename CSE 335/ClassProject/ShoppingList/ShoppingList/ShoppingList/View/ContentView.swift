//
//  ContentView.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/22/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import SwiftUI
import MapKit

struct ContentView: View {
    var body: some View {
        NavigationView {
            VStack(alignment: .center) {
                Text("Shopping List")
                    .font(.title)
                    .fontWeight(.bold)
                    .padding(.bottom, 100)
                NavigationLink(destination: MapKitView())
                {
                    HStack {
                        Text("Find Store Near Me")
                            .fontWeight(.semibold)
                            .font(.headline)
                    }
                    .frame(minWidth: 0, maxWidth: .infinity)
                    .padding()
                    .foregroundColor(.white)
                    .background(Color.blue)
                    .cornerRadius(40)
                    .padding(.horizontal, 20)
                }
                .padding(.bottom)
                
                NavigationLink(destination: ListView()) {
                    HStack {
                        Text("Load List")
                            .fontWeight(.semibold)
                            .font(.headline)
                    }
                    .frame(minWidth: 0, maxWidth: .infinity)
                    .padding()
                    .foregroundColor(.white)
                    .background(Color.blue)
                    .cornerRadius(40)
                    .padding(.horizontal, 20)
                }
                .padding(.bottom)
            }
        }
    }

}

struct MapKitView: View {
    
    @ObservedObject var locationManager = LocationManager()
    @State private var search: String = ""
    @State private var landmarks: [Landmark] = [Landmark]()
    @State private var changed = false
    
    var body: some View {
 
        ZStack(alignment: .top) {
            
            MapView(landmarks: landmarks)
                .edgesIgnoringSafeArea(.all)
            
            TextField("Search Grocery Stores", text: $search)
            {
                self.getNearbyStores()
                changed.toggle()
            }

            .textFieldStyle(RoundedBorderTextFieldStyle())
            .padding()
            .offset(y: -35)
        }

        VStack {
            if(changed){
                mapList(landmarks: self.landmarks)
                    .frame(width: UIScreen.main.bounds.width, height: 300)
                    .animation(.spring())
            }
        }
    }
    
    func getNearbyStores() {
        let request = MKLocalSearch.Request()
        request.naturalLanguageQuery = search
        
        let search = MKLocalSearch(request: request)
        search.start { (response, error) in
            if let response = response {
                let mapItems = response.mapItems
                self.landmarks = mapItems.map {
                    Landmark(placemark: $0.placemark)
                }
                
            }
        }
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
