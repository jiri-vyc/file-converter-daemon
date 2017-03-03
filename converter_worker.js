var tpx3data = require('./cpp/build/Release/tpx3data');
var sleep = require('sleep');
var path = require('path');
var mkdirp = require('mkdirp');
var fs = require('fs');
var datapath = '/data/tpx3-visualization-data/';
var rawdatapath = datapath + 'RAW/';
var rootdatapath = datapath + 'ROOT/';

var filepath = process.argv[2];

var filedir = path.dirname(filepath);

try {
    stat = fs.statSync(rootdatapath + filedir);
} catch (err) {
	console.log("Creating folder " + rootdatapath + filedir);
    mkdirp.sync(rootdatapath + filedir);
}

tpx3data.convert(filepath, filepath);

console.log('Done converting file: ' + filepath);

