
import Cocoa

func handle(data: Data?, response: URLResponse?, error: Error?){
    
}


let url = URL(string: "http://101.37.30.177/info/getDialectTypes")

let session = URLSession(configuration: .default)

let task = session.dataTask(with: url, completionHandler: handle(data: response: error:))

