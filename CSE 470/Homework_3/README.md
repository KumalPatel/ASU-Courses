# Surface of Revolution

## How it Works
First built by creating parametrized surfaces
```
       [ G(t) ]
F(t) = [   t  ]   t ∈ [-1,1] ; where G(t) is the generator function that is rotated along the y-axis
       [   0  ]
```
By applying the couter-clockwise roatation martix to F(t) with an angle θ it will give us the surface definition
```
          [ cos(θ) 0 -sin(θ) ]     [ G(t) ]
S(t,θ) =  [    0   1    0    ]  *  [  t   ]  ; t ∈ [-1,1] θ ∈ [0, 2π)
          [ sin(θ) 0  cos(θ) ]     [  0   ]
          
         [ G(t)cos(θ) ]
S(t,θ) = [     t      ]
         [ G(t)sin(θ) ]
```
The next thing to do is to calculate the normal vectors which is going to be used for shading on the surfaces. To calculate these vectors you take the partial 
deriviates S(t,θ) with respect to t and θ.
```
              [ G'(t)cos(θ) ]
T' = dS/dt =  [     1       ]
              [ G'(t)sin(θ) ]

              [ -G(t)sin(θ) ]
θ' = dS/dθ =  [      0      ]
              [  G(t)cos(θ) ]

              [ G(t)cos(θ)  ]          [ cos(θ) ]
n = T' * θ' = [ -G(t)*G'(t) ] = G(t) * [ -G'(t) ]    Since we do not need the length of the vector we can remove the G(t) 
              [ G(t)sin(θ)  ]          [ sin(θ) ]
              
    [ cos(θ) ] 
n = [ -G'(t) ]
    [ sin(θ) ]
```


## Demo
![test](https://i.gyazo.com/ec7c1e394cc967d4731392dff82f067f.gif)
