//
//  ImagePicker.swift
//  ShoppingList
//
//  Created by Kumal Patel on 11/25/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import SwiftUI

struct ImagePicker: UIViewControllerRepresentable {
    class Corrdinator: NSObject, UINavigationControllerDelegate, UIImagePickerControllerDelegate {
        let parent: ImagePicker
        
        init(_ parent: ImagePicker) {
            self.parent = parent
        }
        
        func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
            if let selectedImage = info[.originalImage] as? UIImage {
                self.parent.image = selectedImage
            }
            self.parent.isPresented.toggle()
        }
    }
    
    @Binding var isPresented: Bool
    @Binding var image: UIImage
    
    var sourceType: UIImagePickerController.SourceType = .photoLibrary
    
    func makeCoordinator() -> Corrdinator {
        Coordinator(self)
    }
    func makeUIViewController(context: UIViewControllerRepresentableContext<ImagePicker>)  ->  UIImagePickerController {
        let picker = UIImagePickerController()
        picker.sourceType = sourceType
        picker.delegate = context.coordinator
        
        print(picker.sourceType)
        
        return picker
    }
    
    func updateUIViewController(_ uiViewController: UIImagePickerController, context: UIViewControllerRepresentableContext<ImagePicker>) {
        
    }
}
