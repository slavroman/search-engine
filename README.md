# **Search engine**
- [Description](#Description)
- [How to build and run](#How-to-build-and-run)
- [How does this work](#How-does-this-work)
- [Technologies](#Technologies)
- [License](#License)

## Description:
*This is a console application that performs searches and can be customized via JSON files.*

## How to build and run:
* **Step 1**
    * *Clone this repository on your pc use following command:*
        * HTTPS: ` https://github.com/slavroman/search-engine.git `
        * SSH: ` git@github.com:slavroman/search-engine.git `
        * GitHub CLI: ` gh repo clone slavroman/search-engine `
        
        *... or donload as **ZIP** file and unzip somewhere on your pc.*
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
    * *To run app go to source directory of build and run SearchEngine.exe*
        ```
        cd src
        SearchEngine.exe
        ```
    * *To run tests for app go to test directory of build and run GTests.exe*
        ```
        cd tests
        GTests.exe
        ```

## How does this work:
*Before running the application, you must specify the paths to the text files to search in the "files" section of the `config.json` file, as well as your requests in the "requests" section of the `requests.json` file. All JSON files are located in the "json" folder.*

*After launching the application, the `answers.json` file will appear in the "json" folder. It will contain the search results: Query number ("request###"), search result("true" or "false"), and a list of documents sorted by relevance*  
*(Note:"docid" 0 = file001.txt, "docid" 1 = file002.txt, etc.).*

*For example:*
* ***config.json***
    ```json
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
    ```json
    "requests": [
    		"moscow is the capital of russia",
    		"london",
    		"world"
    	]
    ```
* ***answers.json***   
    ```json   
    "answers": {
        "request001": {
            "result": true,
            "relevance": [
                {
                    "docid": 7,
                    "rank": 1.0
                },
                {
                    "docid": 0,
                    "rank": 0.667
                },
                {
                    "docid": 1,
                    "rank": 0.667
                },
                {
                    "docid": 2,
                    "rank": 0.667
                },
                {
                    "docid": 3,
                    "rank": 0.667
                }
            ]
        },
        "request002": {
            "result": true,
            "docid": 0,
            "rank": 1.0
        },
        "request003": {
            "result": false
        }
    }
    ```

## Technologies:
* [C++17](https://en.cppreference.com/w/cpp/17)
* [CMake 3.29.6](https://www.kitware.com/cmake-3-29-6-available-for-download/)
* [Nlohmann JSON Library](https://github.com/nlohmann/json)
* [GoogleTest Framework](https://github.com/google/googletest)

## License:
*Any other file of this project is available under the MIT license as follow:*  
*Copyright (c) 2024 Vyacheslav Romanenko (aka slavroman)*