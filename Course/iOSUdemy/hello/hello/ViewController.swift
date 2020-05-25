//
//  ViewController.swift
//  hello
//
//  Created by Bill Chen on 2020/5/17.
//  Copyright © 2020 Bill Chen. All rights reserved.
//

import UIKit
import AVFoundation
import CoreLocation


class ViewController: UIViewController, UITextFieldDelegate {

    @IBOutlet weak var btnHi: UIImageView!
    
    @IBOutlet weak var txtHi: UILabel!
    
    @IBOutlet weak var txtMain: UITextField!

    var locationManager = CLLocationManager()

//MARK: - This is a section.
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        let tap = UITapGestureRecognizer(target: btnHi, action: #selector(doubleTapped))
        tap.numberOfTapsRequired = 2
        
        txtMain.delegate = self
        locationManager.delegate = self
        locationManager.requestWhenInUseAuthorization()
        locationManager.requestLocation()
    }
    
    @objc func doubleTapped() {
        print("I'm in a dream.")
    }
    
    var clickTime = 0

    @IBAction func btnMainClicked(_ sender: Any) {
       
        btnHi.image = #imageLiteral(resourceName: "westworld")
        let words = [
            "Is this real?",
            "Is it now?",
            "Thoso violent delights\n shall have violent ends.",
            "Tell me about this world,\nWilliam.",
            "You can’t play God without\nbeing acquainted with the devil.",
            "Dream means everything.",
            "An old friend once told me something that gave me great comfort.",
            "That which is real is irreplaceable.",
            "To grow we all need to suffer.",
            "Beauty is a lure.",
            "The maze itself is the sum of a man's life.",
            "There’s a path for everyone. And my path leads me back to you.",
            "You can’t play God without being acquainted with the Devil",
            "Evolution forged the entirety of sentient life on this planet using only one tool… The mistake."
        ]
        
        // txtHi.text = "\(clickTime): \n" + words[(Int(arc4random()) % words.count)]
        txtHi.text =  words[Int.random(in: 0...words.count - 1)]
        
        clickTime += 1
        txtMain.endEditing(true);
        
        

        let url = URL(string: "http://101.37.30.177/info/getDialectTypes")

        let session = URLSession(configuration: .default)

        let task = session.dataTask(with: url!, completionHandler: {(data, response, error) in
            if(error != nil){
                       print(error!)
                       return
                   }
            let dataString = String(data: data!, encoding: .utf8)
//            print(dataString!)
            
            struct dialectData: Decodable{
                let timestamp: String
            }
            
            do{
                let dict = try JSONSerialization.jsonObject(with: data!, options: [JSONSerialization.ReadingOptions.init(rawValue: 0)]) as? [String:AnyObject]
                
//                let datas = dict!["data"] as! [String:NSArray]
//                print(datas[0])
//
//                for i in 0...dict["data"]!.count {
//                    print(dict!["data"][i]["dialect_code"])
//                }

                print("pause")
            }
            catch {
                print(error)
            }
            
            
            let decoder = JSONDecoder()
            do{
                let decodedData = try decoder.decode(dialectData.self, from: data!)
                print(decodedData.timestamp)
            } catch {
                print(error)
            }
                
        })
        
        task.resume()
        
    }
    
    func textFieldDidEndEditing(_ textField: UITextField) {
        print(txtMain.text ?? "")
        textField.becomeFirstResponder()
    }
    
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool {
        if txtMain.text != ""{
            textField.endEditing(true)
            txtMain.text = ""
            return true
        } else {
            return false
        }
    }
    
}

//MARK: - Location manager

extension ViewController: CLLocationManagerDelegate {
    
    func locationManager(_ manager: CLLocationManager, didUpdateLocations locations: [CLLocation]) {
        if let location = locations.last {
            let lat = location.coordinate.latitude
            let lon = location.coordinate.latitude
            print(lat)
            print(lon)
        }

    }
    
    func locationManager(_ manager: CLLocationManager, didFailWithError error: Error) {
        print("fail")
    }
    
}
