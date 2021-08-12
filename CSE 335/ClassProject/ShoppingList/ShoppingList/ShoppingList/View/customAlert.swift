//
//  customAlert.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/25/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import SwiftUI
import Combine

enum ActiveAlert {
    case first, second
}

struct customAlert: View {
    
    @State private var title = ""
    @State private var quantity = ""
    @State private var selectedImage = UIImage()
    
    @State private var showSheet = false // actionsheey
    @State private var showImagePicker = false
    @State private var sourceType: UIImagePickerController.SourceType = .camera
    @State private var alertMsg = false
    @State private var activeAlert: ActiveAlert = .first
    
    @State private var posts: [Post] = []
    @Binding var showAlert: Bool //alert
    @Environment(\.managedObjectContext) var managedObjectContext
    @FetchRequest(fetchRequest: ShoppingItem.fetchItems()) var shoppingItems: FetchedResults<ShoppingItem>

    let screenSize = UIScreen.main.bounds
    
    var body: some View {
        VStack(spacing: 20) {
            HStack() {
                Spacer()
                Button(action: {
                    // functionality for camera :
                    // load action sheet prompt user to choose how to pick the image
                    showSheet = true
                })
                {
                    Image("camera")
                        .resizable()
                        .frame(width: 40, height: 40)
                        .padding(.top, 20)
                        .padding(.horizontal, 8)
                }

            }
            
            Text("Add Item")
                .font((.system(size: 24)))
                .fontWeight(.medium)
                .padding(.leading, 15)
            
            HStack(spacing: 30){
                
                Text("Name: ")
                TextField("", text: $title)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .frame(width: 200)
            }
            
            HStack {
                Text("Quantity: ")
                TextField("", text: $quantity)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
                    .frame(width: 200)
            }
            
            HStack(spacing: 50) {
                Button("Save") {
                                        
                if(!self.title.isEmpty && Int16(self.quantity) != nil && self.selectedImage != nil) {
                    let title = self.title
                    let quantity = Int16(self.quantity)
                    let image = self.selectedImage.pngData()
                    
                    let item = ShoppingItem(context: self.managedObjectContext)
                    
                    item.title = title
                    item.quantity = quantity!
                    item.image = image!
                    
                    do {
                        try self.managedObjectContext.save()
                    }
                    catch {
                        alertMsg = true
                        activeAlert = .second
                    }
                    
                    // clear textfields
                    self.title = ""
                    self.quantity = ""
                }
                else {
                    alertMsg = true
                    activeAlert = .second
                }

                // after saving close alert
                showAlert = false
                    
                }
                .padding(.horizontal, 25)
                .padding(.vertical, 5)
                .background(Color(red: 2/255, green: 53/255, blue: 0/255))
                .foregroundColor(.white)
                .clipShape(RoundedRectangle(cornerRadius: 10, style: .continuous))
                
                Button("Cancel") {
                    showAlert = false
                }
                .padding(.horizontal, 25)
                .padding(.vertical, 5)
                .background(Color(red: 2/255, green: 53/255, blue: 0/255))
                .foregroundColor(.white)
                .clipShape(RoundedRectangle(cornerRadius: 10, style: .continuous))
            }
            
            Spacer()
        }

        .frame(width: screenSize.width * 0.8, height: screenSize.height * 0.4 - 15)
        .background(Color(UIColor.systemGray6))
        .clipShape(RoundedRectangle(cornerRadius: 20, style: .continuous))
        .offset(y: showAlert ? 0: screenSize.height)
        .animation(.spring())
        .shadow(color: Color(UIColor.systemGray6), radius: 6, x: -9, y: -9)
        
        // alerts
        .sheet(isPresented: $showImagePicker) {
            ImagePicker(isPresented: $showImagePicker, image: $selectedImage)
        }
        
        .alert(isPresented: $alertMsg) {
            switch activeAlert {
            case .first:
                return Alert(title: Text("Error: Could Not Find Camera."), message: Text(""), dismissButton: .default(Text("OK")))
            case .second:
                return Alert(title: Text("Error: Could Not Add Item."), message: Text(""), dismissButton: .default(Text("OK")))
            }
        }
        .actionSheet(isPresented: $showSheet) {
            
            ActionSheet(title: Text(""), message: Text(""), buttons: [
                .default(Text("Take Photo")) {
                    if(UIImagePickerController.isSourceTypeAvailable(.camera)) {
                        showImagePicker = true
                        sourceType = .camera
                    }
                    else {
                        alertMsg = true
                        activeAlert = .first
                    }
                },
                .default(Text("Choose Existing Photo")) {
                    showImagePicker = true
                    sourceType = .photoLibrary
                },
                .default(Text("Web Search")) {
                    LoadImage().getPosts(query: self.title) { (posts) in
                       let imgUrl = posts.results[0].urls.raw
                       let url = URL(string: imgUrl!)
                       let data = try! Data(contentsOf: url!)
                       selectedImage = UIImage(data: data)!       
                    }
                },
                .cancel() {}
            ])
        }
    }
}


/*
struct customAlert_Previews: PreviewProvider {
    static var previews: some View {
        customAlert(showAlert: )
    }
} */
