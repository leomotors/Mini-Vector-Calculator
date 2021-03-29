# Mini Vector Calculator

  This program can do simple Vector Calculation.

## Related Project

<a href="https://github.com/Leomotors/Website-Vector-Calculator">Website Vector Calculator</a> (Developed from this repo.)

## Program's Features

### Vector Calculation

* Add Vectors

* Multiply Vector with scalar and vector

* Dot Product, Cross Product

* Project a vector on another

* Find area of parrallelogram under two vectors

### Extra Feature that help visualizing

* Import Vector Data from and Export to Files

* Set Number Precision (Number of digits after decimal point)

### Very Good Memory Management

  There is almost no memory leak in this program from testing so far.

* Tested using valgrind, however, some very small leaks are possible in rare case.

* Only applies on English Version

### Multilingual

* Support 3 Languages: English, Thai and Japanese

 __Note__: In Thai and Japanese Version, Import/Export Vector and setting Number Precision is unstable. Please avoid using them.

## How to Run Program

  Compile the source code and done!

  To use import/export function, VectorSave Folder must be in the same directory.

## Sample Vector Data to start with

  I've already put some sample vector data you can play with!

  These are generated using ```numpy```.

  Note: Use Import Vector Function to import them, but please avoid using them in TH,JP Version as it is unstable.

## Compatibility

Support both Windows and UNIX OS.

Compiler : C99 or above

Note : Thai and Japanese Version aren't supported in UNIX OS.

Note : ```-lm``` (Math Library) must be manually attached when compiling in UNIX OS.

## Version

  Version used to present to Teacher (Semester 1) : v1.3.0

  Current Release : v3.3

## Credits

### Initial Development : Version 1

  Developed as a group of 5, presenting to T.Wichai as Mini-Project.

  Subject : 「การเขียนโปรแกรม 1 (ง30221)」 Triam Udom Suksa School (2020/1)

    * Supervisor・Mentor・Core Programming : @Leomotors

    * Support Programmer : Others in Group

    * Present : Every person in the group except Mentor (@Leomotors)

  Presented on : 5 Oct 2020

  The result of this project is really satisfying! 👍

### Further Development : Version 2

  Developing alone with help from
  @Teproanyx, including his Safe Input Module. Big Thanks to him! 😊

  Also thank you to stackoverflow.

### Version 3 Development

  Developed further more to submit to T.Wichai again as improvement project.

  Note : Due to outgoing pandemic, there is no more work group.
   (For social distancing) So this work will done my me alone.

  Subject : 「การเขียนโปรแกรม 2 (ง30222)」 Triam Udom Suksa School (2020/2)
  
    * 制作監督 : @Leomotors

    * Helper・Reviewer : @Teproanyx
    
    * Honorable Mention : Stack Overflow

  Presented on : 3 March 2021
  
  Gained a lot from this!
  
### Special Thanks

  This Project uses Safe Input Module by @Teproanyx

## Program Version History

### Version 3 (Latest Version)

  **2021-03-03** Present Ready Update (3.3): Fixed many bugs. Program should be stable now

  **2021-03-01** Release 3.2: Seperate File (SafeInput.h) and Fatal Bug Fixes

  **2021-02-24** February Improvement Update (3.1): Upgrade to Double, Fix Mem Leak

  **2021-02-08** Multilingual Update (3.0): Add Thai and Japanese
  
  **2021-01-18 to 2021-02-08** Version 3 Development

### Version 2

  **2021-02-03** Release 2.4.1: Add License

  **2021-01-14** January 2021 Update (2.4): Overall Improvement

  **2020-12-26** SPEED Update (2.3): Program moved to C, gained SPEED

  **2020-12-18** December 2020 Update (2.2): Implemented Safe Input V3

  **2020-10-21** 2.1.2 & 2.1.2.1: Fix Memory Leaks
  
  **2020-10-21** 2.1.1: Misc Code Brushing and Readme Edit
  
  **2020-10-21** 2.1: Import Vector Function Change and New Function added

  **2020-10-21** 2.0: Finally release for Vector Version 2!

  **2020-10-16 to 2020-10-21**: Snapshot 2.0 Beta Development

### Version 1

Developed outside github
