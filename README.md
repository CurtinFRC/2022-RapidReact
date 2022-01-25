# 2022-RapidReact
Our code for FRC 2022: RAPID REACT, using multiproject Gradle, supporting CJ-Vision and WML code

# Project Setup

### All Platforms
1. Follow the guide for installing wpilibsuite https://docs.wpilib.org/en/stable/docs/zero-to-robot/step-2/wpilib-setup.html. Be aware of the version you install, as it must be the same as the version for this project, (E.g, `2021.3.1`)

- Note, this is not required if you already have a compiler (VisualCpp/Clang/Gcc) & Java already installed as gradle will download the necessary dependencies for you

### Windows
1. Download Java (JDK 11 for best support https://www.oracle.com/java/technologies/javase-jdk11-downloads.html)


2. "Desktop development with C++" from VS required for local debugging and simulation support https://visualstudio.microsoft.com/downloads/

3. After this is complete you can fork or clone the project recursivly to grab the submodules needed for this project. `git clone --recurse-submodules https://github.com/CurtinFRC/2022-RapidReact.git`


### Linux
1. Linux requires the build-essentials (GCC, CMake, etc...)

2. After this is complete you can fork or clone the project recursivly to grab the submodules needed for this project. E.g `git clone --recurse-submodules https://github.com/CurtinFRC/2022-RapidReact.git`

### Mac
1. Download Xcode from the app store https://apps.apple.com/au/app/xcode/id497799835?mt=12

2. After this is complete you can fork or clone the project recursivly to grab the submodules needed for this project. `git clone --recurse-submodules https://github.com/CurtinFRC/2022-RapidReact.git`

## Project Install/Build

1. Next we will need to download the roborio toolchain to cross compile the program for linuxathena. (All code in this project by a minimum must compile linuxathena)
	- Navigate to the root directory of this project and run `./gradlew installRoboRioToolchain`

2. Build the project
	- Run `./gradlew build` to build and compile all gradle projects
	- (Note: you can run `./gradlew <PROJECT>:build` to build a single project)

3. Inside each projects `build.gradle` (I.e [build.gradle](4788/build.gradle)) consists of options on how that project should compile. If desktop support is disabled then the project will only compile and publish shared and static linuxathena builds. If enabled, the project will build for both linuxathena and the current platform. I.e `windowsx86-64` & `linuxathena`.

# Main Project

## Commands (Robot)

- Build robot code using `./gradlew 4788:build`
- Deploy robot code using `./gradlew 4788:deploy`
- To simulate (in development) use `./gradlew 4788:sim`


## Commands (Vision)

- Generate Framework using `./gradlew CJ-Vision:generateFramework`
- Build vision code using `./gradlew CJ-Vision:build`
- Deploy vision code using `./gradlew CJ-Vision:deploy`
- Debug Vision code using `./gradlew CJ-Vision:runVision`

## Commands (All)

### All code is all subprojects contained in this main proect (E.g, 4788, CJ-Vision, TreasureMapper  etc...)

- Clean all code using `./gradlew clean`
- Build all code using `./gradlew build`
- Deploy all code using `./gradlew deploy`

- You may still use a single command for one subproject given the command only exists within that subproject. I.E `./gradlew runVision` will only run vision code.

# Libs

### View libraries used and extra documentation
- WML: https://github.com/wml-frc/WML
- CJ-Vision: https://github.com/wml-frc/CJ-Vision

### Doxygen

- Generate docuementation for project using `./gradlew doxygen`
- Locally, you can view the documentation in `build/docs/html/index.html`

- You can also view the generated documentation by going to [azure](https://dev.azure.com/ConnorBuchel0890/CurtinFRC/_build) slecting the desired project then the latest successful build. Then clicking the published artifact and downloading the zip folder.
