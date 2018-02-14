#include <cstdlib>
#include <cmath>

#include <Inventor/Sb.h>
#include <Inventor/Xt/SoXt.h>
#include <Inventor/Xt/SoXtRenderArea.h>
#include <Inventor/actions/SoBoxHighlightRenderAction.h>
#include <Inventor/events/SoKeyboardEvent.h>
#include <Inventor/nodes/SoDirectionalLight.h>
#include <Inventor/nodes/SoEventCallback.h>
#include <Inventor/nodes/SoMaterial.h>
#include <Inventor/nodes/SoNode.h>
#include <Inventor/nodes/SoPerspectiveCamera.h>
#include <Inventor/nodes/SoSphere.h>
#include <Inventor/nodes/SoSelection.h>
#include <Inventor/nodes/SoSeparator.h>
#include <Inventor/nodes/SoTransform.h>

// Function prototypes
void myKeyPressCB(void *, SoEventCallback *);
void RandomWalk();

//SoSeparator *MySoSimbox();
void AddSoParticles(SoSeparator *root);



// Global data
SbViewportRegion viewportRegion;

const int N = 4;
float dL=4.5, L=N*dL, Lhalf=L/2.0;


double x[N*N],y[N*N],angle[N*N];
SoTransform *position[N*N];


int
main(int , char **argv)
{
   // Print out usage message
   printf("Up arrow  - random diffusion\n");

   // Initialize Inventor and Xt
   Widget myWindow = SoXt::init(argv[0]);
   if (myWindow == NULL) exit(1);

   // Create and set up the selection node
   SoSelection *selectionRoot = new SoSelection;
   selectionRoot->ref();
   selectionRoot->policy = SoSelection::SHIFT;
   
   SoMaterial *myMaterial = new SoMaterial;
   myMaterial->diffuseColor.setValue(1.0, 0.0, 0.0);
   selectionRoot->addChild(myMaterial);
	
   // Add a camera and some light
   SoPerspectiveCamera *myCamera = new SoPerspectiveCamera;
   selectionRoot->addChild(myCamera);
   selectionRoot->addChild(new SoDirectionalLight);



   // An event callback node so we can receive key press events
   SoEventCallback *myEventCB = new SoEventCallback;
   myEventCB->addEventCallback(
            SoKeyboardEvent::getClassTypeId(), 
            myKeyPressCB, selectionRoot);
   selectionRoot->addChild(myEventCB);


	//particles (ellipsoid)
  AddSoParticles(selectionRoot); 
	
	
   // Create a render area for viewing the scene
   SoXtRenderArea *myRenderArea = new SoXtRenderArea(myWindow);
   myRenderArea->setSceneGraph(selectionRoot);
   myRenderArea->setGLRenderAction(new SoBoxHighlightRenderAction());
   myRenderArea->redrawOnSelectionChange(selectionRoot);
   myRenderArea->setTitle("Adding Event Callbacks");

   // Make the camera see the whole scene
   viewportRegion = myRenderArea->getViewportRegion();
   myCamera->viewAll(selectionRoot, viewportRegion, 2.0);


	
	
   // Show our application window, and loop forever...
   myRenderArea->show();
   SoXt::show(myWindow);
   SoXt::mainLoop();
}


// If the event is down arrow, then scale down every object 
// in the selection list; if the event is up arrow, scale up.
// The userData is the selectionRoot from main().
void
myKeyPressCB(void *userData, SoEventCallback *eventCB)
{
   SoSelection *selection = (SoSelection *) userData;
   const SoEvent *event = eventCB->getEvent();

   // check for the Up and Down arrow keys being pressed
   if (SO_KEY_PRESS_EVENT(event, UP_ARROW)) {
      RandomWalk();
      eventCB->setHandled();
   } 
}


void AddSoParticles(SoSeparator *root){
 
  for(int ix=0;ix<N;ix++){
  for(int iy=0;iy<N;iy++){
  	SoSeparator *particle;
	int i=ix+N*iy;
	particle = new SoSeparator;
	position[i] = new SoTransform;
	position[i]->scaleFactor.setValue(1.0, 2.0, 1.0);
	angle[i]=0.0*M_PI/180.0;
	position[i]->rotation.setValue(0.0,0.0,1.0,angle[i]);
	x[i]=dL*(ix+0.5)-Lhalf; y[i]=dL*(iy+0.5)-Lhalf;
	position[i]->translation.setValue(x[i],y[i],0);
	particle->addChild(position[i]); 
	particle->addChild(new SoSphere); 
   	root->addChild(particle);
   }}

}


void RandomWalk(){
		for(int ix=0;ix<N;ix++) for(int iy=0;iy<N;iy++){
		int i = ix+N*iy;
		x[i]+=0.1*(drand48()-0.5); y[i]+=0.1*(drand48()-0.5);
		position[i]->translation.setValue(x[i],y[i],0);
		angle[i]+= (drand48()-0.5)*M_PI/180.0;
		position[i]->rotation.setValue(0,0,1,angle[i]);
	}
}
