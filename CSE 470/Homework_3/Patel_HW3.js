// Name: Kumal Patel

var canvas;
var gl;
var program;
var lightProgram;

var dz = 0;
var boolShape = 0; // 0 cylinder, 1 vase

var currentShape;
var currentMaterial;
var currentTSlice;
var currentThetaSlice;

var modelViewMatrix,
  projectionMatrix,
  modelViewLightMatrix,
  projectionLightMatrix;
var modelViewMatrixLoc,
  projectionMatrixLoc,
  modelViewLightMatrixLoc,
  projectionLightMatrixLoc;

var rotateLight = false;
var lightAngle = 0;
var rotate_speed;
var fieldView;

var va = vec3(0.0, 0.0, -1.0);
var vb = vec3(0.0, 0.942809, 0.333333);
var vc = vec3(-0.816497, -0.471405, 0.333333);
var vd = vec3(0.816497, -0.471405, 0.333333);

var resolution = {
  low: {
    tSlice: 10,
    thetaSlice: 80,
  },
  high: {
    tSlice: 40,
    thetaSlice: 80,
  },
};
var viewer = {
  eye: vec3(0.0, 0.0, 3.0),
  at: vec3(0.0, 0.0, 0.0),
  up: vec3(0.0, 1.0, 0.0),

  radius: 3.0,
  theta: 0,
  phi: 0,
};

var perspProj = {
  fov: 60,
  aspect: 1,
  near: 0.1,
  far: 10,
};

var materials = {
  emerald: {
    ambient: vec4(0.0215, 0.1745, 0.0215, 1.0),
    diffuse: vec4(0.07568, 0.61424, 0.07568, 1.0),
    specular: vec4(0.633, 0.727811, 0.633, 1.0),
    shininess: 0.6,
    emissive: vec4(0.0, 0.0, 0.0, 1.0),
  },
  red_plastic: {
    ambient: vec4(0.0, 0.0, 0.0, 1.0),
    diffuse: vec4(0.5, 0.0, 0.0, 1.0),
    specular: vec4(0.7, 0.6, 0.6, 1.0),
    shininess: 0.25,
    emissive: vec4(0.0, 0.0, 0.0, 1.0),
  },
  yellow_rubber: {
    ambient: vec4(0.05, 0.05, 0.0, 1.0),
    diffuse: vec4(0.5, 0.5, 0.4, 1.0),
    specular: vec4(0.7, 0.7, 0.04, 1.0),
    shininess: 0.078125,
    emissive: vec4(0.0, 0.0, 0.0, 1.0),
  },
};

var light = {
  // position: vec4(5.0, 0.0, -1.0, 1.0),
  // ambient: vec4(0.8, 0.8, 0.8, 1.0),
  // diffuse: vec4(1.0, 1.0, 1.0, 1.0),
  // specular: vec4(1.0, 1.0, 1.0, 1.0),
  position: vec4(1.0, 1.0, 1.0, 1.0),
  ambient: vec4(0.0, 0.0, 0.0, 1.0),
  diffuse: vec4(1.0, 1.0, 1.0, 1.0),
  specular: vec4(1.0, 1.0, 1.0, 1.0),
  emissive: vec4(1.0, 1.0, 1.0, 1.0),
};

var lightBuffer, lightPosition, normalLight, vNormalLight;
var nBuffer, vNormal, iBuffer, vPosition, vBuffer;

var mouse = {
  prevX: 0,
  prevY: 0,

  leftDown: false,
  rightDown: false,
};

const drawShape = (shape) => {
  gl.useProgram(program);

  // index buffer
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);
  gl.bufferData(
    gl.ELEMENT_ARRAY_BUFFER,
    new Uint16Array(flatten(shape.indices)),
    gl.STATIC_DRAW
  );

  // normal buffer
  gl.bindBuffer(gl.ARRAY_BUFFER, nBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, flatten(shape.normalList), gl.STATIC_DRAW);

  vNormal = gl.getAttribLocation(program, "vNormal");
  gl.vertexAttribPointer(vNormal, 4, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(vNormal);

  // vertex buffer
  gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, flatten(shape.verticesList), gl.STATIC_DRAW);

  vPosition = gl.getAttribLocation(program, "vPosition");
  gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(vPosition);
};

const setMaterial = (mat) => {
  currentMaterial.ambientProduct = mult(currentMaterial.ambient, light.ambient);
  currentMaterial.diffuseProduct = mult(currentMaterial.diffuse, light.diffuse);
  currentMaterial.specularProduct = mult(
    currentMaterial.specular,
    light.specular
  );
  currentMaterial.emissiveProduct = mult(
    currentMaterial.emissive,
    light.emissive
  );
};

