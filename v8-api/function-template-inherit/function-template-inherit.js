const util = require('util');

function Pet() {
    this.name = 'Unknown';
    this.type = 'animal';
}

Pet.prototype.summary = function() {
    return `${this.name} is a/an ${this.type}`;
}

Pet.prototype.setName = function(name) {
    this.name = name;
}

function Dog() {
    Pet.call(this);
    this.type = 'dog';
}

util.inherits(Dog, Pet); // Dog继承Pet

module.exports = {
    Pet,
    Dog,
}
