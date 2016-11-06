var chokidar = require('chokidar');
var exec = require('child_process').exec;
var fs = require('fs');

var maxProcesses = 4;
var activeProcesses = 0;
var files = []; 

// Watch the ./data directory
var watcher_new = chokidar.watch('.', 
	{
		// ignores .dotfiles and files starting with [wu] (Web Upload)
		ignored: /([\/\\]\.|[\/\\]\[wu\])/,
		awaitWriteFinish: {
		    stabilityThreshold: 2000
		  },
		cwd: 'data'
	});

watcher_new.on('add', function(path){
	console.log('Added file ' + path);
	tryToProcessFile(path);
});

var watcher_progress = chokidar.watch('.',
	{
		// ignores .dotfiles and files starting with [wu] (Web Upload)
		ignored: /([\/\\]\.|[\/\\]\[wu\])/,
		cwd: 'in_progress'
	});

watcher_progress.on('unlink', function(path){
	console.log(path + " file unlinked.");
})


function tryToProcessFile(path){
	// All processes are busy at the moment, store file for later processing
	if (activeProcesses >= maxProcesses){
		exec('echo "' + path + '" >> to_process.txt');
	// At least one process free, process file immediately
	} else {
		activeProcesses++;
		convertFile(path);
	}
}

function convertFile(path){
	console.log('Starting process converting file ' + path);
	exec('touch in_progress/' + path);
	exec('node converter_worker.js ' + path, function(err, stdout, stderr){
		if (err) {
			console.error(err);
			return;
		}
		console.log(stdout);
		exec('unlink in_progress/' + path);
		activeProcesses--;
	});
}