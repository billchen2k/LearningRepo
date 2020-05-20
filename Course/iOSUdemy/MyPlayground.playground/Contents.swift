
import Cocoa

class William {

    let favNum :[Int] = [3, 6, 9]

    var greeting : String? {
        get{
            return "Hello, \(self.name)!"
        }
    }

    var name: String {
        willSet {
            print("You wanna change my name?")
        }

    }

    init() {
        self.name = "Bill Chen"
        print(self.greeting!)
    }
}

var will = William()
will.name = "Dolores"
print(will.greeting!)


