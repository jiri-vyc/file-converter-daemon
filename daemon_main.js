var chokidar = require('chokidar');
var exec = require('child_process').exec;
var fs = require('fs');
var path = require('path');
var mkdirp = require('mkdirp');
var config = require('./config.js');

var maxProcesses = config.maxProcesses;
var activeProcesses = 0;
var files = []; 
var datapath = config.dataPath;
var rawdatapath = path.join(datapath + 'RAW');

var log = config.logMethod;

var Datastore = require('nedb')
  , db = new Datastore({ filename: config.databaseFile });

db.loadDatabase(function (err) {
  if (!err){
  	log("Database successfully loaded.");
  } else {
  	log(err);
  }
});


log('Converter daemon/watcher started...');

// ============= WATCHER SETUP ======================
// Watch the ./data directory
var watcher_new = chokidar.watch( path.join(rawdatapath, config.subPath), 
	{
		// ignores .dotfiles and files starting with wu- (Web Upload)
		ignored: /([\/\\]\.|[\/\\]wu-)/,
		// waits 6 seconds after new file stabilizes (doesn't change in size) in the file system
		awaitWriteFinish: {
		    stabilityThreshold: config.stabilityThreshold
		  },
		// ignores files already in the filesystem when starting
		ignoreInitial: true,
		// current working directory
		cwd: rawdatapath
	});
log('Watching folder "' + path.join(rawdatapath, config.subPath) + '" for new files...');
// ==================================================



// =========== The main watching process ============
watcher_new.on('add', function(path){
	log('Added file ' + path);
	tryToProcessFile(path);
});
// ==================================================



// ========== Watching of in_progress folder ========
var watcher_progress = chokidar.watch('in_progress',
	{
		// ignores .dotfiles and files starting with wu- (Web Upload)
		ignored: /([\/\\]\.|[\/\\]wu-)/,
		cwd: '.'
	});
// if the file gets deleted (is no longer in progress - converting is done)
// ask for another file to convert, if available
watcher_progress.on('unlink', function(path){
	log("File " + path + " no longer in progress.");
	pollForNewFile();
});
// ==================================================

var polledFile = "";

function pollForNewFile(){
	// Find next one file stored for later processing in the database
	db.findOne({ "failed": false }, function (err, doc) {
		if (err){
			log(err);
		} else if (doc != null){
			// If the file found was already found by another thread, recursively repeat (find another)
			// Using JavaScript's basic single-thread nature, no 2 threads can access a variable at the same time by default
			if (doc._id == polledFile){
				return pollForNewFile();
			}
			// Mark current file as selected
			polledFile = doc._id;
			// Remove the selected files from db, preventing further finding/repeated converting
			db.remove({ _id: doc._id }, {}, function (err, numRemoved) {
				if (err){
					log(err);
				}
				// Try to convert the file
				tryToProcessFile(doc.filename);
			});
		// No file was found in the database, return and wait for new files
		} else {
			log("No other file to process. Waiting for new files.");
			return;
		}
	});
}


function tryToProcessFile(path){
	// All processes are busy at the moment, store file for later processing
	if (activeProcesses >= maxProcesses){
		log("All processes busy, storing file for later converting.");
		db.insert({"filename" : path, "failed": false, "additionalInfo": "Stored for later processing."}, function (err, newDoc) {   
			if (err){
				log(err);
			}
		});
	// At least one process free, process file immediately
	} else {
		activeProcesses++;
		convertFile(path);
	}
}

// The main converting function, puts the file in the "in_progress" and spawns the converting child process
function convertFile(filepath){
	log('Starting process converting file ' + filepath);
	var filedir = path.dirname(filepath);

	// Create a folder to store the "in progress" file
	try {
    	stat = fs.statSync(path.join('in_progress/', filedir));
	} catch (err) {
		log("Creating folder " + path.join('in_progress/', filedir));
	    mkdirp.sync(path.join('in_progress/', filedir));
	}

	exec('touch in_progress/' + filepath, function(err, stdout, stderr){
		log(stdout);
		log(stderr);
	});

	// Start converting
	// Asynchronously spawn a child process with the supplied script
	exec('node converter_worker.js ' + filepath, function(err, stdout, stderr){
		// Print out the stdout output of the convert script
		log(stdout);
		// If error happened or converter returned "not ok", log errors and save file as "failed" to database
		if (err || stderr.startsWith("not ok")) {
			log("ERROR: " + err);
			log("RET VALUE: " + stderr);
			db.insert({"filename": filepath, "failed": true, "error": err, "additionalInfo": stdout}, function(err, newDoc){
				if (err){
					log(err);
				}
			})
		}
		// Converting done, delete the file from "in_progress"
		exec('unlink in_progress/' + filepath, function(err, stdout, stderr){
			log(stdout);
			log(stderr);
		});
		activeProcesses--;
	});
}