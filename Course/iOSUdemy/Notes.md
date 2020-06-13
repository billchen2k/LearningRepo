# iOS Bootcamp from [Udemy](https://www.udemy.com/course/ios-13-app-development-bootcamp) ^Notes^

> William Chen
> 2020.5
>
> Source: https://www.udemy.com/course/ios-13-app-development-bootcamp

## Getting Started

How to QA?

1. What excepted
2. What actually happened
3. Screenshots

From September 2015, free account can employ the app to an actual device.

- App Store Connect:
  - Check the sales status & statistic of your own APP

### About Xcode

- Requires over 10 GB
- Newest version runs on Catalina
- **Don’t download a beta version**

### Storyboards and Interface builder

Story of *I am rich* app: $100 Dollar app to be removed.

#### Start from Storyboards

Choose a single view app:

![image-20200516232238422](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-16-image-20200516232238422-xU22iD.png)

Organization identifier: a reversed website

Most section: Project navigator

> Resources
>
> Color palete: **colorhunt.co**
>
> Find the resolution of iOS devices: **paintcodeapp.com**
>
> Used for finding colors

Elements are location by left-right corner:![image-20200517002507400](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-17-image-20200517002507400-nPp8Pf.png)

- Resolution: 1x, 2x, 3x:

  - Could start with a 3x version, and shrink it to 1x, 2x or 3x

  - > Generating image assets: **appicon.co**
    >
    > Making prototype: **canva.com**

#### Processing of app compiling

