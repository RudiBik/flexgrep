# Flexgrep 💪
Flexgrep is an extensible library that provides an interface for searching for files in a filetree that match certain criterions. Those criterions can be based on the files meta data (filename, size, binary or not, ...) and/or on the files content. The library is designed in a way to allow easy extension and flexibility. The provided implementation for the content filter is focused on normal "grepping" on text files using regular expressions, but can be easily extended to support filtering images or any type of files using some appropriate filtering criterions.
Two CMake targets are contained in this repository. The library providing the search interface "flexgrep_lib" and a CLI application using the library to allow grepping using a similar interface like the normal linux grep tool.

This is a hobby project from my time as a master student focusing on learning more about:
- Designing a flexible and extensible system
- System design using UML
- Cross platform development with C++ (Linux / Mac / Windows)
- Multithreading (Content filtering is parallelized)

Now after a few years I have got the desire to finish the project. The commits from 2022 are about implementing the multithreaded content filtering and polishing the other parts of the library.


# Getting Started
<details>
<summary>Linux</summary>
  
```
git clone https://github.com/RudiBik/flexgrep.git
cd flexgrep
mkdir build && cd build
cmake ..
make
  
./tests/tests                                   # running unit tests
  
./src/flexgrep [options] rootDirectory regex    # Running the CLI application for grepping
./src/flexgrep ~/ include                       # example search => Find all files containing the word 'include' in the home folder
```
  
</details>

<details>
<summary>Windows</summary>
  
Clone the repo with visual studio community edition
  
Run cmake and build
  
</details>

<details>
<summary>Mac</summary>
  
```
TODO
```

</details>


# Architecture
In the following sections the architecture and design desicions are documented going from top to bottom taking a look at the highest level data flow and the core classes and their relationships.


## Library
On the highest level the library takes a configuration and an output iterator as input and pushes all files matching the configured filters to the output iterator

### Input / Output
Input
- Configuration
  - Root search directory
  - Filename wildcard
  - Content regex
  - (More optional parameters)
- Output Iterator (Template)

Output
- The filepath of all matching files pushed to the output iterator

