//
//  DetailViewController.swift
//  Lab4
//
//  Created by Kumal Patel on 10/4/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class DetailViewController: UIViewController {
    var selectedCityName:String?
    var selectedCityImage:String?
    var selectedCityDesc:String?
    
    @IBOutlet weak var city_title: UILabel!
    @IBOutlet weak var image: UIImageView!
    @IBOutlet weak var city_desc: UITextView!
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        city_desc.isEditable = false
        city_title.text = selectedCityName
        image.image = UIImage(named: selectedCityImage!)
        city_desc.text = selectedCityDesc
    }
    


}
