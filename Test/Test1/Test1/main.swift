//
//  main.swift
//  Test1
//
//  Created by Henrik Swahn on 2016-01-27.
//  Copyright © 2016 Henrik Swahn. All rights reserved.
//

import Foundation

var MAX_SIZE = 1000000;
var set = [UInt32?](count: MAX_SIZE, repeatedValue: nil);

for(var i = 0; i < MAX_SIZE; i++) {
    set[i] = arc4random();
}

func swapNumbers(index1 :Int,index2: Int) {
    let temp = inputArr[index1]
    inputArr[index1] = inputArr[index2]
    inputArr[index2] = temp
}
for var index: Int = inputArr.count–1; index > 1; –index {
    for var jIndex: Int = 0; jIndex < index; ++jIndex {
        if inputArr[jIndex] > inputArr[jIndex + 1] {
            swapNumbers(jIndex, jIndex+1)
        }
    }
}

print("Hej");

