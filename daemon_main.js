var chokidar = require('chokidar');
var exec = require('child_process').exec;
var fs = require('fs');
var path = require('path');
var mkdirp = require('mkdirp');

var maxProcesses = 4;
var activeProcesses = 0;
var files = []; 
var datapath = '/data/tpx3-visualization-data/';
var rawdatapath = datapath + 'RAW/';


var Datastore = require('nedb')
  , db = new Datastore({ filename: 'db/database' });

db.loadDatabase(function (err) {
  if (!err){
  	console.log("Database successfully loaded.");
  } else {
  	console.log(err);
  }
});



console.log('Converter daemon/watcher started...');
// Watch the ./data directory
var watcher_new = chokidar.watch(rawdatapath + '/ATLAS/TPX3_9/', 
	{
		// ignores .dotfiles and files starting with wu- (Web Upload)
		ignored: /([\/\\]\.|[\/\\]wu-)/,
		awaitWriteFinish: {
		    stabilityThreshold: 6000
		  },
		ignoreInitial: true,
		cwd: rawdatapath
	});
console.log('Watching folder "' + rawdatapath + '/ATLAS/TPX3_9/" for new files...');

watcher_new.on('add', function(path){
	console.log('Added file ' + path);
	tryToProcessFile(path);
});

var watcher_progress = chokidar.watch('in_progress',
	{
		// ignores .dotfiles and files starting with wu- (Web Upload)
		ignored: /([\/\\]\.|[\/\\]wu-)/,
		cwd: 'in_progress'
	});

watcher_progress.on('unlink', function(path){
	console.log("File " + path + " no longer in progress.");
});


function tryToProcessFile(path){
	// All processes are busy at the moment, store file for later processing
	if (activeProcesses >= maxProcesses){
		console.log("All processes busy, storing file for later converting.");
		db.insert({"filename" : path}, function (err, newDoc) {   
			if (err){
				console.log(err);
			}
		});
	// At least one process free, process file immediately
	} else {
		activeProcesses++;
		convertFile(path);
	}
}

function convertFile(filepath){
	console.log('Starting process converting file ' + filepath);
	var filedir = path.dirname(filepath);

	// Create a folder to store the "in progress" file
	try {
    	stat = fs.statSync('in_progress/' + filedir);
	} catch (err) {
		console.log("Creating folder " + 'in_progress/' + filedir);
	    mkdirp.sync('in_progress/' + filedir);
	}

	exec('touch in_progress/' + filepath, function(err, stdout, stderr){
		console.log(stdout);
		console.log(stderr);
	});

	exec('node converter_worker.js ' + filepath, function(err, stdout, stderr){
		if (err) {
			console.error(err);
			return;
		}
		console.log(stdout);
		exec('unlink in_progress/' + filepath, function(err, stdout, stderr){
			console.log(stderr);
			console.log(stdout);
			console.log(stderr);
		});
		activeProcesses--;
	});
}