![img](https://i.udemycdn.com/redactor/raw/2019-10-17_14-18-57-1c7f89b1fb5df67f437fe9f6f6d62152.png)

- Matching Xcode and iOS version
  - Check the iOS version of the simulator (Updating both to the latest version should work)
- Sign the app: automatically manage signing
- Connecting via network: sometimes unstable

#### Responsive layout

- Size class: a kind of screen size

- Constaints: ![image-20200517020516606](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-17-image-20200517020516606-CEcjda.png) <u>Avoid safe areas</u>

<img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-17-image-20200517020925385-zmDrX9.png" alt="image-20200517020925385" style="zoom:50%;" />

- Alignment constraint, pinning constraint

  <img src="https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-17-image-20200517120853103-NA7ehs.png" alt="image-20200517120853103" style="zoom:50%;" />

- Trick: Split the whole screen into 3 sub views

  - Stack view: a view to group UIViews

> Dealing with procrastination:
>
> The more you feel, the more you delay.
>
> Just get the work started and don’t do too much work beforehead.

## Swift Language

### Overrals

- Switch statement: different from C, use `fallthrough` to go through
- Computed property
- `typealias`: Like `#DEFINE`
- Interface Builder Outlet: IB
  - Hold control button to create connections

```swift
print('String \(2+3) Interpolation')
```

![image-20200517015347338](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-17-image-20200517015347338-Rg9QOa.png)

Attention:

Apple has recently introduced a new headache for learner developers by limiting the number of apps you can side load on your physical device to 3 per week.

> Avoid distraction: it take time to get back to focus

- ==API = Application Programming Interface==

How to find the answer we need?

![image-20200517134238014](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-17-kwwkI7.png)

>Dealing with your habits
>
>Finde a **CUE**

- Progress View: Used to show progress for the users

#### Mutability

Using this key word to change let variables

```swift
mutating func change(){
	self.a = b
}
```

Self is `let` by default

#### Classes vs Struct

- Struct can’t inheritate
- Class is a blueprint to create an entity in it.

### Optionals

Ways to unwrapping:

![image-20200520230128619](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-20-vHrdhb.png)

Check for nil value: safer way than force unwrapping

Optional Binding: using `if let` clause to create a safeOptional

Using nil coalescing to offer a fallback value

**Optional chaining** - used for struct

### Protocol

(Like interface in Java)

- Can’t have function bodies (Can be implemented by `:`)
- **Protocol can be used as a datatype**

### Closures

`Class: superclass, protocol`

- Closures - Anonymous function is introduced to deal with `completionHandler`

- ![image-20200524165158482](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-24-ZC8RF1.png)

  - Use `$0` to identify the first parameter - Eg.
  - ![image-20200524164717271](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-24-5rUtAf.png)
- ==Trailing colosure== Rule: if the last parameter is a closure, this can be put outside the barces
  - `let result = calcullator(n1:2, n2: 3) {$0 * $1}`
  - Another example: `array.map({$0 + 1})`

### Extensions

Used to extend current code. With key word **`extension`**

- Object: can be Foundation Data Types, structs, classes.

- Eg:

- ```swift
  extension Double {
      func round(to places: Int){
          ...
      }
  }
  
  var myDouble = 3.1415926
  myDouble.round(to: 3)
  ```

- Non-open source classes can also be extended.
- ==Extension to protocol==: Offer a default implementation of methods. (In this way optional delegate can be implemented)
- Also a good way to refactor View Controllers to simplify the code.

> **Enhanced comments:**
>
> `//MARK: - UITextFiledDelegate`
>
> **Create your own code snippets**:
>
> Right click and then click create, use `<#...#>` to create placeholders

## APP Structure and Patterns

![image-20200518213219463](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-18-uvJEJV.png)

### MVC Design Pattern

A common solution 

- Model, View & Controller
- ![image-20200518213323960](../../../../../Library/Application%20Support/typora-user-images/image-20200518213323960.png)

### Delegate Design Pattern

Integrate with protocols To reach maximum reusability:

![image-20200523021822248](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-23-yY11Zn.png)

#### Naming Conventions

Some examples to make code more readable:

- `performRequest(with: weatherData)`
- `parseJSON(_ weatherData: Data) -> ...`
- Begin with did/should: `didFailUpdate()`

### View Controller

`CoreGraphicRectancle : CGRect`: Used for defining the location of one component

#### Navigation

- ![image-20200520224807990](../../../../../Library/Application%20Support/typora-user-images/image-20200520224807990.png)

`as! ResultViewController`: Override the class inheriting relations

- To navigate back to the last view: `self.dismiss(animated: true, complition:nil)`
- ![image-20200520225220904](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-20-MnOGJB.png) 3D Button to check your UI stack

#### Dipatch Queue

Note that UI Update must come from **MAIN THREAD** (Long-running tasks such as networking are often executed in background.)

Solution: `DispatchQueue.main.async{...}`

![image-20200524180743170](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-24-mwkZ4L.png)



>
> Tips from Angela: **Learning before you eat.**
>
> Dealing with lack of progress

## Intergrade App Design

### Delegate

Eg. `UITextFieldDelegate`: Used to handle go button

```swift
searchTextFiled.delegate = self

func textFiledShouldReturn(_ textField: ...) -> Bool {
    // Some code
}
```

Should: happens before try / Did: Happened after execution

### Network & API

#### Retrieving Data

Use URL Session to handle API:

Steps: Create URL -> Create URLSession -> Give the session a task -> Start the task

- **The URL must use https protocol**

```swift
let url = URL(string: "http://101.37.30.177/info/getDialectTypes")

let session = URLSession(configuration: .default)

let task = session.dataTask(with: url!, completionHandler: handle(data:response:error:))

task.resume()

}

func handle(data: Data?, response: URLResponse?, error: Error?){
    if(error != nil){
        print(error!)
        return
    }
    let dataString = String(data: data!, encoding: .utf8)
    print(dataString)

}
```

#### JSON Decoding

- Use `JSONDecoder()`

- Build an instruct, then decode

- ```swift
  struct dialectData: Decodable{
      let timestamp: String
  }
  
  let decoder = JSONDecoder()
  do{
      let decodedData = try decoder.decode(dialectData.self, from: data!)
      print(decodedData.timestamp)
  } catch {
      print(error)
  }
  ```

- Another way:
	-  ```swift
    let dict = try JSONSerialization.jsonObject(with: data!, options: [JSONSerialization.ReadingOptions.init(rawValue: 0)]) as? [String:AnyObject]
    ```

> Using SFSymbols image:
>
> `UIImage(systemName: cloud.full)`



## Swift APIs

### Core Location

A location manager. Authorization need to be requested first.

(Edit in info.plist: `Privacy - Location When In Use Usage Description`)

> Plist: Property List - a file created by Xcode which stores configuration

- Use `CLLocationManagerDelegate`, fail and did must be implemented.
- Don’t forget to `locationManager.stopUpdatingLocation` after fetching the data in need.

> Tips from Angela:
>
> **Mixing different areas of knowledge:** a process of solidifying the knowledge
>
> **Dealing with frustrating:** Take a break and then look back, don’t runaway



## SwiftUI

- An declarative UI Framework, WWDC 2019

- Highly Reusable UI: Layouts can be highly reusable![image-20200611001549327](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-06-11-WnoF3P.png)

  Changing stack into list… Reusing makes us creating reusable.

- Cross Platform - Same app for iWatch, iOS and macOS -> Project Catalyst

`ContentView.previewDevice`

Finding the default value: `ENTER`

```swift
VStack // Verticle Stack
ZStack {
    Color(red: ..., green:..., blue:...)
}

```

### Custom Styles & Advanced

> [https://flatuicolors.com](https://flatuicolors.com) - used to find colors
>
> https://uicolor.xyz - Convert hex color to UI color

- Using Custom Font: `Text(…).font(Font.custom("", size: 40))`

![image-20200611003136948](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-06-11-AtDiGV.png)

- Clipping the image: `Clip Shape`, add it to the Image object

- Overlay: Overlay can be a circle, text:

  - ```swift
    .overlay(Text("...").foregroundColor(.black))
    ```

- Using system image: `Image(systemName: "phone.fill")`
- **Previewing the image:**

![image-20200611004323824](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-06-11-Ksat2u.png)

- `@State` Allow us to change the view wherever the property changes

- `DispatchQueue.main.async` {} This closure happens asyncally