const updatePoints = () => {
  gl.bindBuffer(gl.ARRAY_BUFFER, vBuffer);
  gl.vertexAttribPointer(vPosition, 4, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(vPosition);
  gl.bindBuffer(gl.ELEMENT_ARRAY_BUFFER, iBuffer);
};

const drawLightSource = () => {
  gl.useProgram(lightProgram);

  // light buffer
  gl.bindBuffer(gl.ARRAY_BUFFER, lightBuffer);
  gl.bufferData(gl.ARRAY_BUFFER, flatten(pointsArray), gl.STATIC_DRAW);

  lightPosition = gl.getAttribLocation(lightProgram, "vPosition");
  gl.vertexAttribPointer(lightPosition, 3, gl.FLOAT, false, 0, 0);
  gl.enableVertexAttribArray(lightPosition); // may not need

  gl.bindBuffer(gl.ARRAY_BUFFER, normalLight);
  gl.bufferData(gl.ARRAY_BUFFER, flatten(normalsArray), gl.STATIC_DRAW);
};

window.onload = function init() {
  canvas = document.getElementById("gl-canvas");
  rotate_speed = +document.getElementById("rotating_speed").value;
  fieldView = +document.getElementById("field_of_view").value;
  perspProj.aspect = canvas.width / canvas.height;

  gl = WebGLUtils.setupWebGL(canvas);
  if (!gl) {
    alert("WebGL isn't available");
  }

  gl.viewport(0, 0, canvas.width, canvas.height);
  gl.enable(gl.DEPTH_TEST);

  program = initShaders(gl, "vertex-shader", "fragment-shader");
  lightProgram = initShaders(gl, "light-Vshader", "fragment-shader");

  currentTSlice = resolution.high.tSlice;
  currentThetaSlice = resolution.high.thetaSlice;
  currentMaterial = materials.emerald;
  currentShape = surfaces(shapes.cylinder, currentTSlice, currentThetaSlice);

  dz = currentShape.maxDz;

  // buffers
  iBuffer = gl.createBuffer();
  nBuffer = gl.createBuffer();
  vBuffer = gl.createBuffer();
  lightBuffer = gl.createBuffer();
  normalLight = gl.createBuffer();

  drawShape(currentShape);
  setMaterial(currentMaterial);

  // light sphere
  tetrahedron(va, vb, vc, vd, 6);

  viewer.eye = vec3(0.0, 0.0, 3 * dz);
  viewer.radius = 3 * dz;

  modelViewMatrix = lookAt(vec3(viewer.eye), viewer.at, viewer.up);
  projectionMatrix = perspective(
    perspProj.fov,
    perspProj.aspect,
    perspProj.near,
    perspProj.far
  );

  projectionMatrixLoc = gl.getUniformLocation(program, "projectionMatrix");
  modelViewMatrixLoc = gl.getUniformLocation(program, "modelViewMatrix");

  projectionLightMatrixLoc = gl.getUniformLocation(
    lightProgram,
    "projectionMatrix"
  );
  modelViewLightMatrixLoc = gl.getUniformLocation(
    lightProgram,
    "modelViewMatrix"
  );

  eventHandlers();
  render();
};

var render = function () {
  gl.clear(gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

  gl.useProgram(program);

  gl.uniformMatrix4fv(modelViewMatrixLoc, false, flatten(modelViewMatrix));
  gl.uniformMatrix4fv(projectionMatrixLoc, false, flatten(projectionMatrix));

  gl.uniform4fv(
    gl.getUniformLocation(program, "lightPosition"),
    flatten(light.position)
  );
  gl.uniform4fv(
    gl.getUniformLocation(program, "ambientProduct"),
    flatten(currentMaterial.ambientProduct)
  );
  gl.uniform4fv(
    gl.getUniformLocation(program, "diffuseProduct"),
    flatten(currentMaterial.diffuseProduct)
  );
  gl.uniform4fv(
    gl.getUniformLocation(program, "specularProduct"),
    flatten(currentMaterial.specularProduct)
  );
  gl.uniform4fv(
    gl.getUniformLocation(program, "emissiveProduct"),
    flatten(currentMaterial.emissiveProduct)
  );
  gl.uniform1f(
    gl.getUniformLocation(program, "shininess"),
    200 * currentMaterial.shininess
  );

  updatePoints();
  gl.drawElements(gl.TRIANGLES, currentShape.triNum * 3, gl.UNSIGNED_SHORT, 0);

  // light sphere
  gl.useProgram(lightProgram);

  if (rotateLight) {
    light.position = multMartixByVector(rotateY(lightAngle), vec4(0, 0, 2, 1));
    lightAngle += rotate_speed;
  }

  var mvMatrix = mult(
    translate(
      light.position[0],
      light.position[1],
      light.position[2],
      light.position[3]
    ),
    scalem(0.3, 0.3, 0.3)
  );
  mvMatrix = mult(modelViewMatrix, mvMatrix);

  gl.uniformMatrix4fv(modelViewLightMatrixLoc, false, flatten(mvMatrix));
  gl.uniformMatrix4fv(
    projectionLightMatrixLoc,
    false,
    flatten(projectionMatrix)
  );

  drawLightSource();
  for (var i = 0; i < index; i += 3) gl.drawArrays(gl.TRIANGLES, i, 3);

  requestAnimationFrame(render);
};

var eventHandlers = function () {
  document.getElementById("gl-canvas").onmousedown = function (event) {
    if (event.button == 0 && !mouse.leftDown) {
      mouse.leftDown = true;
      mouse.prevX = event.clientX;
      mouse.prevY = event.clientY;
    } else if (event.button == 2 && !mouse.rightDown) {
      mouse.rightDown = true;
      mouse.prevX = event.clientX;
      mouse.prevY = event.clientY;
    }
  };

  document.getElementById("gl-canvas").onmouseup = function (event) {
    // Mouse is now up
    if (event.button == 0) {
      mouse.leftDown = false;
    } else if (event.button == 2) {
      mouse.rightDown = false;
    }
  };

  document.getElementById("gl-canvas").onmouseleave = function () {
    // Mouse is now up
    mouse.leftDown = false;
    mouse.rightDown = false;
  };

  document.getElementById("gl-canvas").onmousemove = function (event) {
    if (mouse.leftDown || mouse.rightDown) {
      var currentX = event.clientX;
      var currentY = event.clientY;

      var deltaX = event.clientX - mouse.prevX;
      var deltaY = event.clientY - mouse.prevY;

      if (mouse.leftDown) {
        if (viewer.up[1] > 0) {
          viewer.theta -= 0.01 * deltaX;
          viewer.phi -= 0.01 * deltaY;
        } else {
          viewer.theta += 0.01 * deltaX;
          viewer.phi -= 0.01 * deltaY;
        }

        var twoPi = 6.28318530718;
        if (viewer.theta > twoPi) {
          viewer.theta -= twoPi;
        } else if (viewer.theta < 0) {
          viewer.theta += twoPi;
        }

        if (viewer.phi > twoPi) {
          viewer.phi -= twoPi;
        } else if (viewer.phi < 0) {
          viewer.phi += twoPi;
        }
      } else if (mouse.rightDown) {
        viewer.radius -= 0.01 * deltaX;
        viewer.radius = Math.max(0.1, viewer.radius);
      }

      var threePiOver2 = 4.71238898;
      var piOver2 = 1.57079632679;
      var pi = 3.14159265359;

      var r = viewer.radius * Math.sin(viewer.phi + piOver2);
      viewer.eye = vec3(
        r * Math.cos(viewer.theta + piOver2),
        viewer.radius * Math.cos(viewer.phi + piOver2),
        r * Math.sin(viewer.theta + piOver2)
      );

      for (k = 0; k < 3; k++) viewer.eye[k] = viewer.eye[k] + viewer.at[k];

      if (viewer.phi < piOver2 || viewer.phi > threePiOver2) {
        viewer.up = vec3(0.0, 1.0, 0.0);
      } else {
        viewer.up = vec3(0.0, -1.0, 0.0);
      }

      modelViewMatrix = lookAt(vec3(viewer.eye), viewer.at, viewer.up);

      mouse.prevX = currentX;
      mouse.prevY = currentY;
    }
  };

  document.getElementById("cylinder").onclick = function (event) {
    currentShape = surfaces(shapes.cylinder, currentTSlice, currentThetaSlice);
    drawShape(currentShape);
    boolShape = 0;
  };

  document.getElementById("vase").onclick = function (event) {
    currentShape = surfaces(shapes.vase, currentTSlice, currentThetaSlice);
    drawShape(currentShape);
    boolShape = 1;
  };

  document.getElementById("emerald").onclick = function (event) {
    currentMaterial = materials.emerald;
    setMaterial(currentMaterial);
  };

  document.getElementById("red_plastic").onclick = function (event) {
    currentMaterial = materials.red_plastic;
    setMaterial(currentMaterial);
  };

  document.getElementById("yellow_rubber").onclick = function (event) {
    currentMaterial = materials.yellow_rubber;
    setMaterial(currentMaterial);
  };

  document.getElementById("low").onclick = function (event) {
    var shape = boolShape ? shapes.vase : shapes.cylinder;
    currentTSlice = resolution.low.tSlice;
    currentThetaSlice = resolution.low.thetaSlice;
    currentShape = surfaces(shape, currentTSlice, currentThetaSlice);
    drawShape(currentShape);
  };

  document.getElementById("high").onclick = function (event) {
    var shape = boolShape ? shapes.vase : shapes.cylinder;
    currentTSlice = resolution.high.tSlice;
    currentThetaSlice = resolution.high.thetaSlice;
    currentShape = surfaces(shape, currentTSlice, currentThetaSlice);
    drawShape(currentShape);
  };

  document.getElementById("static").onclick = function (event) {
    rotateLight = false;
  };

  document.getElementById("rotating").onclick = function (event) {
    rotateLight = true;
    light.position = vec4(1.0, 1.0, 1.0, 1.0);
    lightAngle = 0;
  };

  document.getElementById("rotating_speed").oninput = function (event) {
    rotate_speed = +this.value;
  };

  document.getElementById("field_of_view").oninput = function (event) {
    perspProj.fov = +this.value;
    projectionMatrix = perspective(
      perspProj.fov,
      perspProj.aspect,
      perspProj.near,
      perspProj.far
    );
  };
};
