// Licensed Materials - Property of IBM
//
// SAMPLE
//
// (c) Copyright IBM Corp. 2017 All Rights Reserved
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp

var binary = require('node-pre-gyp');
var path = require('path');
var binding_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));
var binding = require(binding_path);

process.on('message', function(m) {
  var retdata = {};

  switch (m.function) {
    case "PUT":
      var rc = binding.putContainer(m.data.channel, m.data.name, m.data.string);
      retdata = {"rc": rc};
      break;
    case "LINK":
      var rc = binding.programLink(m.data.applid, m.data.program, m.data.channel);
      retdata = {"rc": rc};
      break;
    case "GET":
      var rstring = binding.getContainer(m.data.channel, m.data.name);
      retdata = {"data": {"rstring": rstring}};
      break;
    default:
      retdata = {"err": "Unknown function"};
  }

  process.send(retdata);
});
