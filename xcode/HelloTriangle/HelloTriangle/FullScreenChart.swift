//
//  FullScreenChart.swift
//  HelloTriangle
//
//  Created by Cesar Gomez on 09/03/21.
//

import Foundation
import UIKit

public class FullScreenChart : UIViewController{
    
    public var sampleView : UIView?
    
    override public func viewDidLoad() {
        super.viewDidLoad()
        
        
        sampleView = self.view;          // Pass the view to the sample code
        
        Test().setSampleView(sampleView)
        
        sample_mainFromCPP()         // Run the LunarG sample
    
    }
}
