//
//CSE 470 HW 2: pickAcube 
//
/*
Written by: HW470:Kumal Patel
Date: Feb 28, 2021
*/

var canvas;
var gl;

var numVertices = 36;
var theta  = 0.0;
var spintheta = 0.0;

var mvMatrix;
var mvMatrix2;
var modelView;
var sliderValue;

var pos = [
    translate(0, 0.75, 0.5),
    translate(0, -0.75, 0.5),
    translate(-0.75, 0, 0.5),
    translate(0.75, 0, 0.5),
    translate(-0.50, 0.50, 0.5),
    translate(0.50, 0.50, 0.5),
    translate(-0.50, -0.50, 0.5),
    translate(0.50, -0.50, 0.5)
];

var vx = [0, 0, -1, 1, -1, 1, -1, 1];
var vy = [1, -1, 0, 0, 1, 1, -1, -1,];


var scale, translation, rotation;
var isClicked = false;
var isRotating = false;
var posX, posY;
var lastIndex;

window.onload = function init() {
    canvas = document.getElementById( "gl-canvas" );    
    sliderValue = document.getElementById("scale-cube").value;
    spintheta = document.getElementById("rotation-speed").value;

    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

    gl.viewport( 0, 0, canvas.width, canvas.height );
    
    //gl.clearColor( 1.0, 1.0, 1.0, 1.0 );
    
    gl.enable(gl.DEPTH_TEST);

    //
    //  Load shaders and initialize attribute buffers
    //
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );
    
    createCube();

    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(cubeColor), gl.STATIC_DRAW );
    
    var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 4, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor);

    var vBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(cubeVertices), gl.STATIC_DRAW );
    
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );
 
    modelView = gl.getUniformLocation( program, "modelView" );

    // event listeners 
    document.getElementById("scale-cube").oninput = function() {
        sliderValue = this.value;
    };

    document.getElementById("rotation-speed").oninput = function() {
        spintheta = this.value;
    };

    document.getElementById('reset-button').onclick = function() {
        isClicked = true;
        isRotating = false;
        posX = -10; 
        posY = -10;
    }
    
    canvas.addEventListener('click', function() {
        var screenx = event.clientX - canvas.offsetLeft;
        var screeny = event.clientY - canvas.offsetTop;
        posX = 2*screenx/canvas.width-1;
        posY = 2*(canvas.height-screeny)/canvas.height-1;
    });
    render(); 
}

const render = () =>  {
    gl.clear( gl.COLOR_BUFFER_BIT | gl.DEPTH_BUFFER_BIT);

    // center cube
    scale = scalem(sliderValue, sliderValue, sliderValue);
    translation = translate(-0.5, -0.5, 0.5);
    
    if (isClicked) { // reset button is clicked
        rotation = rotate(0.0, vx[0], vy[0], 0.0);
    }
    else {
        rotation = rotate(theta * spintheta, vx[0], vy[0], 0.0 );
    }
    
    rotateCenterCube(scale, translation, rotation, mvMatrix);
    rotateCubes(mvMatrix2);

    theta += 0.2;
    requestAnimationFrame(render);
};

const findCube = () => {
    for(var index in pos) {
        upperX = pos[index][0][3] + sliderValue/2;
        lowerX = pos[index][0][3] - sliderValue/2;
        upperY = pos[index][1][3] + sliderValue/2;
        lowerY = pos[index][1][3] - sliderValue/2;

        if(posX < upperX && posX > lowerX && posY < upperY && posY > lowerY) {
            lastIndex = index;
            isRotating = true;
            return index;
        }
    }
        return -1;
};

const rotateCenterCube = (scale, translate, rotation, matrix) => {
    matrix = mult(scale, translate);
    var index = findCube();
    if (index != -1 && isRotating) {
        rotation = rotate(theta * spintheta, vx[index], vy[index], 0.0);
    }
    else if(index == -1 && isRotating) {
        rotation = rotate(theta * spintheta, vx[lastIndex], vy[lastIndex], 0.0);

    }
    else {
        rotation = rotate(0.0 * spintheta, vx[0], vy[0], 0.0);
    }
    matrix = mult(rotation, matrix);
    gl.uniformMatrix4fv(modelView, false, flatten(matrix) );
    gl.drawArrays(gl.TRIANGLES, 0, numVertices);
};

const  rotateCubes = (matrix) => {
    for (var index in pos) {
        var scale = scalem(sliderValue, sliderValue, sliderValue);
        var translation = translate(-0.5, -0.5, 0.5);
        var rotation = rotate(theta * spintheta, vx[index], vy[index], 0.0);
        matrix = mult(scale, translation);
        matrix = mult(rotation, matrix);
        matrix = mult(pos[index], matrix);
        gl.uniformMatrix4fv(modelView, false, flatten(matrix) );
        gl.drawArrays(gl.TRIANGLES, 0, numVertices);
    }   
};