//
//  ContentView.swift
//  HelloTriangle
//
//  Created by Cesar Gomez on 01/03/21.
//

import SwiftUI


struct ContentView: View {
    var body: some View {
        //C function called from Swift
        //let area = CircleAreaFromCPP(5.0)
        
        //let name : NSString = "Cesar"
        //let name_p = UnsafeMutablePointer<CChar>(mutating: name.utf8String)
        
        //var greet = HelloWorldFromCPP(name_p)
        
        //Text("Hello, world!").padding()
        
        //Text("MyMathPlain area: " + String(area)).padding()
        
        //Text("MyMath message: " + String(greet)).padding()
        
        //--------------------------------------------------
        
        Text("Hello, world!").padding().onTapGesture(count: 1, perform: {
            let test = Test.init()
        })
        
        
        
    }
}

struct ContentView_Previews: PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
