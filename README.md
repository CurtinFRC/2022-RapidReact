# 2022-RapidReact
Our code for FRC 2022: RAPID REACT, using multiproject Gradle, supporting CJ-Vision and WML code

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

### Doxygen

- Generate docuementation for project using `./gradlew doxygen`
- Locally, you can view the documentation in `build/docs/html/index.html`

- You can also view the generated documentation by going to [azure](https://dev.azure.com/ConnorBuchel0890/CurtinFRC/_build) slecting the desired project then the latest successful build. Then clicking the published artifact and downloading the zip folder.