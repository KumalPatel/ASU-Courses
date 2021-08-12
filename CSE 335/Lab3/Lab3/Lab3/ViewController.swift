//
//  ViewController.swift
//  Lab3
//
//  Created by Kumal Patel on 9/19/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class ViewController: UIViewController {
    @IBOutlet weak var titleInput: UITextField!
    @IBOutlet weak var genreInput: UITextField!
    @IBOutlet weak var ticketInput: UITextField!
    
    @IBOutlet weak var searchedTitle: UITextField!
    @IBOutlet weak var searchedGenre: UITextField!
    @IBOutlet weak var searchedTicket: UITextField!
    
    // create dictionary that stores movie info
    var movieD:movieDictionary = movieDictionary()
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
    }
    
    @IBAction func addRec(_ sender: UIBarButtonItem) {
        // check if fields are empty
        if let titleR = titleInput.text,
            let genreR = genreInput.text,
            let ticketR = Float(ticketInput.text!)
        {
            // create movie record
            movieD.add(title: titleR, genre: genreR, ticket: ticketR)
            
            // remove entries from text fields
            self.titleInput.text = ""
            self.genreInput.text = ""
            self.ticketInput.text = ""
        }
        else
        {
            // if no entries were entered
            let alert = UIAlertController(title: "Input Error", message: "Input is either empty or invalid", preferredStyle: .alert)
            
            alert.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
            self.present(alert, animated: true)
        }
    }
    @IBAction func delRec(_ sender: UIBarButtonItem) {
        // create delele alertcontroller
        let ac = UIAlertController(title: "Delete Record", message: "", preferredStyle: .alert)
        let deleteAction = UIAlertAction(title: "Delete", style: .default, handler: { (action) in
            let movieT = ac.textFields![0] as UITextField
            if let movie = movieT.text {
                if self.movieD.search(title: movie) != nil { // movie is found
                    self.movieD.delete(title: movie)
                }
                else {
                    let error = UIAlertController(title: "Error", message: "Entry is of incorrect data type or does not exist in our records", preferredStyle: .alert)
                    error.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
                    self.present(error, animated: true)
                }
            }
        })
        ac.addTextField(configurationHandler: { (textField) in
            textField.placeholder = "Enter Movie to be Deleted"
        })
        let cancelAction = UIAlertAction(title: "Cancel", style: .default, handler: nil)
        ac.addAction(deleteAction)
        ac.addAction(cancelAction)
        self.present(ac, animated: true)
    }
    @IBAction func searchRec(_ sender: UIBarButtonItem) {
        // display alertController for user input to search
        
        let alert = UIAlertController(title: "Search Record", message: "", preferredStyle: .alert)
        
        let searchAction = UIAlertAction(title: "Search", style: .default, handler: { (action) in
        
            let txt = alert.textFields![0] as UITextField
            if txt.text! != "" {
                let currMovie = txt.text!
                if let movieS =  self.movieD.search(title: currMovie){
                    self.searchedTitle.text = movieS.title!
                    self.searchedGenre.text = movieS.genre!
                    self.searchedTicket.text = String(movieS.ticket!)
                }
                else{
                        // display error message
                    let errorMsg = UIAlertController(title: "Error", message: "Invalid Entry: entry does not exist in our records", preferredStyle: .alert)
                    
                    errorMsg.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
                    self.present(errorMsg, animated: true)
                    
                    // clear textfields
                    self.searchedTitle.text = ""
                    self.searchedGenre.text = ""
                    self.searchedTicket.text = ""
                }
            }
        })
        alert.addTextField(configurationHandler: { (textField) in
            textField.placeholder = "Enter Movie Title"
            })
        let cancelAction = UIAlertAction(title: "Cancel", style: .default)
        alert.addAction(searchAction)
        alert.addAction(cancelAction)
        self.present(alert, animated: true)
    }
    
    @IBAction func editRec(_ sender: UIBarButtonItem) {
        // create alertController for edit entry
        let ac = UIAlertController(title: "Edit Entry", message: "", preferredStyle: .alert)
        let editAction = UIAlertAction(title: "Update", style: .default, handler: { (action) in
            let entry = ac.textFields![0] as UITextField
            if let ticketP = Float(entry.text!) {
                // find entry in dictionary, and change
                let movie = self.movieD.search(title: self.searchedTitle.text!)
                movie!.ticket = ticketP
                
                // update textfields
                self.searchedTicket.text = String(ticketP)
            }
            else{
                // display alert that changes could not be made
                let error = UIAlertController(title: "Error", message: "Invalid data type update could not be made to this entry", preferredStyle: .alert)
                
                error.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
                self.present(error, animated: true)
            }
        })
        ac.addTextField(configurationHandler: { (textField) in
            textField.placeholder = "Enter New Ticket Sale"
        })
        
        let cancelAction = UIAlertAction(title: "Cancel", style: .default, handler: nil)
        ac.addAction(editAction)
        ac.addAction(cancelAction)
        self.present(ac, animated: true)
    }
    
    @IBAction func navRec(_ sender: UIBarButtonItem) {
        // create alertController for prev and next
        let ac = UIAlertController(title: "", message: "", preferredStyle: .actionSheet)
        let prevAction = UIAlertAction(title: "Prev", style: .default, handler: { (action) in
            for (index, dict) in self.movieD.movieRecords.enumerated() {
                print("\(index): \(dict)")
            }
            if(self.movieD.pos == 0) {
                let warning = UIAlertController(title: "", message: "Showing the First Record", preferredStyle: .alert)
                warning.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
                self.present(warning, animated: true)
            }
            else{
                print("\nPos: \(self.movieD.pos)")
                let prevMovie = self.movieD.prev()
                self.searchedTitle.text = prevMovie?.title
                self.searchedGenre.text = prevMovie?.genre
                self.searchedTicket.text = "\(prevMovie?.ticket ?? 0)"
            }
        })
        let nextAction = UIAlertAction(title: "Next", style: .default, handler: { (action) in
           for (index, dict) in self.movieD.movieRecords.enumerated() {
               print("\(index): \(dict)")
           }
            if(self.movieD.pos == self.movieD.movieRecords.count-1){ // no more records
                let record = UIAlertController(title: "Error", message: "No More Records", preferredStyle: .alert)
                record.addAction(UIAlertAction(title: "Ok", style: .default, handler: nil))
                self.present(record, animated: true)
            }
            else {
                let nextMovie = self.movieD.next()
                self.searchedTitle.text = nextMovie?.title
                self.searchedGenre.text = nextMovie?.genre
                self.searchedTicket.text = "\(nextMovie?.ticket ?? 0)"
            }
        })
        let cancelAction = UIAlertAction(title: "Cancel", style: .default, handler: nil)
        ac.addAction(prevAction)
        ac.addAction(nextAction)
        ac.addAction(cancelAction)
        self.present(ac, animated: true)
    }
    
    
    
    


}


