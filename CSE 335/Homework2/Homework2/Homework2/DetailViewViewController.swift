//
//  DetailViewViewController.swift
//  Homework2
//
//  Created by Kumal Patel on 11/19/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class DetailViewViewController: UIViewController {

    var selectedCityName:String?
    var selectedCityDescription:String?
    var selectedCityImage:UIImage?
    
    @IBOutlet weak var cityName: UILabel!
    @IBOutlet weak var cityDescription: UITextView!
    @IBOutlet weak var cityImage: UIImageView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        cityDescription.isEditable = false
        cityName.text = selectedCityName
        cityDescription.text = selectedCityDescription
        cityImage.image = selectedCityImage

        
    }
    

    

}