The data flow is represented in the following component diagram going from right to left:
![alt text](https://github.com/RudiBik/flexgrep/blob/master/doc/images/component-diagram-flexgrep.png?raw=true)
Basically the main thread will go through the directory tree recursively, filter each file by it's meta data like it's filename and pushing the matching files to the IContentProcessor where they are filtered by their content and pushed to the output iterator when matching.


### Extensibility
The main goal of this library is extensibility, so the following components are flexible and configurable:

- Output Iterator:
The output iterator is templated allowing the output to go to different destinations. For example, it is possible to use a stream output iterator on cout to print the results to the command line, or use a stream iterator on a file or use an output iterator on some container, pushing the output to the container. For the CLI application the output is pushed to cout. It would be possible to develop a GUI application by pushing the output to some container and using it in the GUI application.

- Meta Filters:
The IMetaFilter interface has only one method which takes a reference to the metadata of a file and returns a boolean. The library uses a vector of such filters that are applied to each file parsed in the directory tree. The number and type of filters depends on the configuration provided to the library

- Content Filters:
The IContentFilter interface also has only one method taking a pointer to a file loaded into memory. It contains the metadata and the content of the file loaded into a byte array making the interface very flexible.
Since only the byte array is provieded the implementation of this interface can parse text / image or any type of file and filter it's content by some criterion. Currently only one implementation for this interface is provided which parses text files and filters them by using a regex.


### Directory traversing
The core part of the library that is not flexible is the traversing logic of the provided filetree. In this part directories, regular files and symlinks are distinguished and the processing logic is depicted in the following activity diagram:
![alt text](https://github.com/RudiBik/flexgrep/blob/master/doc/images/activity-diagram-mainthread.png?raw=true)


### Class Diagram
The following class diagram depicts the most important classes and their relationship:
![alt text](https://github.com/RudiBik/flexgrep/blob/master/doc/images/class-diagram.png?raw=true)

Most important are the two classes in the middle: flexgrep and IContentProcessor

flexgrep contains the logic for traversing the directory tree like already described above and applying the configured meta filters to the meta data of each traversed file. For each matching file the content of the file is loaded into memory and the file is pushed to the IContentProcessor.

The IContentProcessor interface takes an output iterator on construction and only has two methods. One for receiving loaded files from the main thread and another for joining with the main thread. The join method is needed to allow a multithreaded implementation of this interface. The received files are filtered using a configured IContentFilter and pushed to the output iterator when matching.
The multithreaded implementation (ParallelContentFilter) of this interface uses a reader and writer view on shared data to allow safe processing.


### Parallelization
The main idea is to have the mainthread do the traversing of the filetree and matching each file directly with the meta data filters. Only matching file are then loaded into memory and pushed to a shared data structure. All other threads work on this data structure filtering the contents of the files and pushing matching files to the output iterator and unloading the files.

The shared data is just a vector of pointers pointing to the files matching the meta filters and loaded into memory. On construction the ParallelContentProcessor spawns threads based on the number of available threads and assigns each one a ReaderView which specifies on which parts of the shared data structure this thread is allowed to read. At the same time it creates a WriterView which is used by the main thread to push new files to the shared data.
The shared data is protected using a mutex. The usage of the mutex is minimized by designing the reader and writer views in a way that minimizes potential conflicts.



### CLI application
The CLI application provides an easy command line interface to grep for files. It parses the command line arguments, fills a configuration class based on them and passes this configuration and an output stream iterator on cout to the library which will then take care of doing the filtering and pushing the output.

The data flow is displayed in the following component diagram going from right to left:
![alt text](https://github.com/RudiBik/flexgrep/blob/master/doc/images/component-diagram-main.png?raw=true)
Basically we parse the incoming command line arguments, turn them into a configuration filling a class providing by the library. Create an output stream iterator on cout and provide the configuration and the output iterator to the library letting it process the provided directory tree and pushing the matching filepaths to the output iterator.  





# Extending the library and future ideas

## Extensible parts
Like described above there are three flexible and extensible parts in this library: The output destination, the meta filters and the content filters.

The output iterator allows streaming the passing filepaths to different locations. One possible extension is to create another GUI project which uses the library to filter files based on some configuration provided through a GUI and directing the output to some std container which can be used by the GUI tool to visualize the filepaths and their content. Another easy extension could be creating a filestream output iterator and forwarding the output of the CLI application to a file.

The meta and content filter interfaces allow the filtering of any type of file. To make usage of this first of all the configuration needs to be extended allowing the user to specify a search mode (e.g. text regex filtering, image comparison filtering, ...) and the configuration for that search mode. Then appropriate meta and content filters need to be implemented that are activated by the provided configuration. 

A direct example could be an image filter. The user could provide an image file and a "similarity threshold" and the library would output all image files in the directory tree that are very similar to the provided file. To implement this first of all the configuration needs to be extended, replacing the regex by a filepath to some image. Then a meta filters needs to be provided that only matches image files that are supported by the content filter. And a content filter implementation would be needed that uses some third party library to parse the binary image data coming from the main thread and comparing it to the initial image provided by the user. 

## Plugin Framework
To make the needed changes for extension more user friendly a plugin framework could be implemented. A plugin would be a library that provides three parts:
- A content filter implementation
- A vector of meta filters (making sure the right files arrive at the content filter)
- A configuration class (extending the core configuration for tree traversal and making sure the right meta and content filters are used in the library)

Having this the library could match some keyword provided by the user configuration to a plugin. Then the appropriate plugin is loaded, the plugin specific user configuration parsed and the appropriate filters created automatically making the library very extensible for different file types and filters. Only the core tree traversal logic and it's configuration are shared between all modes and plugins.


