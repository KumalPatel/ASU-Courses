//
//  TableViewCell.swift
//  Homework2
//
//  Created by Kumal Patel on 11/17/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit

class TableViewCell: UITableViewCell {

    @IBOutlet weak var cTitle: UILabel!
    @IBOutlet weak var cDescription: UILabel!
    @IBOutlet weak var cImage: UIImageView! {
        didSet {
            cImage.layer.cornerRadius = cImage.bounds.width / 2
            cImage.clipsToBounds = true
        }
    }
    override func awakeFromNib() {
        super.awakeFromNib()
        // Initialization code
    }

    override func setSelected(_ selected: Bool, animated: Bool) {
        super.setSelected(selected, animated: animated)

        // Configure the view for the selected state
    }

}
