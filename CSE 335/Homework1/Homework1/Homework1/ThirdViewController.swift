//
//  ThirdViewController.swift
//  Homework1
//
//  Created by Kumal Patel on 10/18/20.
//  Copyright © 2020 Kumal Patel. All rights reserved.
//

import UIKit
import CoreData
import Charts

class ThirdViewController: UIViewController, ChartViewDelegate {

    var managedObjectContext: NSManagedObjectContext?
    var MVC:Model?
    var list:[DailyHealth]?
    var days = ["Day 1", "Day 2", "Day 3", "Day 4", "Day 5", "Day 6", "Day 7"]
    var sBloodData = [Int64]()
    var dBloodData = [Int64]()
    var weightData = [Int64]()
    var sugarData = [Int64]()

    
    @IBOutlet weak var barChart: BarChartView!
    
    override func viewDidLoad() {
        super.viewDidLoad()
        fetchData()
        sBloodData = getDataSet(arr: list!, type: "sBlood")
        dBloodData = getDataSet(arr: list!, type: "dBlood")
        weightData = getDataSet(arr: list!, type: "weight")
        sugarData = getDataSet(arr: list!, type: "sugar")
        
        barChart.delegate = self
        
        if(list?.count != 7) {
           // display error
           let alert = UIAlertController(title: "Error", message: "Not Enough Entries", preferredStyle: .alert)
           alert.addAction(UIAlertAction(title: "OK", style: .default, handler: nil))
           self.present(alert, animated: true, completion: nil)
        }
        else {
            updateChartData()
        }
    }
    
    func fetchData() {
        do {
            self.list = try managedObjectContext!.fetch(DailyHealth.fetchRequest())
        }
        catch {
        }
    }
    
    func updateChartData() {
        //legend
        let legend = barChart.legend
        legend.enabled = true
        legend.horizontalAlignment = .right
        legend.verticalAlignment = .top
        legend.orientation = .vertical
        legend.drawInside = true
        legend.yOffset = 10.0
        legend.xOffset = 10.0
        legend.yEntrySpace = 0.0
        
        //x-axis
        let xAxis = barChart.xAxis
        xAxis.drawGridLinesEnabled = false
        xAxis.valueFormatter = IndexAxisValueFormatter(values: self.days)
        xAxis.labelPosition = .bottom
        xAxis.centerAxisLabelsEnabled = true
        xAxis.granularityEnabled = true
        xAxis.granularity = 1.0
        
        // y-axis
        let yAxis = barChart.leftAxis
        yAxis.spaceTop = 0.35
        yAxis.axisMinimum = 0
        yAxis.drawGridLinesEnabled = false
        barChart.rightAxis.enabled = false

        // data entries for each day of the week
        var dataEntries1: [BarChartDataEntry] = []
        var dataEntries2: [BarChartDataEntry] = []
        var dataEntries3: [BarChartDataEntry] = []
        var dataEntries4: [BarChartDataEntry] = []
        
        for i in 0..<days.count {
            let dataEntry1 = BarChartDataEntry(x: Double(i), y: Double(sBloodData[i]))
            let dataEntry2 = BarChartDataEntry(x: Double(i), y: Double(dBloodData[i]))
            let dataEntry3 = BarChartDataEntry(x: Double(i), y: Double(weightData[i]))
            let dataEntry4 = BarChartDataEntry(x: Double(i), y: Double(sugarData[i]))
            
            dataEntries1.append(dataEntry1)
            dataEntries2.append(dataEntry2)
            dataEntries3.append(dataEntry3)
            dataEntries4.append(dataEntry4)
        }
        
        let  chartDataSet1 = BarChartDataSet(entries: dataEntries1, label: "Systollic Blood")
        let  chartDataSet2 = BarChartDataSet(entries: dataEntries2, label: "Diastollic Blood")
        let  chartDataSet3 = BarChartDataSet(entries: dataEntries3, label: "Weight")
        let  chartDataSet4 = BarChartDataSet(entries: dataEntries4, label: "Sugar Level")
        
        let dataSets: [BarChartDataSet] = [chartDataSet1, chartDataSet2, chartDataSet3, chartDataSet4]
        
        // colors
        chartDataSet1.colors = colorsOfCharts(numberOfColor: 1)
        chartDataSet2.colors = colorsOfCharts(numberOfColor: 1)
        chartDataSet3.colors = colorsOfCharts(numberOfColor: 1)
        chartDataSet4.colors = colorsOfCharts(numberOfColor: 1)
        
        let chartData = BarChartData(dataSets: dataSets)
        
        // removes labels above bar
        chartData.setDrawValues(false)
    
                
        // format bars
        chartData.barWidth = 0.2
        barChart.xAxis.axisMinimum = 0.0
        barChart.xAxis.axisMaximum = Double(0.0) + (chartData.groupWidth(groupSpace: 0.1, barSpace: 0.02)) * Double(self.days.count)
        
        chartData.groupBars(fromX: 0.0, groupSpace: 0.1, barSpace: 0.02)
        
        // plot data
        barChart.data = chartData
    }
    
    func getDataSet(arr: [DailyHealth], type: String) ->[Int64] {
        var array = [Int64]()
        
        for key in arr {
            if(type == "sBlood") {
                array.append(key.sBlood)
            }
            else if(type == "dBlood") {
                array.append(key.dBlood)
            }
            else if(type == "weight") {
                array.append(key.weight)
            }
            else {
                array.append(key.sugarLevel)
            }
        }

        
        return array
    }
 
    private func colorsOfCharts(numberOfColor: Int) -> [UIColor] {
        var colors: [UIColor] = []
        for _ in 0..<numberOfColor {
            let red = Double(arc4random_uniform(256))
            let green = Double(arc4random_uniform(256))
            let blue = Double(arc4random_uniform(256))
            let color = UIColor(red: CGFloat(red/255), green: CGFloat(green/255), blue: CGFloat(blue/255), alpha: 1)
            colors.append(color)
        }
        return colors
    }
}
