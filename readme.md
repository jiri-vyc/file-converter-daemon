# Converter Daemon for TPX3 Data

Very lightweight watcher written in node.js, which checks if any new files are added to specified folder and any of its subfolders. If yes, automatically converts them into ROOT format.

## Overview

The TPX3 Converter Daemon is a tiny node.js program, which uses [chokidar](https://github.com/paulmillr/chokidar) for native watching of file system events and [NeDB](https://github.com/louischatriot/nedb) as its own minimalistic JSON-based persistant storage (database) for logging and synchronization purposes.

With help with these packages, The Daemon reacts immediatelly (real time) on any file added to the file system and automatically converts those files, using set (configurable) number of asynchronous child processes. For synchronization between the child processes it uses the file system, chokidar and NeDB storage. In the NeDB database a stack of files to be processed later is stored, as well as the files which failed to convert for any reason. Error messages and additional info is stored.

## How does it work?

- The Converter Daemon watches for any added file in specified folder
- When file is added, if any threads are free to process it, the daemon tries to immediately process the file
    - File with same name (its "footprint") is created in `in_progress` folder, to mark which files are currently being processed
    - Child process with convert script is asynchronously spawned
- If all threads are busy, the added file is put into database for later pickup for processing
- Whenever any thread finishes processing any file, it deletes its "footprint" from `in_progress` folder
- Whenever any thread finishes processing any file, this free thread polls for another file to process - looks for it in the database
- When all files are processed and no files are in the database, all threads finish and the daemon just waits for any other files added to the file system

The main processing of the file is now done by using the TPX3 Data Converter node.js native add-on. The script for the converting itself can be changed.

The used NeDB JavaScript database manages all operations as "append first", making all write operations lightning-fast.

## Future plans

 - Allow plugging any script/job (in any format) to be performed on the files. External scripts preferred.
 - Improve error handling (especially errors from external convert scripts), prevent crashes