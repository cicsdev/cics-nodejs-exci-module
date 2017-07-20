// Licensed Materials - Property of IBM
//
// SAMPLE
//
// (c) Copyright IBM Corp. 2017 All Rights Reserved
//
// US Government Users Restricted Rights - Use, duplication or
// disclosure restricted by GSA ADP Schedule Contract with IBM Corp

const cp = require('child_process');
const join = require('path').join;

function cicsEXCI() {
  return this;
}

cicsEXCI.prototype.create = function(next) {
  const n = cp.fork(join(__dirname, './cics-exci-process.js'), [], { stdio: ['ignore', 'ignore', 'ignore', 'ipc'] });
  this.cicsproc = n;
  n.on('message', function(m) {
    if (m.err) {
      this.next(m.err, null);
    } else {
      this.next(null, m.data);
    }
  });
  next();
}

cicsEXCI.prototype.link = function(linkdata, next) {
  var n = this.cicsproc;
  n.next = next;
  n.send({"function": "LINK", "data": linkdata});
}

cicsEXCI.prototype.putContainer = function(inputdata, next) {
  var n = this.cicsproc;
  n.next = next;
  n.send({"function": "PUT", "data": inputdata});
}

cicsEXCI.prototype.getContainer = function(outputdata, next) {
  var n = this.cicsproc;
  n.next = next;
  n.send({"function": "GET", "data": outputdata});
}

cicsEXCI.prototype.dispose = function() {
  this.cicsproc.kill();
}

module.exports = cicsEXCI;
