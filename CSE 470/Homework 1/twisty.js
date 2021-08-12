//
//CSE 470 HW 1 TWISTY!  
//
/*
Written by: HW470:YOUR NAME HERE
Date: Jan 2021

Description: 
This program ..... HW470: COMPLETE THIS. DESCRIBE WHAT YOU DID.
*/

var canvas;
var gl;

//store the vertices
//Each triplet represents one triangle
var vertices = [];

//store a color for each vertex
var colors = [
];

//HW470: control the rotation
//(Your variable here)

//HW470: control the redraw rate
var delay = 1;
var thetaLoc;
var theta = 0.0;
var direction;


// =============== function init ======================
 
// When the page is loaded into the browser, start webgl stuff
window.onload = function init()
{
	// notice that gl-canvas is specified in the html code
    canvas = document.getElementById( "gl-canvas" );
    
	// gl is a canvas object
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

	// Track progress of the program with print statement
    console.log("Opened canvas");
        
    //HW470:
    // Define  data for object 
	// See HW specs for number of vertices  required
	// Recommendation: each set of three points corresponds to a triangle.
	// Here is one triangle. You can use parametric equations, for example of a circle to generate (x,y) values
	
    vertices = [
        // stationary shape
        vec2( 0.0, 0.125 ),
        vec2( -0.125, -0.125 ),
        vec2( 0.125, -0.125 ),

        // moving shape
        vec2( 0.0, 0.125 ),
        vec2( -0.125, 0.375 ),
        vec2( 0.125, 0.375 ),

        vec2( 0.0, 0.125 ),
        vec2( 0.125, 0.375 ),
        vec2( 0.25, 0.125 ),

        vec2( 0.0, 0.125 ),
        vec2( 0.25, 0.125 ),
        vec2( 0.125, -0.125 ),

        vec2( -0.25, 0.125 ),
        vec2( -0.125, 0.375 ),
        vec2( 0.0, 0.125 ),

        vec2( -0.25, 0.125 ),
        vec2( -0.125, -0.125 ),
        vec2( 0.0, 0.125 ),

        vec2( -0.125, -0.125 ),
        vec2( 0.125, -0.125 ),
        vec2( 0.0, -0.375 ),

        vec2( -0.125, 0.375 ),
        vec2( 0.125, 0.375 ),
        vec2( 0.0, 0.625 ),

        vec2( -0.25, 0.125 ),
        vec2( -0.125, -0.125 ),
        vec2( -0.625, -0.5 ),

        vec2( 0.25, 0.125 ),
        vec2( 0.125, -0.125 ),
        vec2( 0.625, -0.5 ),
    ];
	 
	
	//HW470: Create colors for the core and outer parts
	// See HW specs for the number of colors needed
	for(var i=0; i < vertices.length; i+=3) {
		colors.push(vec3(0.5, 0.0, 0.0));
        colors.push(vec3(0.5, 0.0, 0.0));
        colors.push(vec3(0.5, 0.0, 0.0));

        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));

        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));

        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));

        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));

        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));
        colors.push(vec3(1.0, 0.0, 0.0));

        colors.push(vec3(0.8, 0.8, 0.8));
        colors.push(vec3(0.8, 0.8, 0.8));
        colors.push(vec3(0.8, 0.8, 0.8));

        colors.push(vec3(0.4, 0.4, 0.4));
        colors.push(vec3(0.4, 0.4, 0.4));
        colors.push(vec3(0.4, 0.4, 0.4));

        colors.push(vec3(0.0, 0.0, 0.0));
        colors.push(vec3(0.0, 0.0, 0.0));
        colors.push(vec3(0.0, 0.0, 0.0));

        colors.push(vec3(0.0, 0.0, 0.0));
        colors.push(vec3(0.0, 0.0, 0.0));
        colors.push(vec3(0.0, 0.0, 0.0));
	};
	 
	// HW470: Print the input vertices and colors to the console
	console.log("Input vertices and colors:");
	 
	 

    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );
	// Background color to white
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );

    //  Define shaders to use  
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    // Load the data into the GPU
	//
	// color buffer: create, bind, and load
    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );
	
	// Associate shader variable for  r,g,b color
	var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );
    
    // vertex buffer: create, bind, load
    var vbuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vbuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );

    // Associate shader variables for x,y vertices	
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );
	
	//HW470: associate shader explode variable ("Loc" variables defined here) 
    thetaLoc = gl.getUniformLocation(program, "theta");

    console.log("Data loaded to GPU -- Now call render");

    render();
};


// =============== function render ======================

function render()
{
    // clear the screen 
    gl.clear( gl.COLOR_BUFFER_BIT );
	
    //HW470: send uniform(s) to vertex shader


    if (theta > 2 * Math.PI) {
        direction = false;
    }
    else if (theta < 0) {
        direction = true;
    }

    theta += (direction ? 0.01 : -0.01);
    gl.uniform1f(thetaLoc, theta);


	
	//HW470: draw the object
	// You will need to change this to create the twisting outer parts effect
	// Hint: you will need more than one draw function call
    gl.drawArrays( gl.TRIANGLES, 3, vertices.length-3 );
	
	gl.uniform1f(thetaLoc, 0.0);
    gl.drawArrays( gl.TRIANGLES, 0, 3); 
	
	//re-render after delay
	setTimeout(function (){requestAnimFrame(render);}, delay);
}

