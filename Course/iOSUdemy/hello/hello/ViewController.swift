//
//  ViewController.swift
//  hello
//
//  Created by Bill Chen on 2020/5/17.
//  Copyright © 2020 Bill Chen. All rights reserved.
//

import UIKit
import AVFoundation


class ViewController: UIViewController {

    @IBOutlet weak var btnHi: UIImageView!
    
    @IBOutlet weak var txtHi: UILabel!
    
    var player: AVAudioPlayer?
    
    var timer = Timer()
    
    func playNote(){

        print("I'm in a dream.")

        
    }
    
    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        let tap = UITapGestureRecognizer(target: btnHi, action: #selector(doubleTapped))
        tap.numberOfTapsRequired = 2

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
       
        
    }
}

