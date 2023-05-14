const testInheritCpp = require('./build/Release/function-template-inherit');

const pet1 = new testInheritCpp.Pet();

console.log(pet1); // { name: 'Unknown', type: 'animal' }
console.log(pet1.summary()); // Unknown is a/an animal.

const dog1 = new testInheritCpp.Dog();
console.log(dog1); // { name: 'Unknown', type: 'dog' }
console.log(dog1.summary()); // Unknown is a/an dog.

dog1.setName('dog');
console.log(dog1.summary()); //dog is a/an dog.

/**==========功能等价于以下js代码====== */

const testInheritJs = require('./function-template-inherit.js');

const pet2 = new testInheritJs.Pet();

console.log(pet2); // { name: 'Unknown', type: 'animal' }
console.log(pet2.summary()); // Unknown is a/an animal.

const dog2 = new testInheritJs.Dog();
console.log(dog2); // { name: 'Unknown', type: 'dog' }
console.log(dog2.summary()); // Unknown is a/an dog.

dog2.setName('dog');
console.log(dog2.summary()); //dog is a/an dog.
