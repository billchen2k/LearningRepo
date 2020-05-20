# iOS Bootcamp from [Udemy](https://www.udemy.com/course/ios-13-app-development-bootcamp)^Notes^

> William Chen
> 2020.5

## Getting Started

How to QA?

1. What excepted
2. What actually happened
3. Screenshots

From September 2015, free account can employ the app to an actual device.

- App Store Connect:
  - Check the sales

### About Xcode

- Requires over 10 GB
- Newest version runs on Catalina
- **Don’t download a beta version**

## Storyboards and Interface builder

Story of *I am rich* app: $100 Dollar app to be removed.

### Start from Storyboards

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

### Processing of app compiling

![img](https://i.udemycdn.com/redactor/raw/2019-10-17_14-18-57-1c7f89b1fb5df67f437fe9f6f6d62152.png)

- Matching Xcode and iOS version
  - Check the iOS version of the simulator (Updating both to the latest version should work)
- Sign the app: automatically manage signing
- Connecting via network: sometimes unstable

### Responsive layout

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

### Mutability

Using this key word to change let variables

```swift
mutating func change(){
	self.a = b
}
```



## APP Structure and Patterns

![image-20200518213219463](https://billc.oss-cn-shanghai.aliyuncs.com/img/2020-05-18-uvJEJV.png)

### MVC Design Pattern

- Model, View & Controller![image-20200518213323960](../../../../../Library/Application%20Support/typora-user-images/image-20200518213323960.png)


