# **Search engine**

## Description:
*This is a console application that performs searches and can be customized via JSON files.*

## How to build and run:
* **Step 1**
    *Clone this repository on your pc use following command:*
    * HTTPS: ` https://github.com/slavroman/search-engine.git `
    * SSH: ` git@github.com:slavroman/search-engine.git `
    * GitHub CLI: ` gh repo clone slavroman/search-engine `
    
    *... or donload as **ZIP** file and unpack somewhere on your pc.*
* **Step 2**
    * *Go to project folder:*
        ```
        cd search-engine
        ```
    * *Create folder for build and go to it:*
        ```
        mkdir build
        cd build
        ```
    * *Build the app:*
        ```
        cmake -G Ninja ..
        ninja -j1
        ```
        *... or select the generator and compiler you usually use.*
* **Step 3**
    * *To run app:*
        *Go to source directory of build and run SearchEngine.exe*
        ```
        cd src
        SearchEngine.exe
        ```
    * *To run tests for app:*
        *Go to test directory of build and run GTests.exe*
        ```
        cd tests
        GTests.exe
        ```

## How does this work:
*Before launching the application, you must specify the paths to the text files in which the search will be performed in the "files" section of the "config.json" file and your requests in the "requests" section of the "requests.json" file.*
*For example:*
* ***config.json***
    ```
    "files": [
    		"./resources/file001.txt",
    		"./resources/file002.txt",
    		"./resources/file003.txt",
    		"./resources/file004.txt",
    		"./resources/file005.txt",
    		"./resources/file006.txt",
    		"./resources/file007.txt",
    		"./resources/file008.txt",
    		"./resources/file009.txt",
    		"./resources/file0010.txt",
    		"./resources/file0011.txt",
    		"./resources/file0012.txt",
    		"./resources/file0013.txt",
    		"./resources/file0014.txt"		
    	]
    ```
* ***requests.json***
    ```
    "requests": [
    		"moscow is the capital of russia",
    		"london",
    		"world"
    	]
    ```

## This project based on:
* [C++17](https://en.cppreference.com/w/cpp/17)
* [CMake 3.29.6](https://www.kitware.com/cmake-3-29-6-available-for-download/)
* [Nlohmann JSON Library](https://github.com/nlohmann/json)
* [GoogleTest Framework](https://github.com/google/googletest)

## License:
*Any other file of this project is available under the MIT license as follow:*
*Copyright (c) 2024 Vyacheslav Romanenko (aka slavroman)*