//
//  ViewController.swift
//  Homework2
//
//  Created by Kumal Patel on 11/17/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class ViewController: UITableViewController, UIImagePickerControllerDelegate, UINavigationControllerDelegate {

    var cityModel:cities = cities()
    let picker = UIImagePickerController()
    var cName:String?
    var cDescription:String?
    var cImage:UIImage?
    var Editing:Bool = false
    var Adding:Bool = false
    var selectedCity: city?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        picker.delegate = self
        cityModel.createCityDictionary()
    }

    // MARK: - Table view data source
    override func numberOfSections(in tableView: UITableView) -> Int {
        cityModel.citySectionTitles.count
    }

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        let cityKey = cityModel.citySectionTitles[section]
        
        if let count = cityModel.getSectionCount(key: cityKey) {
            return count
        }
        else {
            return 0
        }
    }

    override func tableView(_ tableView: UITableView, titleForHeaderInSection section: Int) -> String? {
        return cityModel.citySectionTitles[section]
    }
    
    
    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cityCell", for: indexPath) as! TableViewCell
        
        let cityKey = cityModel.citySectionTitles[indexPath.section]
        if let city = cityModel.getCityObjectRow(key: cityKey, index: indexPath.row) {
            cell.cTitle.text = city.cityName
            cell.cDescription.text = city.cityDescription
            cell.cImage.image = city.cityImage
        }
        return cell
    }
    
    override func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        var cellHeight:CGFloat = CGFloat()
        cellHeight = 70
        return cellHeight
    }
    
    // Override to support conditional editing of the table view.
   override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        return true
    }
    
    override func tableView(_ tableView: UITableView, trailingSwipeActionsConfigurationForRowAt indexPath: IndexPath) -> UISwipeActionsConfiguration? {
        let update = UIContextualAction(style: .normal, title: "Update") { (action, view, completion) in
            // update booleans
            self.Editing = true
            self.Adding = false
            
            let alert = UIAlertController(title: "Update City", message: nil, preferredStyle: .alert)
            
            alert.addAction(UIAlertAction(title: "Take Photo", style: .default, handler: { action in
                if UIImagePickerController.isSourceTypeAvailable(.camera) {
                    self.picker.allowsEditing = false
                    self.picker.sourceType = UIImagePickerController.SourceType.camera
                    self.picker.modalPresentationStyle = .fullScreen
                    self.present(self.picker, animated: true, completion: nil)
                    
                    // find selected city info
                    let cityKey = self.cityModel.citySectionTitles[indexPath.section]
                    self.selectedCity = self.cityModel.getCityObjectRow(key: cityKey, index: indexPath.row)
                    
                    self.cDescription = alert.textFields?.first?.text
                }
                else {
                    let eAlert = UIAlertController(title: "Error", message: "No Camera Found!", preferredStyle: .alert)
                    
                    eAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
                    self.present(eAlert,animated: true)
                }
            }))
                
            alert.addAction(UIAlertAction(title: "Choose Existing Photo", style: .default, handler: { action in
                self.picker.allowsEditing = false
                self.picker.sourceType = .photoLibrary
                self.picker.modalPresentationStyle = .fullScreen
                self.present(self.picker, animated: true, completion: nil)
                
                // find selected city info
                let cityKey = self.cityModel.citySectionTitles[indexPath.section]
                self.selectedCity = self.cityModel.getCityObjectRow(key: cityKey, index: indexPath.row)
    
                self.cDescription = alert.textFields?.first?.text
            }))
                
            alert.addTextField(configurationHandler: { textField in
                textField.placeholder = "Enter new City Description"
            })
            
            alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
            self.present(alert,animated: true)
        
            self.tableView.setEditing(false, animated: true)
        }
        
        let remove = UIContextualAction(style: .destructive, title: "Remove") { (action, view, completion) in
            let cityKey = self.cityModel.citySectionTitles[indexPath.section]
            self.cityModel.removeCityObject(key: cityKey, index: indexPath.row)
            self.tableView.deleteRows(at: [indexPath], with: .automatic)
            self.tableView.setEditing(false, animated: true)
        }
        return UISwipeActionsConfiguration(actions: [remove, update])
    }
    
    func imagePickerController(_ picker: UIImagePickerController, didFinishPickingMediaWithInfo info: [UIImagePickerController.InfoKey : Any]) {
        if let image = info[UIImagePickerController.InfoKey.originalImage] as? UIImage {
            cImage = image
            
            if(self.Adding) {
                cityModel.addCityObject(name: cName!, description: cDescription!, image: cImage!)
                self.tableView.reloadData()
            }
            else if(self.Editing) {
                self.selectedCity?.cityDescription = cDescription!
                self.selectedCity?.cityImage = image
                self.tableView.reloadData()
            }
            
        }
            
            dismiss(animated: true, completion: nil)
        
    }
    
    @IBAction func add(_ sender: Any) {
        // update booleans
        self.Adding = true
        self.Editing = false
        
        let alert = UIAlertController(title: "Add City", message: nil, preferredStyle: .alert)
               
               alert.addAction(UIAlertAction(title: "Take Photo", style: .default, handler: { action in
                   if UIImagePickerController.isSourceTypeAvailable(.camera) {
                       self.picker.allowsEditing = false
                       self.picker.sourceType = UIImagePickerController.SourceType.camera
                       self.picker.modalPresentationStyle = .fullScreen
                       self.present(self.picker, animated: true, completion: nil)
                      
                       self.cName = alert.textFields?.first?.text
                       self.cDescription = alert.textFields?.last?.text
                   }
                   else {
                        let eAlert = UIAlertController(title: "Error", message: "No Camera Found!", preferredStyle: .alert)
                    
                        eAlert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
                        self.present(eAlert,animated: true)
                   }
               }))
               
               alert.addAction(UIAlertAction(title: "Choose Existing Photo", style: .default, handler: { action in
                   self.picker.allowsEditing = false
                   self.picker.sourceType = .photoLibrary
                   self.picker.modalPresentationStyle = .fullScreen
                   self.present(self.picker, animated: true, completion: nil)
            
                   self.cName = alert.textFields?.first?.text
                   self.cDescription = alert.textFields?.last?.text
                
               }))
        
                alert.addTextField(configurationHandler: { textField in
                    textField.placeholder = "Enter City Name"
                })
                alert.addTextField(configurationHandler: { textField in
                    textField.placeholder = "Enter City Description"
                })
               
                alert.addAction(UIAlertAction(title: "Cancel", style: .cancel, handler: nil))
                self.present(alert,animated: true)
    }
    
    // MARK: - Navigation
    
    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        let selectedIndex:IndexPath = self.tableView.indexPath(for:sender as! UITableViewCell)!
        let cityKey = cityModel.citySectionTitles[selectedIndex.section]
        let city = cityModel.getCityObjectRow(key: cityKey, index: selectedIndex.row)
        
        if(segue.identifier == "detailView") {
            if let viewController:DetailViewViewController = segue.destination as? DetailViewViewController {
                viewController.selectedCityName = city?.cityName
                viewController.selectedCityDescription = city?.cityDescription
                viewController.selectedCityImage = city?.cityImage
            }
        }
        
    }

    
}

