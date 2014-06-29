#include <iostream>

/* Use the following line on a Windows machine:
 #include <GL/glut.h>
 */
/* This line is for Max OSX  */
#include <GLUT/glut.h>
#include <cmath>

int width=512;
int height=512;

/*! GLUT display callback function */
void display(void);
/*! GLUT window reshape callback function */
void reshape(int, int);

void God(float sunX, float sunY);

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    
    /* set the window size to 512 x 512 */
    glutInitWindowSize(width, height);
    
    /* set the display mode to Red, Green, Blue and Alpha
     allocate a depth buffer
     enable double buffering
     */
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    
    /* create the window (and call it Lab 1) */
    glutCreateWindow("Lab 1");
    
    /* set the glut display callback function
     this is the function GLUT will call every time
     the window needs to be drawn
     */
    glutDisplayFunc(display);
    
    /* set the glut reshape callback function
     this is the function GLUT will call whenever
     the window is resized, including when it is
     first created
     */
    glutReshapeFunc(reshape);
    
    /* set the default background color to black */
    glClearColor(0,0,0,1);
    
    /* enter the main event loop so that GLUT can process
     all of the window event messages
     */
    glutMainLoop();
    
    return 0;
}

/*! glut display callback function.  Every time the window needs to be drawn,
 glut will call this function.  This includes when the window size
 changes, or when another window covering part of this window is
 moved so this window is uncovered.
 */
int timer=200;
double sunX, sunY;
void display()
{
    /* clear the color buffer (resets everything to black) */
    glClear(GL_COLOR_BUFFER_BIT);
    
    /* set the current drawing color to red */
    glColor3f(1, 0, 0);
    
    /* start drawing triangles, each triangle takes 3 vertices */
    glBegin(GL_TRIANGLES);
    
    /* give the 3 triangle vertex coordinates 1 at a time */
    glVertex2f(-100+width/2, -100+width/2);
    glVertex2f(0+width/2, 100+width/2);
    glVertex2f(100+width/2, -100+width/2);
    
	
    glColor3f(0, 1, 0);
    glVertex2f(0, 200);
    glVertex2f(200, 200);
    glVertex2f(100, 300);
	
    /* tell OpenGL we're done drawing triangles */
    glEnd();
    
	sunX=256+256*cos(timer*M_PI/180);
	sunY=256+256*sin(timer*M_PI/180);
	God(sunX, sunY);
	timer=200;
    /* swap the back and front buffers so we can see what we just drew */
    glutSwapBuffers();
	//glutPostRedisplay();
}

/*! glut reshape callback function.  GLUT calls this function whenever
 the window is resized, including the first time it is created.
 You can use variables to keep track the current window size.
 */
void reshape(int width, int height)
{
    /* tell OpenGL we want to display in a recangle that is the 
     same size as the window
     */
    glViewport(0,0,width,height);
    
    /* switch to the projection matrix */
    glMatrixMode(GL_PROJECTION);
    
    /* clear the projection matrix */
    glLoadIdentity();
    
    /* set the camera view, orthographic projection in 2D */
    gluOrtho2D(0,width,0,height);
    
    /* switch back to the model view matrix */
    glMatrixMode(GL_MODELVIEW);
}

void God(float sunX, float sunY){
	int sampleCount=100;
	
	float *original=new float[width*height*3];
	glReadPixels(0, 0, width, height, GL_RGB, GL_FLOAT, original);
	
	float *newImage=new float[width*height*3];
	
	for(int j=0;j<height;j++){
		for(int i=0;i<width;i++){
			
			int pixel=j*width+i;
			
			newImage[3*pixel]=original[3*pixel];
			newImage[3*pixel+1]=original[3*pixel+1];
			newImage[3*pixel+2]=original[3*pixel+2];
			
			float x, y;
			x=i;
			y=j;
			
			float dx, dy;
			dx=x-sunX;
			dy=y-sunY;
			
			dx/=sampleCount;
			dy/=sampleCount;
			
			float oR, oG, oB;
			oR=newImage[3*pixel];
			oG=newImage[3*pixel+1];
			oB=newImage[3*pixel+2];
			
			float decay=1;
			for(int k=0;k<sampleCount-1;k++){
				x-=dx;
				y-=dy;
				
				//if(x<0 || width>=x || y<0 || height>=y)
				//	break;
				int tPix=int(y)*width+int(x);
				float tR, tG, tB;
				tR=newImage[3*tPix];
				tG=newImage[3*tPix+1];
				tB=newImage[3*tPix+2];
				
				double scale=decay/sampleCount;
				
				decay*=0.99;
				
				newImage[3*pixel]+=tR*scale;
				newImage[3*pixel+1]+=tG*scale;
				newImage[3*pixel+2]+=tB*scale;
			}
			
		}
	}
	glDrawPixels(width, height, GL_RGB, GL_FLOAT, newImage);
}
/*
float4 main(float2 texCoord : TEXCOORD0) : COLOR0  
{  
	// Calculate vector from pixel to light source in screen space.  
	half2 deltaTexCoord = (texCoord - ScreenLightPos.xy);  
	// Divide by number of samples and scale by control factor.  
	deltaTexCoord *= 1.0f / NUM_SAMPLES * Density;  
	// Store initial sample.  
	half3 color = tex2D(frameSampler, texCoord);  
	// Set up illumination decay factor.  
	half illuminationDecay = 1.0f;  
	// Evaluate summation from Equation 3 NUM_SAMPLES iterations.  
	for (int i = 0; i < NUM_SAMPLES; i++)  
	{  
		// Step sample location along ray.  
		texCoord -= deltaTexCoord;  
		// Retrieve sample at new location.  
		half3 sample = tex2D(frameSampler, texCoord);  
		// Apply sample attenuation scale/decay factors.  
		sample *= illuminationDecay * Weight;  
		// Accumulate combined color.  
		color += sample;  
		// Update exponential decay factor.  
		illuminationDecay *= Decay;  
	}  
	// Output final color with a further scale control factor.  
	return float4( color * Exposure, 1);  
}*/