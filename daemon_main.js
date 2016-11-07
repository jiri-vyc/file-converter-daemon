var chokidar = require('chokidar');
var exec = require('child_process').exec;
var fs = require('fs');

var maxProcesses = 8;
var activeProcesses = 0;
var files = []; 
var datapath = '/data/tpx3-visualization-data/';
var rawdatapath = datapath + 'RAW/';

console.log('Converter daemon/watcher started...');
// Watch the ./data directory
var watcher_new = chokidar.watch(rawdatapath, 
	{
		// ignores .dotfiles and files starting with [wu] (Web Upload)
		ignored: /([\/\\]\.|[\/\\]\[wu\])/,
		awaitWriteFinish: {
		    stabilityThreshold: 2000
		  },
		ignoreInitial: true,
		cwd: rawdatapath
	});
console.log('Watching folder "' + datapath + 'RAW/" for new files...');

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
	console.log("File " + path + " no longer in progress.");
})


function tryToProcessFile(path){
	// All processes are busy at the moment, store file for later processing
	if (activeProcesses >= maxProcesses){
		console.log("All processes busy, storing file for later converting.");
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