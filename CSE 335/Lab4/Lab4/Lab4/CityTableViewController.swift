//
//  CityTableViewController.swift
//  Lab4
//
//  Created by Kumal Patel on 10/4/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class CityTableViewController: UITableViewController {
      
    // model
    var cityList:cities = cities()
    
    override func viewDidLoad() {
        super.viewDidLoad()
    }

    // MARK: - Table view data source

    override func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int {
        return cityList.getCount()
    }

    override func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell {
        let cell = tableView.dequeueReusableCell(withIdentifier: "cityCell", for: indexPath) as! CityTableViewCell
        cell.layer.borderWidth = 1.0
        
        let cityItem = cityList.getCityObject(item: indexPath.row)
        
        cell.cityTitle.text = cityItem.cityName
        cell.cityImage.image = UIImage(named: cityItem.cityImage!)

        return cell
    }
    
    // Override to support conditional editing of the table view.
    override func tableView(_ tableView: UITableView, canEditRowAt indexPath: IndexPath) -> Bool {
        return true
    }
    
    // Override to support editing the table view.
    override func tableView(_ tableView: UITableView, commit editingStyle: UITableViewCell.EditingStyle, forRowAt indexPath: IndexPath) {
        cityList.removeCityObject(item:indexPath.row)
        
        self.tableView.beginUpdates()
        self.tableView.deleteRows(at: [indexPath], with: .automatic)
        self.tableView.endUpdates()
    }
    
    override func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat {
        var cellHeight:CGFloat = CGFloat()
        cellHeight = 65
        return cellHeight
    }
    
    func tableView(tableView: UITableView, editingStlyForRowAtIndexPath indexPath: NSIndexPath) -> UITableViewCell.EditingStyle {
        return UITableViewCell.EditingStyle.delete
    }
    
    @IBAction func addCity(_ sender: Any) {
        let ac = UIAlertController(title: "Add City", message: nil, preferredStyle: .alert)
        let okAction = UIAlertAction(title: "OK", style: .default, handler: { action in
            let name = ac.textFields?.first?.text
            let desc = ac.textFields?.last?.text
            
            self.cityList.addCityObject(cityname: name!, description: desc!, image: "city.jpg")
            let indexPath = IndexPath(row: self.cityList.getCount()-1, section:0)
            self.tableView.beginUpdates()
            self.tableView.insertRows(at: [indexPath], with: .automatic)
            self.tableView.endUpdates()
        })
        let cancelAction = UIAlertAction(title: "Cancel", style: .cancel, handler: { action in})
        ac.addTextField(configurationHandler: { (textField) in
            textField.placeholder = "Enter City Name"
        })
        ac.addTextField(configurationHandler: { (textField) in
            textField.placeholder = "Enter City Description"
        })
        
        ac.addAction(okAction)
        ac.addAction(cancelAction)
        self.present(ac, animated: true)
    }
    
    
    // MARK: - Navigation

    // In a storyboard-based application, you will often want to do a little preparation before navigation
    override func prepare(for segue: UIStoryboardSegue, sender: Any?)
    {
        let selectedIndex:IndexPath = self.tableView.indexPath(for:sender as! UITableViewCell)!
        let city = cityList.getCityObject(item: selectedIndex.row)
        
        if(segue.identifier == "detailView")
        {
            if let viewController:DetailViewController = segue.destination as? DetailViewController {
                viewController.selectedCityName = city.cityName
                viewController.selectedCityImage = city.cityImage
                viewController.selectedCityDesc = city.cityDescription
            }
        }
    }
    

}
