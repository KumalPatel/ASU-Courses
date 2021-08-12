// Name: Kumal Patel

var normalsArray = [];
var pointsArray = [];
var index = 0;

const multMartixByVector = (matrix, vector) => {
  var newVector = [];
  for (var i = 0; i < matrix.length; i++) {
    var newVectorValue = 0;
    for (var j = 0; j < vector.length; j++) {
      newVectorValue += matrix[i][j] * vector[j];
    }
    newVector.push(newVectorValue);
  }
  return newVector;
};

const shapes = {
  cylinder: {
    function: function (t) {
      return 1;
    },
    derivative: function (t) {
      return 0;
    },
  },
  vase: {
    function: function (t) {
      return 0.25 * Math.sin(-1 * t * Math.PI) + 0.5;
    },
    derivative: function (t) {
      return (-Math.PI / 4) * Math.cos(Math.PI * t);
    },
  },
};

const surfaces = (curveFunction, tSlice, thetaSlice) => {
  var verticesList = [];
  var normalList = [];
  var indices = [];
  var triNum = 0;
  var maxDz = 0;

  for (var t = -1; t <= 1.1; t += 2 / tSlice) {
    var curve = curveFunction.function(t);
    maxDz = Math.max(maxDz, curve);
    const initVect = vec4(curve, t, 0, 1);

    for (var theta = 0; theta < 360; theta += 360 / thetaSlice) {
      var rotation = rotateY(theta);
      var vertices = multMartixByVector(rotation, initVect);
      var slope = curveFunction.derivative(t);
      const normal = normalize(
        vec4(Math.cos(radians(theta)), -slope, Math.sin(radians(theta)), 0)
      );
      verticesList.push(vertices);
      normalList.push(normal);
    }
  }
  console.log(verticesList);

  const sub = [0, 1, 2, 2, 1, 3];

  for (var i = 0; i < tSlice; i++) {
    for (var j = 0; j < thetaSlice; j++) {
      var quad = [
        thetaSlice * i + j,
        thetaSlice * i + ((j + 1) % thetaSlice),
        thetaSlice * (i + 1) + j,
        thetaSlice * (i + 1) + ((j + 1) % thetaSlice),
      ];
      for (var k = 0; k < sub.length; k++) {
        indices.push(quad[sub[k]]);
      }
      triNum += 2;
    }
  }

  return {
    verticesList,
    normalList,
    indices,
    triNum,
    maxDz,
  };
};

const triangle = (a, b, c) => {
  normalsArray.push(a);
  normalsArray.push(b);
  normalsArray.push(c);
  // play: create an incorrect normal vector to see what happens
  //normalsArray.push(c + Math.random());

  pointsArray.push(a);
  pointsArray.push(b);
  pointsArray.push(c);

  index += 3;
};

const divideTriangle = (a, b, c, count) => {
  if (count > 0) {
    var ab = mix(a, b, 0.5);
    var ac = mix(a, c, 0.5);
    var bc = mix(b, c, 0.5);

    // normalize 3d vector
    ab = normalize(ab, false);
    ac = normalize(ac, false);
    bc = normalize(bc, false);

    divideTriangle(a, ab, ac, count - 1);
    divideTriangle(ab, b, bc, count - 1);
    divideTriangle(bc, c, ac, count - 1);
    divideTriangle(ab, bc, ac, count - 1);
  } else {
    triangle(a, b, c);
  }
};

const tetrahedron = (a, b, c, d, n) => {
  divideTriangle(a, b, c, n);
  divideTriangle(d, c, b, n);
  divideTriangle(a, d, b, n);
  // comment out next line to create an open object
  divideTriangle(a, c, d, n);
};
