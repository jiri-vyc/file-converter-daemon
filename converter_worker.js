var tpx3data = require('./cpp/build/Release/tpx3data');
var sleep = require('sleep');
var path = require('path');
var mkdirp = require('mkdirp');
var fs = require('fs');
var config = require('./config.js');
var datapath = config.dataPath;
var rawdatapath = path.join(datapath, 'RAW/');
var rootdatapath = path.join(datapath,'ROOT/');

var filepath = process.argv[2];

var filedir = path.dirname(filepath);


// Check if the given folder exists, if not, create it
try {
    stat = fs.statSync(rootdatapath + filedir);
} catch (err) {
	console.log("Folder did not exist. Creating: " + rootdatapath + filedir);
    mkdirp.sync(rootdatapath + filedir);
}

console.error(tpx3data.convert(filepath, filepath));

